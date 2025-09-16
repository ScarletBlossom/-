#pragma once
#include <memory>
#include "CSession.h"
#include "Singleton.hpp"

class LogicSystem:public Singleton<LogicSystem>
{
private:
    /* data */
public:
    LogicSystem(/* args */);
    ~LogicSystem();
    void pushLogicNode(std::shared_ptr<LogicNode> node);

};

