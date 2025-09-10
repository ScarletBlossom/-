#include "resetpw.h"
#include "ui_resetpw.h"
#include "httpmgr.h"
#include <iostream>

resetpw::resetpw(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::resetpw),_count(5)
{
    ui->setupUi(this);

    ui->pw_edit->setEchoMode(QLineEdit::Password);
    ui->pwagain_edit->setEchoMode(QLineEdit::Password);
    ui->err_tip->setProperty("state","normal");
    repolish(ui->err_tip);
    connect(httpmgr::getInstance().get(),&httpmgr::sig_changepw_mod_finish,this,&resetpw::slot_changepw_mod_finish);
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

    _count_timer = new QTimer(this);
    connect(_count_timer,&QTimer::timeout,[this](){
        _count--;
        if(_count<=0){
            _count_timer->stop();
            emit switchLogin();
        }
        ui->tip_label->setText(QString("密码重置成功！%1 秒后返回登陆").arg(_count));
    });

}

resetpw::~resetpw()
{
    delete ui;
}

void resetpw::ChangeTipPage()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
    _count_timer->start(1000);
}

void resetpw::initHttpHandlers()
{
    _handlers.insert(ReqId::ID_GET_VERIFY_CODE,[this]( QJsonObject jsonObj){
        int error = jsonObj["error"].toInt();
        if(error!=ErrorCodes::SUCCESS){
            std::cout<< "error is" << error <<std::endl;
            showTip(tr("ARGS ERROR!"),false);
            return;
        }
        // auto email = jsonObj["email"].toString();
        showTip(tr("The verify code has been sent to your email, please check out!"),true);
        // qDebug() << "email is " << email;
    });
    _handlers.insert(ReqId::ID_CHANGE_PW,[this](QJsonObject jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            showTip(tr("参数错误"),false);
            return;
        }
        showTip(tr("修改密码成功"), true);
        ChangeTipPage();
    });
}

void resetpw::AddTipErr(TipErr te, QString tips)
{
    _tip_errs[te] = tips;
    showTip(tips, false);
}

void resetpw::DelTipErr(TipErr te)
{
    _tip_errs.remove(te);
    if(_tip_errs.empty()){
        ui->err_tip->clear();
        return;
    }

    showTip(_tip_errs.first(), false);
}

void resetpw::resetToPage1()
{
    ui->stackedWidget->setCurrentWidget(ui->page_1);
}

void resetpw::on_cancel_button_clicked()
{
    emit switchLogin();
}


void resetpw::on_return_button_clicked()
{
    _count_timer->stop();
    emit switchLogin();
}

void resetpw::slot_changepw_mod_finish(ReqId id, QString res, ErrorCodes err)
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

void resetpw::showTip(QString str, bool b_ok)
{
    if(b_ok){
        ui->err_tip->setProperty("state","err");
    }else{
        ui->err_tip->setProperty("state","normal");
    }

    ui->err_tip->setText(str);
    repolish(ui->err_tip);
}



void resetpw::on_verifycode_button_clicked()
{
    auto email =  ui -> email_edit->text();
    auto name = ui -> user_edit ->text();
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email).hasMatch();
    if(match){
        QJsonObject json_obj;
        json_obj["email"] = email;
        json_obj["user"] = name;
        httpmgr::getInstance()->PostHttpReq(QUrl(gate_url_prefix+"/reset_verifycode"),
                                            json_obj, ReqId::ID_GET_VERIFY_CODE,Modules::CHANGEPWMOD);
    }else{
        showTip(tr("Email address is illegal!"),false);
    }
}

bool resetpw::checkUserValid()
{
    if(ui->user_edit->text() == ""){
        AddTipErr(TipErr::TIP_USER_ERR, tr("用户名不能为空"));
        return false;
    }

    DelTipErr(TipErr::TIP_USER_ERR);
    return true;
}

bool resetpw::checkEmailValid()
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

bool resetpw::checkPWValid()
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

bool resetpw::checkPWagainValid()
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

bool resetpw::checkVerifycodeValid()
{
    auto pass = ui->verifycode_edit->text();
    if(pass.isEmpty()){
        AddTipErr(TipErr::TIP_VERIFY_ERR, tr("验证码不能为空"));
        return false;
    }

    DelTipErr(TipErr::TIP_VERIFY_ERR);
    return true;
}


void resetpw::on_confirm_button_clicked()
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
    QJsonObject json_obj;
    json_obj["user"] = ui->user_edit->text();
    json_obj["email"] = ui->email_edit->text();
    json_obj["passwd"] = ui->pw_edit->text();
    json_obj["confirm"] = ui->pwagain_edit->text();
    json_obj["verifycode"] = ui->verifycode_edit->text();
    httpmgr::getInstance()->PostHttpReq(QUrl(gate_url_prefix+"/change_pw"),
                                        json_obj, ReqId::ID_CHANGE_PW,Modules::CHANGEPWMOD);
}


