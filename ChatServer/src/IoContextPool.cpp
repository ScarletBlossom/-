#include "../headers/IoContextPool.h"

IoContextPool::IoContextPool(size_t poolSize)
    : _nextIoContext(0), _ioContexts(poolSize)
{
    for(size_t i = 0; i < poolSize; ++i)
    {
        auto guard = boost::asio::make_work_guard(_ioContexts[i]);
        _work_guard.push_back(std::move(guard));
    }
    for(size_t i = 0; i < poolSize; ++i)
    {
        _threads.emplace_back([this, i](){
            _ioContexts[i].run();
        });
    }
}
IoContextPool::~IoContextPool()
{
    Stop();
}

boost::asio::io_context& IoContextPool::getIoContext()
{
    auto& ioContext = _ioContexts[_nextIoContext++];
    if(_nextIoContext == _ioContexts.size())
        _nextIoContext = 0;
    return ioContext;
}

void IoContextPool::Stop()
{
    for(auto& ioContext : _ioContexts)
    {
        ioContext.stop();
    }
    for(auto& thread : _threads)
    {
        if(thread.joinable())
            thread.join();
    }
    _threads.clear();
    _work_guard.clear();
}
