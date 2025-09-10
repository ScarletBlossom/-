#include "tcpmgr.h"



void TcpMgr::closeConnection()
{
    _socket.close();
}

void TcpMgr::slot_tcp_connect(ServerInfo si)
{
    qDebug()<< "receive tcp connect signal";
    // 尝试连接到服务器
    qDebug() << "Connecting to server...";
    _host = si.Host;
    _port = static_cast<uint16_t>(si.Port.toUInt());
    _socket.connectToHost(si.Host, _port);
}

void TcpMgr::slot_send_data(ReqId id, QByteArray data)
{
    uint16_t write_id = id;

    // 计算长度（使用网络字节序转换）
    quint16 len = static_cast<quint16>(data.length());

    // 创建一个QByteArray用于存储要发送的所有数据
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    // 设置数据流使用网络字节序
    out.setByteOrder(QDataStream::BigEndian);

    // 写入ID和长度
    out << write_id << len;

    // 添加字符串数据
    block.append(data);

    // 发送数据
    _socket.write(block);
    qDebug() << "tcp mgr send byte data is " << block ;
}

void TcpMgr::slot_tcp_complete(ReqId id, int len, QByteArray res)
{
    if(id==ReqId::ID_CHAT_LOGIN_RSP){
        emit sig_login_mod_finsh(id, len, res);
    }
}

TcpMgr::TcpMgr():_recev_pending(false),_host(""),_port(0),_message_id(0),_message_len(0)
{
    connect(this,&TcpMgr::sig_tcp_complete,this,&TcpMgr::slot_tcp_complete);
    connect(&_socket,&QTcpSocket::connected,this,[&](){
        emit sig_tcp_is_connect(true);
    });
    connect(&_socket,&QTcpSocket::readyRead,this,[&]{
        _buffer.append(_socket.readAll());
        QDataStream stream(&_buffer,QIODevice::ReadOnly);
        forever{
            if(!_recev_pending){
                if (_buffer.size() < static_cast<int>(sizeof(quint16) * 2)) {
                    return; // 数据不够，等待更多数据
                }
                // 预读取消息ID和消息长度，但不从缓冲区中移除
                stream >> _message_id >> _message_len;

                //将buffer 中的前四个字节移除
                _buffer = _buffer.mid(sizeof(quint16) * 2);

                // 输出读取的数据
                qDebug() << "Message ID:" << _message_id << ", Length:" << _message_len;

            }
            //buffer剩余长读是否满足消息体长度，不满足则退出继续等待接受
            if(_buffer.size() < _message_len){
                _recev_pending = true;
                return;
            }
            _recev_pending = true;
            QByteArray message = _buffer.mid(0,_message_len);
            _buffer = _buffer.mid(_message_len);
            emit sig_tcp_complete(ReqId(_message_id),_message_len,message);
        }


    });
    connect(&_socket,QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred),this,[&](QAbstractSocket::SocketError error){
        qDebug() << "Error:" << _socket.errorString();
        switch (error) {
            case QAbstractSocket::RemoteHostClosedError:
                qDebug() << "Remote host closed the connection";
                emit sig_tcp_is_connect(false);
                break;
            case QAbstractSocket::HostNotFoundError:
                qDebug() << "Host not found";
                emit sig_tcp_is_connect(false);
                break;
            case QAbstractSocket::ConnectionRefusedError:
                qDebug() << "Connection refused by server";
                emit sig_tcp_is_connect(false);
                break;
            case QAbstractSocket::SocketTimeoutError:
                qDebug() << "Connection refused by server";
                emit sig_tcp_is_connect(false);
                break;
            default:
                qDebug() << "Other Error!";
                break;
        }

    });

    QObject::connect(this, &TcpMgr::sig_send_data, this, &TcpMgr::slot_send_data);

    QObject::connect(&_socket, &QTcpSocket::disconnected, this, [&]() {
        qDebug() << "Disconnected from server.";
    });

}


