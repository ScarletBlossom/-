#include "RedisMgr.h"
#include <iostream>
#include <cstring>
#include "ConfigMgr.h"

RedisConPool::RedisConPool(size_t size, const char* host,int port, const char* pw):_stop(false){
    for(size_t i=0; i < size; ++i){
        auto* context = redisConnect(host,port);
        if(context == nullptr ||context->err != 0){
            if(context!= nullptr){
                redisFree(context);
            }
            continue;
        }
        auto reply = (redisReply*)redisCommand(context,"AUTH %s",pw);
        if( reply -> type == REDIS_REPLY_ERROR){
            std::cout << "认证失败" << std::endl;
            redisFree(context);
            freeReplyObject(reply);
            continue;
        }
        freeReplyObject(reply);
        _conpool.push(context);
    }
}
redisContext* RedisConPool::GetRedis(){
    std::unique_lock<std::mutex> lock(_mutex);
    _conditon.wait(lock,[this](){return (_stop||!_conpool.empty());});
    if(_stop&&_conpool.empty()){
        return nullptr;
    }
    auto* context = _conpool.front();
    _conpool.pop();
    return context;
}

void RedisConPool::ReturnRedis(redisContext* context){
    std::lock_guard<std::mutex> lock(_mutex);
    if(_stop){
        return;
    }
    _conpool.push(context);
    _conditon.notify_one();
}

RedisConPool::~RedisConPool(){
    std::lock_guard<std::mutex> lock(_mutex);
    _stop = true;
    while(!_conpool.empty()){
        auto* context = _conpool.front();
        _conpool.pop();
        redisFree(context);
    } 
    _conditon.notify_all();
}

RedisMgr::RedisMgr(){
    ConfigMgr& config = ConfigMgr::GetInstance();
    auto host = config["RedisServer"]["Host"];
    auto port = std::stoi(config["RedisServer"]["Port"]);
    auto pw = config["RedisServer"]["PW"];
    _pool.reset(new RedisConPool(5,host.c_str(),port,pw.c_str()));
}

std::shared_ptr<RedisMgr> RedisMgr::GetInstance(){
    static std::shared_ptr<RedisMgr> ins(new RedisMgr());
    return ins; 
}

bool RedisMgr::Get(const std::string &key, std::string& value)
{   
    auto*context = _pool->GetRedis();
    if(context==nullptr){
        return false;
    }
    auto* reply = (redisReply*)redisCommand(context, "GET %s", key.c_str());
    if (reply == NULL) {
        std::cout << "[ GET  " << key << " ] failed" << std::endl;
        freeReplyObject(reply);
        _pool->ReturnRedis(context);
        return false;
    }

    if (reply->type != REDIS_REPLY_STRING) {
        std::cout << "[ GET  " << key << " ] failed" << std::endl;
        freeReplyObject(reply);
        _pool->ReturnRedis(context);
        return false;
    }

    value = reply->str;
    freeReplyObject(reply);
    _pool->ReturnRedis(context);
    std::cout << "Succeed to execute command [ GET " << key << "  ]" << std::endl;

    return true;
}

bool RedisMgr::Set(const std::string &key, const std::string &value){
    //执行redis命令行
    auto*context = _pool->GetRedis();
    if(context==nullptr){
        return false;
    }
    auto*reply = (redisReply*)redisCommand(context, "SET %s %s", key.c_str(), value.c_str());

    //如果返回NULL则说明执行失败
    if (NULL == reply)
    {
        std::cout << "Execut command [ SET " << key << "  "<< value << " ] failure ! " << std::endl;
        freeReplyObject(reply);
        _pool->ReturnRedis(context);
        return false;
    }

    //如果执行失败则释放连接
    if (!(reply->type == REDIS_REPLY_STATUS && (strcmp(reply->str, "OK") == 0 || strcmp(reply->str, "ok") == 0)))
    {
        std::cout << "Execut command [ SET " << key << "  " << value << " ] failure ! " << std::endl;
        freeReplyObject(reply); 
        _pool->ReturnRedis(context);    
        return false;
    }

    //执行成功 释放redisCommand执行后返回的redisReply所占用的内存
    freeReplyObject(reply);
    std::cout << "Execut command [ SET " << key << "  " << value << " ] success ! " << std::endl;
    _pool->ReturnRedis(context);
    return true;
}


bool RedisMgr::LPush(const std::string &key, const std::string &value)
{
    auto*context = _pool->GetRedis();
    if(context==nullptr){
        return false;
    }
    auto*reply = (redisReply*)redisCommand(context, "LPUSH %s %s", key.c_str(), value.c_str());
    if (NULL == reply)
    {
        std::cout << "Execut command [ LPUSH " << key << "  " << value << " ] failure ! " << std::endl;
        freeReplyObject(reply);
        _pool->ReturnRedis(context);
        return false;
    }

    if (reply->type != REDIS_REPLY_INTEGER || reply->integer <= 0) {
        std::cout << "Execut command [ LPUSH " << key << "  " << value << " ] failure ! " << std::endl;
        freeReplyObject(reply);
        _pool->ReturnRedis(context);
        return false;
    }

    std::cout << "Execut command [ LPUSH " << key << "  " << value << " ] success ! " << std::endl;
    freeReplyObject(reply);
    _pool->ReturnRedis(context);
    return true;
}

bool RedisMgr::LPop(const std::string &key, std::string& value){
    auto*context = _pool->GetRedis();
    if(context==nullptr){
        return false;
    }
    auto*reply = (redisReply*)redisCommand(context, "LPOP %s ", key.c_str());
    if (reply == nullptr || reply->type == REDIS_REPLY_NIL) {
        std::cout << "Execut command [ LPOP " << key<<  " ] failure ! " << std::endl;
        freeReplyObject(reply);
        _pool->ReturnRedis(context);
        return false;
    }
    value = reply->str;
    std::cout << "Execut command [ LPOP " << key <<  " ] success ! " << std::endl;
    freeReplyObject(reply);
    _pool->ReturnRedis(context);
    return true;
}

bool RedisMgr::RPush(const std::string& key, const std::string& value) {
    auto*context = _pool->GetRedis();
    if(context==nullptr){
        return false;
    }
    auto*reply = (redisReply*)redisCommand(context, "RPUSH %s %s", key.c_str(), value.c_str());
    if (NULL == reply)
    {
        std::cout << "Execut command [ RPUSH " << key << "  " << value << " ] failure ! " << std::endl;
        freeReplyObject(reply);
        _pool->ReturnRedis(context);
        return false;
    }

    if (reply->type != REDIS_REPLY_INTEGER || reply->integer <= 0) {
        std::cout << "Execut command [ RPUSH " << key << "  " << value << " ] failure ! " << std::endl;
        freeReplyObject(reply);
        _pool->ReturnRedis(context);
        return false;
    }

    std::cout << "Execut command [ RPUSH " << key << "  " << value << " ] success ! " << std::endl;
    freeReplyObject(reply);
    _pool->ReturnRedis(context);
    return true;
}

bool RedisMgr::RPop(const std::string& key, std::string& value) {
    auto*context = _pool->GetRedis();
    if(context==nullptr){
        return false;
    }
    auto*reply = (redisReply*)redisCommand(context, "RPOP %s ", key.c_str());
    if (reply == nullptr || reply->type == REDIS_REPLY_NIL) {
        std::cout << "Execut command [ RPOP " << key << " ] failure ! " << std::endl;
        freeReplyObject(reply);
        _pool->ReturnRedis(context);
        return false;
    }
    value = reply->str;
    std::cout << "Execut command [ RPOP " << key << " ] success ! " << std::endl;
    freeReplyObject(reply);
    _pool->ReturnRedis(context);
    return true;
}

bool RedisMgr::HSet(const std::string &key, const std::string &hkey, const std::string &value) {
    auto*context = _pool->GetRedis();
    if(context==nullptr){
        return false;
    }
    auto*reply = (redisReply*)redisCommand(context, "HSET %s %s %s", key.c_str(), hkey.c_str(), value.c_str());
    if (reply == nullptr || reply->type != REDIS_REPLY_INTEGER ) {
        std::cout << "Execut command [ HSet " << key << "  " << hkey <<"  " << value << " ] failure ! " << std::endl;
        freeReplyObject(reply);
        _pool->ReturnRedis(context);
        return false;
    }
    std::cout << "Execut command [ HSet " << key << "  " << hkey << "  " << value << " ] success ! " << std::endl;
    freeReplyObject(reply);
    _pool->ReturnRedis(context);
    return true;
}


bool RedisMgr::HSet(const char* key, const char* hkey, const char* hvalue, size_t hvaluelen)
{
    const char* argv[4];
    size_t argvlen[4];
    argv[0] = "HSET";
    argvlen[0] = 4;
    argv[1] = key;
    argvlen[1] = strlen(key);
    argv[2] = hkey;
    argvlen[2] = strlen(hkey);
    argv[3] = hvalue;
    argvlen[3] = hvaluelen;
    auto*context = _pool->GetRedis();
    if(context==nullptr){
        return false;
    }
    auto*reply = (redisReply*)redisCommandArgv(context, 4, argv, argvlen);
    if (reply == nullptr || reply->type != REDIS_REPLY_INTEGER) {
        std::cout << "Execut command [ HSet " << key << "  " << hkey << "  " << hvalue << " ] failure ! " << std::endl;
        freeReplyObject(reply);
        _pool->ReturnRedis(context);
        return false;
    }
    std::cout << "Execut command [ HSet " << key << "  " << hkey << "  " << hvalue << " ] success ! " << std::endl;
    freeReplyObject(reply);
    _pool->ReturnRedis(context);
    return true;
}

std::string RedisMgr::HGet(const std::string &key, const std::string &hkey)
{
    const char* argv[3];
    size_t argvlen[3];
    argv[0] = "HGET";
    argvlen[0] = 4;
    argv[1] = key.c_str();
    argvlen[1] = key.length();
    argv[2] = hkey.c_str();
    argvlen[2] = hkey.length();
    auto*context = _pool->GetRedis();
    if(context==nullptr){
        return "";
    }
    auto*reply = (redisReply*)redisCommandArgv(context, 3, argv, argvlen);
    if (reply == nullptr || reply->type == REDIS_REPLY_NIL) {
        freeReplyObject(reply);
        std::cout << "Execut command [ HGet " << key << " "<< hkey <<"  ] failure ! " << std::endl;
        _pool->ReturnRedis(context);
        return "";
    }

    std::string value = reply->str;
    freeReplyObject(reply);
    std::cout << "Execut command [ HGet " << key << " " << hkey << " ] success ! " << std::endl;
    _pool->ReturnRedis(context);
    return value;
}

bool RedisMgr::Del(const std::string &key)
{
    auto*context = _pool->GetRedis();
    if(context==nullptr){
        return false;
    }
    auto*reply = (redisReply*)redisCommand(context, "DEL %s", key.c_str());
    if (reply == nullptr || reply->type != REDIS_REPLY_INTEGER) {
        std::cout << "Execut command [ Del " << key <<  " ] failure ! " << std::endl;
        freeReplyObject(reply);
        _pool->ReturnRedis(context);
        return false;
    }
    std::cout << "Execut command [ Del " << key << " ] success ! " << std::endl;
     freeReplyObject(reply);
     _pool->ReturnRedis(context);
     return true;
}

bool RedisMgr::ExistsKey(const std::string &key)
{
    auto*context = _pool->GetRedis();
    if(context==nullptr){
        std::cout<<"connect error!"<<std::endl;
        return false;
    }
    auto* reply = (redisReply*)redisCommand(context, "exists %s", key.c_str());
    if (reply == nullptr || reply->type != REDIS_REPLY_INTEGER || reply->integer == 0) {
        std::cout << "Not Found [ Key " << key << " ]  ! " << std::endl;
        freeReplyObject(reply);
        _pool->ReturnRedis(context);
        return false;
    }
    std::cout << " Found [ Key " << key << " ] exists ! " << std::endl;
    freeReplyObject(reply);
    _pool->ReturnRedis(context);
    return true;
}

bool RedisMgr::SetWithExpire(const std::string &key, const int time, const std::string &value)
{
    //执行redis命令行
    auto*context = _pool->GetRedis();
    if(context==nullptr){
        return false;
    }
    auto*reply = (redisReply*)redisCommand(context, "SETEX %s %d %s", key.c_str(), time,value.c_str());

    //如果返回NULL则说明执行失败
    if (NULL == reply)
    {
        std::cout << "Execut command [ SET " << key << "  "<< value << " ] failure ! " << std::endl;
        freeReplyObject(reply);
        _pool->ReturnRedis(context);
        return false;
    }

    //如果执行失败则释放连接
    if (!(reply->type == REDIS_REPLY_STATUS && (strcmp(reply->str, "OK") == 0 || strcmp(reply->str, "ok") == 0)))
    {
        std::cout << "Execut command [ SET " << key << "  " << value << " ] failure ! " << std::endl;
        freeReplyObject(reply); 
        _pool->ReturnRedis(context);    
        return false;
    }

    //执行成功 释放redisCommand执行后返回的redisReply所占用的内存
    freeReplyObject(reply);
    std::cout << "Execut command [ SETEX " << key << "  " << value << " ] success ! " << std::endl;
    _pool->ReturnRedis(context);
    return true;
    
}
