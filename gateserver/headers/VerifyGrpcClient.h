#pragma once
#include <grpcpp/grpcpp.h>
#include "message.grpc.pb.h"
#include "const.h"
#include <queue>
#include <atomic>
#include <mutex>
#include <condition_variable>


using grpc::Channel;
using grpc::Status;
using grpc::ClientContext;

using message::GetVerifyReq;
using message::GetVerifyRsp;
using message::VerifyService;

class RpcConPool{
public:
    RpcConPool(size_t size, std::string host, std::string port);
    ~RpcConPool();
    std::unique_ptr<VerifyService::Stub> GetStub();
    void ReturnStub(std::unique_ptr<VerifyService::Stub>);
private:
    std::atomic<bool> _stop;
    size_t _poolsize;
    std::string _host;
    std::string _port;
    std::queue<std::unique_ptr<VerifyService::Stub>> _stub_pool;
    std::mutex _mutex;
    std::condition_variable _condition;

};




class VerifyGrpcClient{

public:
    GetVerifyRsp GetVerifyCode(std::string email);
    static VerifyGrpcClient* GetInstance();
    VerifyGrpcClient(const VerifyGrpcClient & ) = delete;
    VerifyGrpcClient& operator=(const VerifyGrpcClient & ) = delete;
private:
    VerifyGrpcClient();
    std::unique_ptr<RpcConPool> _pool;
};


