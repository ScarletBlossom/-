#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "global.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private:
    Ui::Login *ui;
    void initHttpHandlers();
    void initTcpHandlers();
    void initHead();

    void enableBtn();
    void showTip(QString str,bool);

    void AddTipErr(TipErr te, QString tips);
    void DelTipErr(TipErr te);

    bool checkUserValid();

    QMap<TipErr, QString> _tip_errs;

    int _uid;
    QString _token;

    QMap<ReqId,std::function<void(const QJsonObject&)>> _http_handlers;
    QMap<ReqId,std::function<void(const QJsonObject&)>> _tcp_handlers;
signals:

    void switchRegister();
    void switchResetpw();
    void switchChat();
    void sig_tcp_connect(ServerInfo);
    void sig_send_data(ReqId, QByteArray);



private slots:
    void slot_http_finish(ReqId id,QString res,ErrorCodes err);
    void slot_tcp_finish(bool success);
    void slot_login_finish(ReqId id,int len,QByteArray res);
    void on_login_Button_clicked();
};

#endif // LOGIN_H
