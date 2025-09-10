#ifndef TCPMGR_H
#define TCPMGR_H
#include <QObject>
#include "singleton.h"
#include "global.h"
#include <QNetworkReply>

class TcpMgr:public QObject, public Singleton<TcpMgr>, public std::enable_shared_from_this<TcpMgr>
{
    Q_OBJECT
    friend class Singleton<TcpMgr>;
public:
    void closeConnection();
public slots:
    void slot_tcp_connect(ServerInfo);
    void slot_send_data(ReqId id, QByteArray data);
    void slot_tcp_complete(ReqId id,int len,QByteArray res);

signals:

    void sig_tcp_is_connect(bool success);
    void sig_send_data(ReqId id,QByteArray data);
    void sig_switch_chatdlg();
    // void sig_connect_failed();


    void sig_tcp_complete(ReqId id,int len,QByteArray res);
    void sig_login_mod_finsh(ReqId id,int len,QByteArray res);

private:
    TcpMgr();
    QTcpSocket _socket;
    bool _recev_pending;
    QString _host;
    uint16_t _port;
    QByteArray _buffer;
    quint16 _message_id;
    quint16 _message_len;

};

#endif // TCPMGR_H
