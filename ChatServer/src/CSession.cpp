#include "../headers/CSession.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "../headers/CServer.h"
#include "../headers/LogicSystem.h"

CSession::CSession(boost::asio::io_context& ioc, CServer* server):_socket(ioc), _server(server),_uid(0)
{
    _headNode = std::make_shared<MsgNode>(HEADER_LENGTH);
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    _sessionId = boost::uuids::to_string(uuid);

}
CSession::~CSession()
{
    _isclosed = true;
    closeSession();
}
boost::asio::ip::tcp::socket& CSession::getSocket()
{
    return _socket;
}
std::string CSession::getSessionId()
{
    return _sessionId;
}
void CSession::Start()
{   
    parseHead();
}

void CSession::parseHead()
{
    auto self = shared_from_this();
    _headNode->clear();
    boost::asio::async_read(_socket,boost::asio::buffer(_headNode->_data,HEADER_LENGTH),
    [this,self](const boost::system::error_code& ec, std::size_t bytes_transferred)
    {
        if(!ec && bytes_transferred == HEADER_LENGTH)
        {
            _headParsed = true;
            dealHeader();
        }else
        {
            std::cout<<"Parse head error:"<<ec.message()<<std::endl;
            closeSession();
        }
    });
}

void CSession::dealHeader()
{
    if(!_server->checkSessionExist(_sessionId))
    {
        closeSession();
        return;
    }
    short msg_id = 0;
    memcpy(&msg_id,_headNode->_data,HEAD_ID);
    msg_id = ntohs(msg_id);
    if(msg_id <= 0)
    {
        std::cout<<"Invalid msg id:"<<msg_id<<std::endl;
        _server->removeSession(_sessionId);
        closeSession();
        return;
    }
    short body_len = 0;
    memcpy(&body_len,_headNode->_data+HEAD_ID,HEAD_LENGTH);
    body_len = ntohs(body_len);
    if(body_len < 0 || body_len > MAX_BODY_LENGTH){
        std::cout<<"Invalid body len:"<<body_len<<std::endl;
        _server->removeSession(_sessionId);
        closeSession();
        return;
    }
    _recvNode = std::make_shared<RecvMsgNode>(body_len,msg_id);
    parseBody();
}

void CSession::closeSession()
{   
    std::lock_guard<std::mutex> lg(_sendMtx);
    if(_isclosed){
        return;
    }
    _isclosed = true;
    if(!_sendQue.empty()){
        _close_after_write = true;
        return;
    }
    close();
    
}

void CSession::parseBody()
{
    if(_headParsed){
        return;
    }
    auto self = shared_from_this();
    _recvNode->_len = 0;
    boost::asio::async_read(_socket,boost::asio::buffer(_recvNode->_data,_recvNode->_maxlen),
    [this,self](const boost::system::error_code& ec, std::size_t bytes_transferred){
        if(!ec && bytes_transferred == _recvNode->_maxlen)
        {
            _recvNode->_len = bytes_transferred;
            dealBody();
        }else
        {
            std::cout<<"Parse body error:"<<ec.message()<<std::endl;
            closeSession();
        }
    });
}

void CSession::close()
{
    boost::system::error_code ec;
    _socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both,ec);
    _socket.close(ec);
    _server->removeSession(_sessionId);
}

void CSession::dealBody()
{
    if(!_server->checkSessionExist(_sessionId))
    {
        closeSession();
        return;
    } 
    LogicSystem::getInstance()->pushLogicNode(std::make_shared<LogicNode>(shared_from_this(),_recvNode));
    parseHead();
    _headParsed = false;
}

