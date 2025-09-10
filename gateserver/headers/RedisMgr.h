#pragma once
#include <hiredis/hiredis.h>
#include <memory>
#include <atomic>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>


class RedisConPool{
public:   
    // struct deleter{
    //     void operator()(redisContext* ptr){
    //         if(ptr) redisFree(ptr);
    //     }
    // };
    // using redisCon = std::unique_ptr<redisContext,deleter>;
    RedisConPool(size_t size, const char* host,int port, const char* pw);
    ~RedisConPool();
    redisContext* GetRedis();
    void ReturnRedis(redisContext*);

private:
    std::atomic<bool> _stop;
    std::queue<redisContext*> _conpool;
    std::mutex _mutex;
    std::condition_variable _conditon;
};

class RedisMgr:std::enable_shared_from_this<RedisMgr>{
public: 
    ~RedisMgr() = default;
    RedisMgr(const RedisMgr&) = delete;
    RedisMgr& operator=(const RedisMgr&) = delete;
    bool Get(const std::string &key, std::string& value);
    bool Set(const std::string &key, const std::string &value);

    bool LPush(const std::string &key, const std::string &value);
    bool LPop(const std::string &key, std::string& value);
    bool RPush(const std::string& key, const std::string& value);
    bool RPop(const std::string& key, std::string& value);
    bool HSet(const std::string &key, const std::string  &hkey, const std::string &value);
    bool HSet(const char* key, const char* hkey, const char* hvalue, size_t hvaluelen);
    std::string HGet(const std::string &key, const std::string &hkey);
    bool Del(const std::string &key);
    bool ExistsKey(const std::string &key);
    
    static std::shared_ptr<RedisMgr> GetInstance();
protected:
    RedisMgr();
    std::unique_ptr<RedisConPool> _pool;
};