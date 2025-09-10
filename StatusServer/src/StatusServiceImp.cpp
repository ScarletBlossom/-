#include  "../headers/StatusServiceImpl.h"
#include <boost/uuid/uuid.hpp>           // uuid 类型
#include <boost/uuid/uuid_generators.hpp> // uuid 生成器，例如 random_generator
#include <boost/uuid/uuid_io.hpp>        // 用于输出 uuid（operator<<）



std::string generate_unique_string() {
    // 创建UUID对象
    boost::uuids::uuid uuid = boost::uuids::random_generator()();

    // 将UUID转换为字符串
    std::string unique_string = to_string(uuid);

    return unique_string;
}

Status StatusServiceImpl::GetChatServer(ServerContext* context, const GetChatServerReq* request, GetChatServerRsp* reply)
{
    std::string prefix("status server has received :  ");
    auto &server = _servers[_server_index++];
    if(_server_index==_servers.size()){
        _server_index = 0;
    }
    reply->set_host(server.host);
    reply->set_port(server.port);
    reply->set_error(ErrorCodes::Success);
    std::string uid=std::to_string(request->uid());
    std::string token = generate_unique_string();
    RedisMgr::GetInstance()->SetWithExpire(user_prefix +uid,604800,token);
    reply->set_token(token);
    
    return Status::OK;
}

StatusServiceImpl::StatusServiceImpl():_server_index(0)
{
    auto& cfg = ConfigMgr::GetInstance();
    ChatServer server;
    server.port = cfg["ChatServer1"]["Port"];
    server.host = cfg["ChatServer1"]["Host"];
    _servers.push_back(server);

    server.port = cfg["ChatServer2"]["Port"];
    server.host = cfg["ChatServer2"]["Host"];
    _servers.push_back(server);
}