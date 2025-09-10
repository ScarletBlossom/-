#pragma once
#include <string>
#include <memory>
#include <mariadb/conncpp.hpp>
#include <queue>
#include <atomic>
#include <string>
#include <thread>
#include <chrono>
#include <map>
#include <mutex>
#include <condition_variable>
#include <iostream>

struct SqlConnection{
    SqlConnection(std::unique_ptr<sql::Connection> c, std::chrono::steady_clock::time_point t)
        : conn(std::move(c)), lastused(t) {}
    std::unique_ptr<sql::Connection> conn;
    std::chrono::steady_clock::time_point lastused;
};


class MySqlPool {

private:
    sql::SQLString _url;
    sql::Properties _property;
    size_t _size;
    std::atomic<bool> _stop;
    bool _connectIsAlive(std::shared_ptr<SqlConnection>);
    void _keepAlive();
    std::thread heartbeatThread;
    const time_t heartbeatIntervalSec=300; 
    std::mutex _mutex;
    std::condition_variable _condition;
    sql::Driver * driver;
    std::queue<std::shared_ptr<SqlConnection>> _pool;


public:
    MySqlPool(size_t, std::string url, std::string pw, std::string user);
    ~MySqlPool();
    std::shared_ptr<SqlConnection> GetConnection();
    void ReturnConnection(std::shared_ptr<SqlConnection>);
    
};