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

inline constexpr int HEADER_LENGTH = 4;
inline constexpr int MAX_BODY_LENGTH = 1024*2;
inline constexpr int HEAD_ID = 2;
inline constexpr int HEAD_LENGTH = 2;
inline constexpr int MAX_RECVQUE = 10000;
inline constexpr int MAX_SENDQUE = 1000;

enum MsgType
{
    TYPE_LOGIN = 1,
    TYPE_LOGOUT = 2,
    TYPE_SINGLE_CHAT = 3,
    TYPE_GROUP_CHAT = 4,
    TYPE_HEART_BEAT = 5,
    TYPE_ERROR = 6,
    TYPE_REGISTER = 7,
    TYPE_VERIFY_CODE = 8,
    TYPE_FRIEND_REQ = 9,
    TYPE_FRIEND_RESP = 10,
    TYPE_ADD_GROUP = 11,
    TYPE_CREATE_GROUP = 12,
    TYPE_OFFLINE_MSG_REQ = 13,
    TYPE_OFFLINE_MSG_RESP = 14,
};

#endif