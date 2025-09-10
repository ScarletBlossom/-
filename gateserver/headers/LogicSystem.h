#pragma once
#include <functional>
#include "const.h"
#include <map>
#include "Httpconnection.h"
#include "RedisMgr.h"
#include "SqlMgr.h"

using HttpHandler = std::function<void(std::shared_ptr<Httpconnection>)>;
class LogicSystem{
public:
    ~LogicSystem(){};
    bool HandleGet(std::string path,std::shared_ptr<Httpconnection> con);
    bool HandlePost(std::string path,std::shared_ptr<Httpconnection> con);
    void RegGet(std::string url,HttpHandler handler);
    void RegPost(std::string url,HttpHandler handler);
    static LogicSystem* GetInstance();
    LogicSystem(const LogicSystem&) = delete;
    LogicSystem& operator=(const LogicSystem&) = delete;
    bool GetVerifyCode(std::shared_ptr<Httpconnection> conn);

private:
    LogicSystem();
    std::map<std::string, HttpHandler> _post_handlers;
	std::map<std::string, HttpHandler> _get_handlers;

};