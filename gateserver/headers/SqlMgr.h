#pragma once
#include "SqlConnectPool.h"
#include "MysqlDAO.h"

class SqlMgr{
private:
    MysqlDAO _dao;
    SqlMgr();
    SqlMgr(SqlMgr&) = delete;
    SqlMgr& operator=(SqlMgr&) = delete;
public:
    ~SqlMgr() = default;
    static SqlMgr* GetInstance();
    int RegUser(const std::string& name, const std::string& email,  const std::string& pwd);
    int userExists(const std::string &username, const std::string &email);
    int ChangePW(const std::string &username, const std::string &password, const std::string &email);
    int CheckPW(std::string name,std::string pwd,int &uid);
};