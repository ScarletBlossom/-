#ifndef HTTP_CONNECTION
#define HTTP_CONNECTION
#include "const.h"

class Httpconnection: public std::enable_shared_from_this<Httpconnection>{
    friend class LogicSystem;
public:
    Httpconnection(boost::asio::io_context &io_context);
    void Start();
    std::string _get_url;
    std::unordered_map<std::string, std::string> _get_params;
    tcp::socket& GetSocket();


private:
    void PreParseGetParam();
    void CheckDeadline();
    void WriteResponse();
    void HandleReq();

    tcp::socket _socket;
    beast::flat_buffer _buffer{8192};
    http::request<http::dynamic_body> _request;
    http::response<http::dynamic_body> _response;
    net::steady_timer deadline_{
        _socket.get_executor(),std::chrono::seconds(60)
    };
};
#endif