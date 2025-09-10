#include "StatusGrpcClient.h"

StatusConPool::StatusConPool(size_t size, std::string host, std::string port):_stop(false),_host(host),_port(port)
{
    for(int i = 0; i < size; ++i){
        auto channel = grpc::CreateChannel(_host + ":" + _port, grpc::InsecureChannelCredentials());
        if (!channel->WaitForConnected(std::chrono::system_clock::now() + std::chrono::seconds(1))) {
            std::cerr << "[StatusConPool] Failed to connect to gRPC server at " << _host << ":" << _port << std::endl;
            --i;
            continue;  // 跳过该连接，或记录失败
        }
        _stubs.push(StatusService::NewStub(channel));
    }
}

StatusConPool::~StatusConPool(){
    Close();
}

void StatusConPool::Close(){
    std::lock_guard<std::mutex> lock(_mutex);
    _stop = true;
    while(!_stubs.empty()){
        _stubs.pop();
    }
    _condition.notify_all(); 

}

void StatusConPool::ReturnStub(std::unique_ptr<StatusService::Stub> stub)
{
    if(!stub){
        return;
    }
    std::lock_guard<std::mutex> lock(_mutex);
    if (_stop) {
        // 不再归还，直接丢弃
        return;
    }

    _stubs.push(std::move(stub));
    _condition.notify_one();
}

std::unique_ptr<StatusService::Stub> StatusConPool::GetStub(){
    std::unique_lock<std::mutex> lock(_mutex);
    _condition.wait(lock, [this]() {
        return _stop || !_stubs.empty();
    });

    if (_stop && _stubs.empty()) {
        return nullptr;
    }

    auto stub = std::move(_stubs.front());
    _stubs.pop();
    return stub;
}

StatusGrpcClient::StatusGrpcClient()
{
    auto& config = ConfigMgr::GetInstance();
    auto host = config["StatusServer"]["Host"];
    auto port = config["StatusServer"]["Port"];
    _pool  = std::make_unique<StatusConPool>(5,host,port);
    
}

StatusGrpcClient* StatusGrpcClient::GetInstance(){
    static StatusGrpcClient instance;
    return &instance;
}
