#include <boost/asio.hpp>

#include <memory>

class CServer;

class CSession
{
private:
    boost::asio::ip::tcp::socket _socket;
    CServer* _server; 
public:
    CSession(boost::asio::io_context& ioc, CServer* server);
    void Start();
    ~CSession();
    boost::asio::ip::tcp::socket& getSocket();
    std::string getSessionId();
};

