#include "../headers/IoConTextPool.h"

IoContextPool::IoContextPool(std::size_t size):_io_context(size),_next_io_context(0){
    for(std::size_t i=0;i<size;++i){
        _work.emplace_back(boost::asio::make_work_guard(_io_context[i]));
    }
    for(std::size_t i=0;i<size;++i){
        _threads.emplace_back([this,i](){
            _io_context[i].run();
        });

    }
}
IoContextPool::~IoContextPool(){
    Stop();
}

void IoContextPool::Stop(){
    // Step 1: 停止所有 io_context
    for (auto& io : _io_context) {
        io.stop();  // 显式停止 run()
    }
    // Step 2: 重置所有 work_guard（释放保活器）
    for (auto& guard : _work) {
        guard.reset();
    }
    // Step 3: 等待所有线程退出
    for (auto& t : _threads) {
        if (t.joinable())
            t.join();
    }
}
IoContextPool* IoContextPool::GetInstance(){
    static IoContextPool instance;
    return &instance;
}

boost::asio::io_context& IoContextPool::GetIoContext(){
    auto &IoContext = _io_context[_next_io_context++];
    if(_next_io_context == _io_context.size()){
        _next_io_context = 0;
    }
    return IoContext;
}
