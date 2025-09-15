#include <boost/asio.hpp>
#include "Const.h"
#include <boost/asio/buffer.hpp>
#include <memory>
#include <mutex>

class CServer;

class CSession
{
private:
    boost::asio::ip::tcp::socket _socket;
    CServer* _server; 
public:
    CSession(boost::asio::io_context& ioc, CServer* server);
    void Start();
    void dealHeader(const boost::system::error_code& ec, std::size_t bytes_transferred);
    void dealBody(const boost::system::error_code& ec, std::size_t bytes);
    ~CSession();
    boost::asio::ip::tcp::socket& getSocket();
    std::string getSessionId();
    boost::asio::streambuf _recvBuffer;
    std::string _sessionId;
    int _uid ;
    std::mutex _sessionMtx;
    std::mutex _sendMtx;
    std::deque<> _sendQue;
    std::

};

