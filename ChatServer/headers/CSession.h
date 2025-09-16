#pragma once
#include <boost/asio.hpp>
#include "Const.h"
#include <boost/asio/buffer.hpp>
#include <memory>
#include <mutex>
#include <queue>
#include "MsgNode.h"


class CServer;
class LogicSystem;

class CSession:public std::enable_shared_from_this<CSession>
{
private:
    boost::asio::ip::tcp::socket _socket;
    CServer* _server; 
    void close();
public:
    CSession(boost::asio::io_context& ioc, CServer* server);
    void Start();
    void dealHeader(const boost::system::error_code& ec, std::size_t bytes_transferred);
    void dealBody(const boost::system::error_code& ec, std::size_t bytes);
    ~CSession();
    boost::asio::ip::tcp::socket& getSocket();
    std::string getSessionId();
    std::string _sessionId;
    int _uid;
    // std::mutex _sessionMtx;
    std::mutex _sendMtx;
    std::queue<std::shared_ptr<SendMsgNode>> _sendQue;

    void sendMsg(const char* data,short len,short msg_id);
    void doSend();
    std::shared_ptr<RecvMsgNode> _recvNode;
    std::shared_ptr<MsgNode> _headNode;
    bool _isclosed = false;
    void closeSession();
    bool _headParsed = false;
    void parseHead();
    void parseBody();
    void dealHeader();
    void dealBody();
    bool _close_after_write = false;
    
};

class LogicNode{
    friend class LogicSystem;
public:
    LogicNode(std::shared_ptr<CSession> session,std::shared_ptr<RecvMsgNode> node);
private:
    std::shared_ptr<CSession> _session;
    std::shared_ptr<RecvMsgNode> _node;   
};

