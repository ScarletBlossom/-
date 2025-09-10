#include "httpmgr.h"

httpmgr::httpmgr()
{
    connect(this,&httpmgr::sig_http_finish,this,&httpmgr::slot_http_finish );
}





std::shared_ptr<httpmgr> httpmgr::getInstance()
{
    static httpmgr inst;  // 静态局部变量
    static std::shared_ptr<httpmgr> shared_inst(
        &inst,
        [](httpmgr*){}  // 空删除器
        );
    return shared_inst;
}

void httpmgr::PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod)
{
    QByteArray data = QJsonDocument(json).toJson();
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(data.length()));
    auto self = shared_from_this();
    QNetworkReply * reply = _manager.post(request,data);
    connect(reply,&QNetworkReply::finished,[self,reply,req_id,mod](){
        if (reply->error()!=QNetworkReply::NoError){
            qDebug() << reply->errorString();
            emit self->sig_http_finish(req_id,"",ErrorCodes::ERR_NETWORK, mod);
            reply->deleteLater();
            return;
        }
        QString res = reply -> readAll();
        emit self->sig_http_finish(req_id,res,ErrorCodes::SUCCESS, mod);
        reply -> deleteLater();
    });
}

void httpmgr::slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod)
{
    if(mod ==Modules::REGISTERMOD){
        emit sig_reg_mod_finish(id,res,err);
    }
    if(mod ==Modules::CHANGEPWMOD){
        emit sig_changepw_mod_finish(id,res,err);
    }
    if(mod ==Modules::LOGINMOD){
        emit sig_login_mod_finish(id,res,err);
    }

}
