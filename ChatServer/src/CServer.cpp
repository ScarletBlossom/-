#include "../headers/CServer.h"

CServer::CServer(boost::asio::io_context& ioc, short port): _acceptor(ioc, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
    Start();
}

CServer::~CServer()
{
    boost::system::error_code ec;
    _acceptor.close(ec); // 取消 pending accept，相关 handler 会以 operation_aborted 回调
}

void CServer::Start()
{
    auto& iocontext = IoContextPool::getInstance()->getIoContext();
    auto newsession = std::make_shared<CSession>(iocontext, this);
    auto self = shared_from_this(); // 保证在回调里持有 shared_ptr，延长生命周期
    _acceptor.async_accept(newsession->getSocket(),
        [self, newsession](const boost::system::error_code& ec){
            self->DoAccept(newsession, ec);
        }
    );
}

void CServer::DoAccept(std::shared_ptr<CSession> session, const boost::system::error_code& ec)
{
    if(!ec){
        session->Start();
        std::lock_guard<std::mutex> lg(mtx);
        _sessions.insert(std::make_pair(session->getSessionId(),session));
    }else{
        std::cout<<"accept error: "<<ec.message()<<std::endl;
    }
    Start();
}

void CServer::removeSession(const std::string& sessionId)
{
    std::lock_guard<std::mutex> lg(mtx);
    auto it = _sessions.find(sessionId);
    if(it != _sessions.end()){
        _sessions.erase(it);
    }
}

bool CServer::checkSessionExist(const std::string& sessionId)
{
    std::lock_guard<std::mutex> lg(mtx);
    auto it = _sessions.find(sessionId);
    if(it != _sessions.end()){
        return true;
    }
    return false;
}

// void CServer::onTimer()
// {
//     auto now = std::chrono::steady_clock::now();
//     std::lock_guard<std::mutex> lg(mtx);
//     for(auto it = _sessions.begin(); it != _sessions.end(); ){
//         auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - _clock).count();
//         if(duration > 10){
//             it = _sessions.erase(it);
//         }else{
//             ++it;
//         }
//     }
//     _clock = now;
// }