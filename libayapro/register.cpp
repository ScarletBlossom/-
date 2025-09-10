#include "register.h"
#include "ui_register.h"
#include "global.h"
#include "httpmgr.h"

Register::Register(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Register),_count(5)
{
    // ui->stackedWidget->setCurrentWidget(ui->page_1);
    ui->setupUi(this);
    ui->pw_edit->setEchoMode(QLineEdit::Password);
    ui->pwagain_edit->setEchoMode(QLineEdit::Password);
    ui->err_tip->setProperty("state","normal");
    repolish(ui->err_tip);
    connect(httpmgr::getInstance().get(),&httpmgr::sig_reg_mod_finish,this,&Register::slot_reg_mod_finish);
    initHttpHandlers();

    ui->err_tip->clear();

    connect(ui->user_edit,&QLineEdit::editingFinished,this,[this](){
        checkUserValid();
    });

    connect(ui->email_edit, &QLineEdit::editingFinished, this, [this](){
        checkEmailValid();
    });

    connect(ui->pw_edit, &QLineEdit::editingFinished, this, [this](){
        checkPWValid();
    });

    connect(ui->pwagain_edit, &QLineEdit::editingFinished, this, [this](){
        checkPWagainValid();
    });

    connect(ui->verifycode_edit, &QLineEdit::editingFinished, this, [this](){
        checkVerifycodeValid();
    });

    ui->pw_visible->setCursor(Qt::PointingHandCursor);
    ui->pwagain_visible->setCursor(Qt::PointingHandCursor);

    ui->pw_visible->SetState("unvisible","unvisible_hover","","visible",
                               "visible_hover","");

    ui->pwagain_visible->SetState("unvisible","unvisible_hover","","visible",
                                  "visible_hover","");
    //连接点击事件

    connect(ui->pw_visible, &ClickedLabel::clicked, this, [this]() {
        auto state = ui->pw_visible->GetCurState();
        if(state == ClickLbState::Normal){
            ui->pw_edit->setEchoMode(QLineEdit::Password);
        }else{
            ui->pw_edit->setEchoMode(QLineEdit::Normal);
        }
        qDebug() << "Label was clicked!";
    });

    connect(ui->pwagain_visible, &ClickedLabel::clicked, this, [this]() {
        auto state = ui->pwagain_visible->GetCurState();
        if(state == ClickLbState::Normal){
            ui->pwagain_edit->setEchoMode(QLineEdit::Password);
        }else{
            ui->pwagain_edit->setEchoMode(QLineEdit::Normal);
        }
        qDebug() << "Label was clicked!";
    });
    _count_timer = new QTimer(this);

    connect(_count_timer,&QTimer::timeout,[this](){
        _count--;
        if(_count<=0){
            _count_timer->stop();
            emit switchLogin();
        }
        ui->return_label->setText(QString("注册成功，%1 秒后返回登陆").arg(_count));

    });


}

Register::~Register()
{
    delete ui;
}

void Register::AddTipErr(TipErr te, QString tips)
{
    _tip_errs[te] = tips;
    showTip(tips, false);
}

void Register::DelTipErr(TipErr te)
{
    _tip_errs.remove(te);
    if(_tip_errs.empty()){
        ui->err_tip->clear();
        return;
    }

    showTip(_tip_errs.first(), false);
}

void Register::ChangeTipPage()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
    _count_timer->start(1000);

}

void Register::resetToPage1()
{
    ui->stackedWidget->setCurrentWidget(ui->page_1);
}

void Register::on_verifyButton_clicked()
{
    auto email =  ui -> email_edit->text();
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email).hasMatch();
    if(match){
        QJsonObject json_obj;
        json_obj["email"] = email;
        httpmgr::getInstance()->PostHttpReq(QUrl(gate_url_prefix+"/reg_verifycode"),
                                            json_obj, ReqId::ID_GET_VERIFY_CODE,Modules::REGISTERMOD);
    }else{
        showTip(tr("Email address is illegal!"),false);
    }
}

void Register::slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err)
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
    _handlers[id](jsonDoc.object());
    return;

}

void Register::initHttpHandlers()
{//注册获取验证码回包的逻辑
    _handlers.insert(ReqId::ID_GET_VERIFY_CODE,[this]( QJsonObject jsonObj){
        int error = jsonObj["error"].toInt();
        if(error!=ErrorCodes::SUCCESS){
            showTip(tr("ARGS ERROR!"),false);
            return;
        }
        auto email = jsonObj["email"].toString();
        showTip(tr("The verify code has been sent to your email, please check out!"),true);
        qDebug() << "email is " << email;
    });
    _handlers.insert(ReqId::ID_REG_USER, [this](QJsonObject jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            showTip(tr("参数错误"),false);
            return;
        }
        auto email = jsonObj["email"].toString();
        showTip(tr("用户注册成功"), true);
        // qDebug()<< "email is " << email ;
        // qDebug()<< "user uuid is " <<  jsonObj["uuid"].toString();
        ChangeTipPage();
    });
}

void Register::showTip(QString str,bool b_ok)
{
    if(b_ok){
        ui->err_tip->setProperty("state","err");
    }else{
        ui->err_tip->setProperty("state","normal");
    }

    ui->err_tip->setText(str);
    repolish(ui->err_tip);

}

bool Register::checkUserValid()
{
    if(ui->user_edit->text() == ""){
        AddTipErr(TipErr::TIP_USER_ERR, tr("用户名不能为空"));
        return false;
    }

    DelTipErr(TipErr::TIP_USER_ERR);
    return true;
}

bool Register::checkEmailValid()
{
    //验证邮箱的地址正则表达式
    auto email = ui->email_edit->text();
    // 邮箱地址的正则表达式
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email).hasMatch(); // 执行正则表达式匹配
    if(!match){
        //提示邮箱不正确
        AddTipErr(TipErr::TIP_EMAIL_ERR, tr("邮箱地址不正确"));
        return false;
    }

    DelTipErr(TipErr::TIP_EMAIL_ERR);
    return true;
}

bool Register::checkPWValid()
{
    auto pass = ui->pw_edit->text();

    if(pass.length() < 6 || pass.length()>15){
        //提示长度不准确
        AddTipErr(TipErr::TIP_PWD_ERR, tr("密码长度应为6~15"));
        return false;
    }

    // 创建一个正则表达式对象，按照上述密码要求
    // 这个正则表达式解释：
    // ^[a-zA-Z0-9!@#$%^&*]{6,15}$ 密码长度至少6，可以是字母、数字和特定的特殊字符
    QRegularExpression regExp("^[a-zA-Z0-9!@#$%^&*]{6,15}$");
    bool match = regExp.match(pass).hasMatch();
    if(!match){
        //提示字符非法
        AddTipErr(TipErr::TIP_PWD_ERR, tr("不能包含非法字符"));
        return false;;
    }

    DelTipErr(TipErr::TIP_PWD_ERR);

    return true;
}

bool Register::checkPWagainValid()
{
    auto pw = ui->pw_edit->text();
    auto pw_again = ui->pwagain_edit->text();
    if(pw != pw_again){
        AddTipErr(TipErr::TIP_PWD_CONFIRM,tr("两次密码不一致"));
        return false;
    }
    DelTipErr(TipErr::TIP_PWD_CONFIRM);
    return true;
}

bool Register::checkVerifycodeValid()
{
    auto pass = ui->verifycode_edit->text();
    if(pass.isEmpty()){
        AddTipErr(TipErr::TIP_VERIFY_ERR, tr("验证码不能为空"));
        return false;
    }

    DelTipErr(TipErr::TIP_VERIFY_ERR);
    return true;
}



void Register::on_confirm_button_clicked()
{
    bool valid = checkUserValid();
    if(!valid){
        return;
    }

    valid = checkEmailValid();
    if(!valid){
        return;
    }

    valid = checkPWValid();
    if(!valid){
        return;
    }

    valid = checkPWagainValid();
    if(!valid){
        return;
    }

    valid = checkVerifycodeValid();
    if(!valid){
        return;
    }
    //day11 发送http请求注册用户
    QJsonObject json_obj;
    json_obj["user"] = ui->user_edit->text();
    json_obj["email"] = ui->email_edit->text();
    json_obj["passwd"] = ui->pw_edit->text();
    json_obj["confirm"] = ui->pwagain_edit->text();
    json_obj["verifycode"] = ui->verifycode_edit->text();
    httpmgr::getInstance()->PostHttpReq(QUrl(gate_url_prefix+"/user_register"),
                                        json_obj, ReqId::ID_REG_USER,Modules::REGISTERMOD);
}




void Register::on_return_login_clicked()
{
    _count_timer->stop();
    emit switchLogin();
}


void Register::on_cancel_button_clicked()
{
    emit switchLogin();
}

