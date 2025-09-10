#include "server.h"
#include "Httpconnection.h"
#include "IoConTextPool.h"

CServer::CServer(boost::asio::io_context&ioc,unsigned short& port):_ioc(ioc),
_acceptor(ioc, tcp::endpoint(tcp::v4(), port)){
}
void CServer::Start(){
    auto self = shared_from_this();
    auto& io_context = IoContextPool::GetInstance()->GetIoContext();
    std::shared_ptr<Httpconnection> new_con = std::make_shared<Httpconnection>(io_context);
    _acceptor.async_accept(new_con->GetSocket(),[self,new_con](beast::error_code ec){
        try{
            //出错放弃连接，继续监听其他连接
            if(ec){
                self->Start();
                return;
            }
            new_con->Start();
            self->Start();
        }
        catch(std::exception& exp){
            std::cout << "exception is " << exp.what() << std::endl;
			self->Start();
        }
    });
}