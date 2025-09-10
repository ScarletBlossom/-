#include "../headers/CSession.h"

CSession::CSession(boost::asio::io_context& ioc, CServer* server):_socket(ioc), _server(server)
{
}
CSession::~CSession()
{
}