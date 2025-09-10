#pragma once
#include <vector>
#include <boost/asio.hpp>

class IoContextPool{
public:
    using IoService = boost::asio::io_context;
    using work_guard = boost::asio::executor_work_guard<IoService::executor_type>;

    ~IoContextPool();
    static IoContextPool* GetInstance();
    IoService& GetIoContext(); 
    IoContextPool(const IoContextPool&) = delete;
    IoContextPool& operator=(const IoContextPool&) = delete;
    void Stop();
private:
    IoContextPool(size_t size=2);
    std::vector<IoService> _io_context;
    std::vector<work_guard> _work;
    std::vector<std::thread> _threads;
    std ::size_t _next_io_context;
};