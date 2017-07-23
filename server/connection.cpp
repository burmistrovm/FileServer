#include "connection.h"
#include <iostream>

Connection::Connection(boost::asio::io_service& service, ServerHandler& handler):
    strand(service),
    socket(service),
    serverHandler(handler)
{

}

boost::asio::ip::tcp::socket& Connection::getSocket()
{
    return socket;
}

void Connection::start()
{
    auto shared_this = shared_from_this();
    socket.async_read_some(boost::asio::buffer(buffer),
                            strand.wrap([shared_this](const boost::system::error_code& e,
                                                       std::size_t bytes_transferred) {
                                shared_this->read(e, bytes_transferred);
                            }));
}

void Connection::read(const boost::system::error_code &e, std::size_t bytes_transferred) {
    if (!e) {
        Parser::result_type result;
        std::tie(result, std::ignore) = parser.parse(
                request_, buffer.data(), buffer.data() + bytes_transferred);
        std::cout << bytes_transferred << std::endl;
        auto shared_this = shared_from_this();
        if (result == Parser::result_type::good) {
            std::cout << request_.uri << std::endl;
        } else if (result == Parser::result_type::bad) {

        } else {
            socket.async_read_some(boost::asio::buffer(buffer),
                                    strand.wrap([shared_this](const boost::system::error_code &e, size_t bytes) {
                                        shared_this->read(e, bytes);
                                    }));
        }
    }
}

