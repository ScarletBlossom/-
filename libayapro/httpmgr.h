#ifndef HTTPMGR_H
#define HTTPMGR_H
#include "global.h"
#include <QObject>
#include <QString>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <memory>
// #include "singleton.h"

class httpmgr: public QObject, public std::enable_shared_from_this<httpmgr>
{
    Q_OBJECT

public:
    ~httpmgr(){};
    static std::shared_ptr<httpmgr> getInstance();
    void PostHttpReq(QUrl url,QJsonObject json,ReqId req_id, Modules mod);
private:
    httpmgr();
    QNetworkAccessManager _manager;
private slots:
    void slot_http_finish(ReqId id, QString res,ErrorCodes err, Modules mod);
signals:
    void sig_http_finish(ReqId id, QString res,ErrorCodes err, Modules mod);
    void sig_reg_mod_finish(ReqId id, QString res,ErrorCodes err);
    void sig_changepw_mod_finish(ReqId id, QString res,ErrorCodes err);
    void sig_login_mod_finish(ReqId id, QString res,ErrorCodes err);
};

#endif // HTTPMGR_H
