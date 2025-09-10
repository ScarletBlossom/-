#include "SqlConnectPool.h"

bool MySqlPool::_connectIsAlive(std::shared_ptr
    <SqlConnection> con){
    try{
        if(!con||_stop) return false;
        std::unique_ptr<sql::Statement> stmt(con->conn->createStatement());
        stmt->execute("SELECT 1");
        return true;
    }catch(sql::SQLException& e){

        return false;
    }
}

void MySqlPool::_keepAlive(){
    while(!_stop){
        std::this_thread::sleep_for(std::chrono::seconds(heartbeatIntervalSec));
        std::lock_guard<std::mutex> lock(_mutex);
        auto size = _pool.size();
        auto now = std::chrono::steady_clock::now();
        
        for(int i=0;i < size; ++i){
            auto con = _pool.front();
            _pool.pop();
            auto intertime = std::chrono::duration_cast<std::chrono::seconds> (now-con->lastused).count();
            if(intertime >= heartbeatIntervalSec){

                if(!_connectIsAlive(con)){
                    try{
                        con = std::make_shared<SqlConnection>(std::unique_ptr<sql::Connection>(driver->connect(_url,_property)),now);
                        _pool.emplace(con);
                    }catch(sql::SQLException& e){
                        std::cout << "重连失败。。。"<<std::endl;
                        std::cout<<e.what()<<std::endl;
                    }
                }else{
                    _pool.emplace(con);
                }
            }
            
        }       
        
    }
}

MySqlPool::MySqlPool(size_t size, std::string url, std::string pw, std::string user):_size(size),_url(url),_stop(false){
    driver = sql::mariadb::get_driver_instance();
    _property["user"] = user;
    _property["password"] = pw;
    try{
        for(size_t i=0;i<size;++i){
        auto now = std::chrono::steady_clock::now();
        auto conn = std::make_shared<SqlConnection> (std::unique_ptr<sql::Connection>(driver->connect(_url,_property)),now);
        _pool.emplace(conn);
        }
    }catch(sql::SQLException& e){
        std::cout<<e.what()<<std::endl;
    }
    
    heartbeatThread = std::thread(&MySqlPool::_keepAlive,this);
}

std::shared_ptr<SqlConnection> MySqlPool::GetConnection(){
    std::unique_lock<std::mutex> lock(_mutex);
    _condition.wait(lock,[this](){
        return _stop||!_pool.empty();
    });
    if(_stop&&_pool.empty()){
        std::cout <<"数据库连接池已关闭！"<<std::endl;
        return nullptr;
    }
    auto now = std::chrono::steady_clock::now();
    auto conn = _pool.front();
    conn->lastused = now;
    _pool.pop();
    return conn;
}

void MySqlPool::ReturnConnection(std::shared_ptr<SqlConnection>conn){   
    std::lock_guard<std::mutex> lock(_mutex);
    if(_stop){
        return;
    }
    _pool.emplace(conn);
    _condition.notify_one();
}

MySqlPool::~MySqlPool(){
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _stop = true;
        while(!_pool.empty()){
            _pool.pop();
        }
        _condition.notify_all();
    }
    if(heartbeatThread.joinable()){
        heartbeatThread.join();
    }
    

}