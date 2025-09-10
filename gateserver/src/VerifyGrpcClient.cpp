#include "VerifyGrpcClient.h"
#include "ConfigMgr.h"
#include <iostream>
#include "StatusGrpcClient.h"

// ========== VerifyGrpcClient ========== //

GetVerifyRsp VerifyGrpcClient::GetVerifyCode(std::string email) {
    GetVerifyRsp reply;
    auto stub = _pool->GetStub();
    if (!stub) {
        reply.set_error(ErrorCodes::RPCFailed);
        return reply;
    }

    ClientContext context;
    GetVerifyReq request;
    request.set_email(email);

    Status status = stub->GetVerifyCode(&context, request, &reply);

    if (status.ok()) {
        _pool->ReturnStub(std::move(stub));
    } else {
        std::cerr << "[VerifyGrpcClient] RPC failed: " << status.error_message() << std::endl;
        // 如果返回的是 UNAVAILABLE 等状态，可以选择不归还 stub 以触发重建机制
        reply.set_error(ErrorCodes::RPCFailed);
        _pool->ReturnStub(std::move(stub));  // 也可选择直接丢弃该 stub
    }

    return reply;
}

VerifyGrpcClient::VerifyGrpcClient() {
    auto& config = ConfigMgr::GetInstance();
    auto host = config["VerifyServer"]["Host"];
    auto port = config["VerifyServer"]["Port"];
    std::cout << "port is: "<< port <<std::endl;
    _pool = std::make_unique<RpcConPool>(5, host, port);
}

VerifyGrpcClient* VerifyGrpcClient::GetInstance() {
    static VerifyGrpcClient instance;
    return &instance;
}


// ========== RpcConPool ========== //

RpcConPool::RpcConPool(size_t size, std::string host, std::string port)
    : _stop(false), _poolsize(size), _host(std::move(host)), _port(std::move(port)) {
    for (size_t i = 0; i < _poolsize; ++i) {
        auto channel = grpc::CreateChannel(_host + ":" + _port, grpc::InsecureChannelCredentials());

        // 等待连接成功，超时时间 1s
        if (!channel->WaitForConnected(std::chrono::system_clock::now() + std::chrono::seconds(1))) {
            std::cerr << "[VerifyServerConPool] Failed to connect to gRPC server at " << _host << ":" << _port << std::endl;
            continue;  // 跳过该连接，或记录失败
        }

        _stub_pool.push(VerifyService::NewStub(channel));
    }

    if (_stub_pool.empty()) {
        std::cerr << "[RpcConPool] Warning: no valid stubs were created!" << std::endl;
    }
}

RpcConPool::~RpcConPool() {
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _stop = true;

        // 清空连接池，确保 stub 析构（释放资源）
        while (!_stub_pool.empty()) {
            _stub_pool.pop();
        }
    }
    _condition.notify_all();  // 唤醒等待线程
}

std::unique_ptr<VerifyService::Stub> RpcConPool::GetStub() {
    std::unique_lock<std::mutex> lock(_mutex);
    _condition.wait(lock, [this]() {
        return _stop || !_stub_pool.empty();
    });

    if (_stop && _stub_pool.empty()) {
        return nullptr;
    }

    auto stub = std::move(_stub_pool.front());
    _stub_pool.pop();
    return stub;
}



void RpcConPool::ReturnStub(std::unique_ptr<VerifyService::Stub> stub) {
    if (!stub) return;

    std::lock_guard<std::mutex> lock(_mutex);
    if (_stop) {
        // 不再归还，直接丢弃
        return;
    }

    _stub_pool.push(std::move(stub));
    _condition.notify_one();
}
