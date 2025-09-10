#include "../headers/SqlMgr.h"
#include "SqlMgr.h"

SqlMgr::SqlMgr() {
}

SqlMgr* SqlMgr::GetInstance(){
    static SqlMgr instance;
    return &instance;
}

int SqlMgr::RegUser(const std::string& name, const std::string& email, const std::string& pwd)
{
    return _dao.RegisterUser(name, pwd, email);
}

int SqlMgr::userExists(const std::string &username, const std::string &email){
    return _dao.userExists(username,email);
}

int SqlMgr::ChangePW(const std::string &username, const std::string &password, const std::string &email){
    return _dao.ChangePW(username,password,email);
}

int SqlMgr::CheckPW(std::string name, std::string pwd,int &uid)
{
    return _dao.CheckPW(name,pwd,uid);
}