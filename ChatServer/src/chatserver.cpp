#include <boost/asio.hpp>



int main() {
    boost::asio::io_context ioc;
    boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);
    signals.async_wait([&](const boost::system::error_code&, int) {
        ioc.stop();
    });
    

    ioc.run();
    return 0;
}