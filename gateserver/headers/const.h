#ifndef CONST_H
#define CONST_H

#include <boost/beast/http.hpp>
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <memory>
#include <iostream>

#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/reader.h>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
enum ErrorCodes {
    Success = 0,
    Error_Json = 1001,  //Json解析错误
    RPCFailed = 1002,  //RPC请求错误
    VerifyExpired = 1003, //验证码超时
    VerifyCodeErr = 1004, //验证码不匹配
    UserExist = 1005, //用户名重复
    UserOremailErr = 1006,
    SqlErr = 1007,
    PasswdInvalid,
};

struct UserInfo
{
    std::string Host;
    std::string Port;
    std::string Token;
    int uid;
};

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

#define CODEPREFIX "code_"



#endif