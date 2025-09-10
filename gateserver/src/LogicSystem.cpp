#include "LogicSystem.h"
#include "VerifyGrpcClient.h"
#include "StatusGrpcClient.h"


void LogicSystem::RegGet(std::string url, HttpHandler handler) {
	_get_handlers.insert(make_pair(url, handler));
}
LogicSystem* LogicSystem::GetInstance(){
    static LogicSystem instance;
    return &instance;
}

bool LogicSystem::GetVerifyCode(std::shared_ptr<Httpconnection> connection)
{
    auto body_str = boost::beast::buffers_to_string(connection->_request.body().data());
    std::cout << "receive body is " << body_str << std::endl;
    connection->_response.set(http::field::content_type, "text/json");
    Json::Value root;
    Json::Reader reader;
    Json::Value src_root;
    bool parse_success = reader.parse(body_str, src_root);
    if (!parse_success) {
        std::cout << "Failed to parse JSON data!" << std::endl;
        root["error"] = ErrorCodes::Error_Json;
        std::string jsonstr = root.toStyledString();
        beast::ostream(connection->_response.body()) << jsonstr;
        return true;
    }

    auto email = src_root["email"].asString();
    GetVerifyRsp rsp = VerifyGrpcClient::GetInstance()->GetVerifyCode(email);
    std::cout << "email is " << email << std::endl;
    root["error"] = rsp.error();
    root["email"] = src_root["email"];
    std::string jsonstr = root.toStyledString();
    beast::ostream(connection->_response.body()) << jsonstr;
    return true;
}

void LogicSystem::RegPost(std::string url, HttpHandler handler) {
    _post_handlers.insert(make_pair(url, handler));
}

LogicSystem::LogicSystem() {
	RegGet("/get_test", [](std::shared_ptr<Httpconnection> connection) {
		beast::ostream(connection->_response.body()) << "receive get_test req"<<std::endl;
		int i = 0;
        for (auto& elem : connection->_get_params) {
            i++;
            beast::ostream(connection->_response.body()) << "param" << i << " key is " << elem.first;
            beast::ostream(connection->_response.body()) << ", " <<  " value is " << elem.second << std::endl;
        }

	});

    RegPost("/user_login", [](std::shared_ptr<Httpconnection> connection) {
    auto body_str = boost::beast::buffers_to_string(connection->_request.body().data());
    std::cout << "receive body is " << body_str << std::endl;
    connection->_response.set(http::field::content_type, "text/json");
    Json::Value root;
    Json::Reader reader;
    Json::Value src_root;
    bool parse_success = reader.parse(body_str, src_root);
    if (!parse_success) {
        std::cout << "Failed to parse JSON data!" << std::endl;
        root["error"] = ErrorCodes::Error_Json;
        std::string jsonstr = root.toStyledString();
        beast::ostream(connection->_response.body()) << jsonstr;
        return true;
    }

    auto name = src_root["user"].asString();
    auto pwd = src_root["passwd"].asString();
    UserInfo userInfo;
    //查询数据库判断用户名和密码是否匹配
    int uid=0;
    int pwd_valid = SqlMgr::GetInstance()->CheckPW(name, pwd,uid);
    if (pwd_valid <= 0) {
        std::cout << " user pwd not match" << std::endl;
        root["error"] = ErrorCodes::PasswdInvalid;
        std::string jsonstr = root.toStyledString();
        beast::ostream(connection->_response.body()) << jsonstr;
        return true;
    }

    //查询StatusServer找到合适的连接
    auto reply = StatusGrpcClient::GetInstance()->GetChatServer(uid);
    if (reply.error()) {
        std::cout << " grpc get chat server failed, error is " << reply.error()<< std::endl;
        root["error"] = ErrorCodes::RPCFailed;
        std::string jsonstr = root.toStyledString();
        beast::ostream(connection->_response.body()) << jsonstr;
        return true;
    }

    std::cout << "succeed to load userinfo uid is " << userInfo.uid << std::endl;
    root["error"] = 0;
    root["user"] = name;
    root["uid"] = uid;
    root["token"] = reply.token();
    root["host"] = reply.host();
    root["port"] = reply.port();
    std::string jsonstr = root.toStyledString();
    beast::ostream(connection->_response.body()) << jsonstr;
    return true;
    });
    
	RegPost("/reg_verifycode", [this](std::shared_ptr<Httpconnection> connection) {
        GetVerifyCode(connection);
    });

    RegPost("/reset_verifycode", [this](std::shared_ptr<Httpconnection> connection) {

        auto body_str = boost::beast::buffers_to_string(connection->_request.body().data());
        std::cout << "receive body is " << body_str << std::endl;
        connection->_response.set(http::field::content_type, "text/json");
        Json::Value root;
        Json::Reader reader;
        Json::Value src_root;
        bool parse_success = reader.parse(body_str, src_root);
        if (!parse_success) {
            std::cout << "Failed to parse JSON data!" << std::endl;
            root["error"] = ErrorCodes::Error_Json;
            std::string jsonstr = root.toStyledString();
            beast::ostream(connection->_response.body()) << jsonstr;
            return true;
        }

        auto email = src_root["email"].asString();
        auto name = src_root["user"].asString();

        int ret = SqlMgr::GetInstance()->userExists(name,email);
        if(ret<=0){
            std::cout << "ret is" <<ret<<std::endl;
            root["error"] = ErrorCodes::UserOremailErr;
            std::string jsonstr = root.toStyledString();
            beast::ostream(connection->_response.body()) << jsonstr;
            return true;
        }
    
        GetVerifyRsp rsp = VerifyGrpcClient::GetInstance()->GetVerifyCode(email);
        std::cout << "email is " << email << std::endl;
        root["error"] = rsp.error();
        root["email"] = src_root["email"];
        std::string jsonstr = root.toStyledString();
        beast::ostream(connection->_response.body()) << jsonstr;
        return true;
    });

    RegPost("/user_register", [](std::shared_ptr<Httpconnection> connection) {
    auto body_str = boost::beast::buffers_to_string(connection->_request.body().data());
    std::cout << "receive body is " << body_str << std::endl;
    connection->_response.set(http::field::content_type, "text/json");
    Json::Value root;
    Json::Reader reader;
    Json::Value src_root;
    bool parse_success = reader.parse(body_str, src_root);
    if (!parse_success) {
        std::cout << "Failed to parse JSON data!" << std::endl;
        root["error"] = ErrorCodes::Error_Json;
        std::string jsonstr = root.toStyledString();
        beast::ostream(connection->_response.body()) << jsonstr;
        return true;
    }

    auto email = src_root["email"].asString();
    auto name = src_root["user"].asString();
    auto pwd = src_root["passwd"].asString();
    auto confirm = src_root["confirm"].asString();

    //先查找redis中email对应的验证码是否合理
    std::string  verify_code;
    bool b_get_verify = RedisMgr::GetInstance()->Get(CODEPREFIX+src_root["email"].asString(), verify_code);
    if (!b_get_verify) {
        std::cout << " get verify code expired" << std::endl;
        root["error"] = ErrorCodes::VerifyExpired;
        std::string jsonstr = root.toStyledString();
        beast::ostream(connection->_response.body()) << jsonstr;
        return true;
    }

    if (verify_code != src_root["verifycode"].asString()) {
        std::cout << " verify code error" << std::endl;
        root["error"] = ErrorCodes::VerifyCodeErr;
        std::string jsonstr = root.toStyledString();
        beast::ostream(connection->_response.body()) << jsonstr;
        return true;
    }

    //访问redis查找
    // bool b_usr_exist = RedisMgr::GetInstance()->ExistsKey(src_root["user"].asString());
    // if (b_usr_exist) {
    //     std::cout << " user exist" << std::endl;
    //     root["error"] = ErrorCodes::UserExist;
    //     std::string jsonstr = root.toStyledString();
    //     beast::ostream(connection->_response.body()) << jsonstr;
    //     return true;
    // }

    //查找数据库判断用户是否存在
    int uid = SqlMgr::GetInstance()->RegUser(name, email, pwd);
    std::cout << "uid is" << uid << std::endl;
    if (uid == 0 || uid == -1) {
        std::cout << " user or email exist" << std::endl;
        root["error"] = ErrorCodes::UserExist;
        std::string jsonstr = root.toStyledString();
        beast::ostream(connection->_response.body()) << jsonstr;
        return true;
    }

    root["error"] = 0;
    root["uid"] = uid;
    root["email"] = src_root["email"];
    root ["user"]= src_root["user"].asString();
    root["passwd"] = src_root["passwd"].asString();
    root["confirm"] = src_root["confirm"].asString();
    root["verifycode"] = src_root["verifycode"].asString();
    std::string jsonstr = root.toStyledString();
    beast::ostream(connection->_response.body()) << jsonstr;
    return true;
    });

    RegPost("/change_pw", [](std::shared_ptr<Httpconnection> connection) {
    auto body_str = boost::beast::buffers_to_string(connection->_request.body().data());
    std::cout << "receive body is " << body_str << std::endl;
    connection->_response.set(http::field::content_type, "text/json");
    Json::Value root;
    Json::Reader reader;
    Json::Value src_root;
    bool parse_success = reader.parse(body_str, src_root);
    if (!parse_success) {
        std::cout << "Failed to parse JSON data!" << std::endl;
        root["error"] = ErrorCodes::Error_Json;
        std::string jsonstr = root.toStyledString();
        beast::ostream(connection->_response.body()) << jsonstr;
        return true;
    }

    auto email = src_root["email"].asString();
    auto name = src_root["user"].asString();
    auto pwd = src_root["passwd"].asString();
    auto confirm = src_root["confirm"].asString();

    //先查找redis中email对应的验证码是否合理
    std::string  verify_code;
    bool b_get_verify = RedisMgr::GetInstance()->Get(CODEPREFIX+src_root["email"].asString(), verify_code);
    if (!b_get_verify) {
        std::cout << " get verify code expired" << std::endl;
        root["error"] = ErrorCodes::VerifyExpired;
        std::string jsonstr = root.toStyledString();
        beast::ostream(connection->_response.body()) << jsonstr;
        return true;
    }

    if (verify_code != src_root["verifycode"].asString()) {
        std::cout << " verify code error" << std::endl;
        root["error"] = ErrorCodes::VerifyCodeErr;
        std::string jsonstr = root.toStyledString();
        beast::ostream(connection->_response.body()) << jsonstr;
        return true;
    }

    //访问redis查找
    // bool b_usr_exist = RedisMgr::GetInstance()->ExistsKey(src_root["user"].asString());
    // if (b_usr_exist) {
    //     std::cout << " user exist" << std::endl;
    //     root["error"] = ErrorCodes::UserExist;
    //     std::string jsonstr = root.toStyledString();
    //     beast::ostream(connection->_response.body()) << jsonstr;
    //     return true;
    // }

    //查找数据库判断用户是否存在
    int ret = SqlMgr::GetInstance()->ChangePW(name, pwd, email);
    if (ret <=0) {
        std::cout << " CHANGE PW ret is " << ret <<std::endl;
        root["error"] = ErrorCodes::SqlErr;
        std::string jsonstr = root.toStyledString();
        beast::ostream(connection->_response.body()) << jsonstr;
        return true;
    }

    root["error"] = 0;
    root["email"] = src_root["email"];
    root ["user"]= src_root["user"].asString();
    root["passwd"] = src_root["passwd"].asString();
    root["confirm"] = src_root["confirm"].asString();
    root["verifycode"] = src_root["verifycode"].asString();
    std::string jsonstr = root.toStyledString();
    beast::ostream(connection->_response.body()) << jsonstr;
    return true;
    });
    

}

bool LogicSystem::HandleGet(std::string path, std::shared_ptr<Httpconnection> con) {
	if (_get_handlers.find(path) == _get_handlers.end()) {
		return false;
	}

	_get_handlers[path](con);
	return true;
}

bool LogicSystem::HandlePost(std::string path, std::shared_ptr<Httpconnection> con) {
    if (_post_handlers.find(path) == _post_handlers.end()) {
        return false;
    }

    _post_handlers[path](con);
    return true;
}