#pragma once
#include <memory>
#include "ConfigMgr.h"
#include <grpcpp/grpcpp.h>
#include "message.grpc.pb.h"
#include <queue>
#include <condition_variable>
#include <string>


using grpc::Channel;
using grpc::Status;
using grpc::ClientContext;

using message::GetChatServerReq;
using message::GetChatServerRsp;
using message::StatusService;

class StatusConPool{
public:
    std::unique_ptr<StatusService::Stub> GetStub();
    void ReturnStub(std::unique_ptr<StatusService::Stub> stub);
    void Close();
    StatusConPool(size_t size=5,std::string host,std::string port);
    ~StatusConPool();
private:
    std::queue<std::unique_ptr<StatusService::Stub>> _stubs;
    std::mutex _mutex;
    std::condition_variable _condition;
    std::string _host;
    std::string _port;
    std::atomic<bool> _stop;

};

class StatusGrpcClient
{
public:
    ~StatusGrpcClient() {

    }
    GetChatServerRsp GetChatServer(int uid);
    StatusGrpcClient(StatusGrpcClient&) = delete;
    StatusGrpcClient& operator=(StatusGrpcClient&) = delete;
    static StatusGrpcClient* GetInstance();

private:
    
    StatusGrpcClient();
    std::unique_ptr<StatusConPool> _pool;

};