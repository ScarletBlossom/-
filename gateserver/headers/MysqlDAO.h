#pragma once
#include "SqlConnectPool.h"
#include <string>

class MysqlDAO {
public:
    MysqlDAO();
    int RegisterUser(const std::string& username, const std::string& password, const std::string& email);
    int ChangePW(const std::string& username, const std::string& password, const std::string& email);
    int userExists(const std::string& username, const std::string& email);
    int CheckPW(const std::string& username,const std::string& pw,int& uid);

private:
    std::unique_ptr<MySqlPool> _pool;
};