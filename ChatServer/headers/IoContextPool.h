#include <boost/asio.hpp>
#include <thread>
#include "Singleton.hpp"
#include <vector>



class IoContextPool: public Singleton<IoContextPool>
{
    friend class Singleton<IoContextPool>;
public:
    
    ~IoContextPool();
    boost::asio::io_context& getIoContext();
    void Stop();
    

private:
    IoContextPool(size_t poolSize = std::thread::hardware_concurrency()); 
    std::vector<boost::asio::io_context> _ioContexts;
    std::vector<boost::asio::executor_work_guard<boost::asio::io_context::executor_type>> _work_guard;
    std::vector<std::thread> _threads;
    size_t _nextIoContext;
};