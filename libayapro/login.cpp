#include "login.h"
#include "ui_login.h"
#include "httpmgr.h"
#include "tcpmgr.h"
#include <QPainter>
#include <QPainterPath>

Login::Login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Login), _uid(0),_token()
{
    ui->setupUi(this);

    ui->err_tip->setProperty("state","normal");

    connect(ui->user_edit,&QLineEdit::editingFinished,this,[this](){
        checkUserValid();
    });


    repolish(ui->err_tip);
    ui->pw_edit->setEchoMode(QLineEdit::Password);
    connect(ui->RegisterButton,&QPushButton::clicked,this,&Login::switchRegister);
    connect(ui->forgetButton,&QPushButton::clicked,this,&Login::switchResetpw);
    connect(httpmgr::getInstance().get(),&httpmgr::sig_login_mod_finish,this,&Login::slot_http_finish);

    connect(this,&Login::sig_tcp_connect,TcpMgr::getInstance().get(),&TcpMgr::slot_tcp_connect);
    connect(TcpMgr::getInstance().get(),&TcpMgr::sig_tcp_is_connect,this,&Login::slot_tcp_finish);
    connect(this,&Login::sig_send_data,TcpMgr::getInstance().get(),&TcpMgr::sig_send_data);
    connect(TcpMgr::getInstance().get(),&TcpMgr::sig_login_mod_finsh,this,&Login::slot_login_finish);

    initHead();
    initHttpHandlers();
    initTcpHandlers();
}

Login::~Login()
{
    delete ui;
}

void Login::initHttpHandlers()
{
    _http_handlers.insert(ID_CHAT_LOGIN_RSP,[&](const QJsonObject& jsonObj){
        int error = jsonObj["error"].toInt();
        if(error!=ErrorCodes::SUCCESS){
            showTip(tr("ARGS ERROR!"),false);
            enableBtn();
            return;
        }
        ServerInfo si;
        si.Uid = jsonObj["uid"].toInt();
        si.Host = jsonObj["host"].toString();
        si.Port = jsonObj["port"].toString();
        si.Token = jsonObj["token"].toString();
        _uid = si.Uid;
        _token = si.Token;

        qDebug() << " uid is " << si.Uid <<" host is "
                 << si.Host << " Port is " << si.Port << " Token is " << si.Token;
        emit sig_tcp_connect(si);
    });
}


void Login::AddTipErr(TipErr te, QString tips)
{
    _tip_errs[te] = tips;
    showTip(tips, false);
}

void Login::DelTipErr(TipErr te)
{
    _tip_errs.remove(te);
    if(_tip_errs.empty()){
        ui->err_tip->clear();
        return;
    }

    showTip(_tip_errs.first(), false);
}


void Login::initTcpHandlers()
{
    _http_handlers.insert(ID_CHAT_LOGIN_RSP,[&](const QJsonObject& jsonObj){
        int error = jsonObj["error"].toInt();
        if(error!=ErrorCodes::SUCCESS){
            showTip(tr("Login Failed!"),false);
            enableBtn();
            return;
        }
        auto uid = jsonObj["uid"].toInt();
        auto name = jsonObj["name"].toString();
        qDebug() << "uid is" << uid;
        qDebug() << "name is" << name;
        emit switchChat();
    });
}

void Login::initHead()
{
    // 加载图片
    QPixmap originalPixmap(":/res/images/head_1.jpg");
    // 设置图片自动缩放
    qDebug()<< originalPixmap.size() << ui->head_label->size();
    originalPixmap = originalPixmap.scaled(ui->head_label->size(),
                                           Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // 创建一个和原始图片相同大小的QPixmap，用于绘制圆角图片
    QPixmap roundedPixmap(originalPixmap.size());
    roundedPixmap.fill(Qt::transparent); // 用透明色填充

    QPainter painter(&roundedPixmap);
    painter.setRenderHint(QPainter::Antialiasing); // 设置抗锯齿，使圆角更平滑
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    // 使用QPainterPath设置圆角
    QPainterPath path;
    path.addRoundedRect(0, 0, originalPixmap.width(), originalPixmap.height(), 10, 10); // 最后两个参数分别是x和y方向的圆角半径
    painter.setClipPath(path);

    // 将原始图片绘制到roundedPixmap上
    painter.drawPixmap(0, 0, originalPixmap);

    // 设置绘制好的圆角图片到QLabel上
    ui->head_label->setPixmap(roundedPixmap);
}

void Login::enableBtn()
{
    ui->login_Button->setEnabled(true);
    ui->RegisterButton->setEnabled(true);
    ui->forgetButton->setEnabled(true);
}

void Login::showTip(QString str, bool b_ok)
{
    if(b_ok){
        ui->err_tip->setProperty("state","err");
    }else{
        ui->err_tip->setProperty("state","normal");
    }

    ui->err_tip->setText(str);
    repolish(ui->err_tip);
}

bool Login::checkUserValid()
{
    if(ui->user_edit->text() == ""){
        AddTipErr(TipErr::TIP_USER_ERR, tr("用户名不能为空"));
        return false;
    }

    DelTipErr(TipErr::TIP_USER_ERR);
    return true;
}


void Login::slot_http_finish(ReqId id,QString res,ErrorCodes err)
{
    if(err!=ErrorCodes::SUCCESS){
        showTip(tr("NETWORKS REQUESTS ERROR!"),false);
        return;
    }
    QJsonDocument jsonDoc = QJsonDocument:: fromJson(res.toUtf8());
    if(jsonDoc.isNull()){
        showTip(tr("PARSE JSON FALIED!"),false);
        return;
    }
    if(!jsonDoc.isObject()){
        showTip(tr("json解析错误"),false);
        return;
    }
    _http_handlers[id](jsonDoc.object());
    return;
}

void Login::slot_tcp_finish(bool success)
{
    if(success){
        showTip(tr("聊天服务连接成功，正在登录..."),true);
        QJsonObject jsonObj;
        jsonObj["uid"] = _uid;
        jsonObj["token"] = _token;

        QJsonDocument doc(jsonObj);
        QByteArray jsonData = doc.toJson(QJsonDocument::Indented);

        //发送tcp请求给chat server
        emit sig_send_data(ReqId::ID_CHAT_LOGIN_RSP, jsonData);
    }else{
        showTip(tr("Tcp connect failed!"),false);
        enableBtn();
        return;
    }
}

void Login::slot_login_finish(ReqId id, int len, QByteArray res)
{
    Q_UNUSED(len);
    QJsonDocument jsonDoc = QJsonDocument:: fromJson(res);
    if(jsonDoc.isNull()){
        showTip(tr("PARSE JSON FALIED!"),false);
        enableBtn();
        return;
    }
    if(!jsonDoc.isObject()){
        showTip(tr("json解析错误"),false);
        enableBtn();
        return;
    }
    _tcp_handlers[id](jsonDoc.object());
}


void Login::on_login_Button_clicked()
{
    bool valid = checkUserValid();
    if(!valid){
        return;
    }

    QJsonObject user;
    user["name"] = ui->user_edit->text();
    user["passwd"] = ui->pw_edit->text();
    httpmgr::getInstance()->PostHttpReq(QUrl(gate_url_prefix+"/user_login"),user,ReqId::ID_CHAT_LOGIN_RSP,Modules::LOGINMOD);

}

