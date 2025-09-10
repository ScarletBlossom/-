#include <boost/asio.hpp>
#include <memory>
#include "IoContextPool.h"
#include "CSession.h"
#include <map>
#include <string>
#include <iostream>

class CServer : public std::enable_shared_from_this<CServer> {
public:
    CServer(boost::asio::io_context& ioc, short port);
    ~CServer();
    void removeSession(const std::string& sessionId);
    bool checkSessionExist(const std::string& sessionId);
    // void onTimer();
    // void closeTimer();
private:
    void Start();
    void DoAccept(std::shared_ptr<CSession> session, const boost::system::error_code& ec);
    std::map<std::string,std::shared_ptr<CSession>> _sessions;
    boost::asio::ip::tcp::acceptor _acceptor;
    std::mutex mtx;
    // std::chrono::steady_clock _clock;
};


