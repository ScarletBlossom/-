#pragma once
#include<string>

enum ErrorCodes {
    Success = 0,
    Error_Json = 1001,  //Json解析错误
    RPCFailed = 1002,  //RPC请求错误
    VerifyExpired = 1003, //验证码超时
    VerifyCodeErr = 1004, //验证码不匹配
    UserExist = 1005, //用户名重复
    UserOremailErr = 1006,
    SqlErr = 1007,
};

extern const std::string user_prefix; 