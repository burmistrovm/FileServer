#include "connection.h"
#include <iostream>

Connection::Connection(boost::asio::io_service& service, ServerHandler& handler):
    strand(service),
    socket(service),
    serverHandler(handler) {
}

boost::asio::ip::tcp::socket& Connection::getSocket() {
    return socket;
}

void Connection::start() {
    auto shared_this = shared_from_this();
    socket.async_read_some(boost::asio::buffer(buffer),
                            strand.wrap([shared_this](const boost::system::error_code& e,
                                                       std::size_t bytes_transferred) {
                                shared_this->read(e, bytes_transferred);
                            }));
}

void Connection::read(const boost::system::error_code &e, std::size_t bytes_transferred) {
    if (!e) {
        result_type result;
        std::tie(result, std::ignore) = parser.parse(
                request, buffer.data(), buffer.data() + bytes_transferred);
        std::cout << bytes_transferred << std::endl;
        auto shared_this = shared_from_this();
        if (result == result_type::good) {
            serverHandler.handle_request(request, response);
            write();
        } else if (result == result_type::bad) {

        } else {
            socket.async_read_some(boost::asio::buffer(buffer),
                                    strand.wrap([shared_this](const boost::system::error_code &e, size_t bytes) {
                                        shared_this->read(e, bytes);
                                    }));
        }
    }
}

void Connection::write() {
    auto self(shared_from_this());
    boost::asio::async_write(socket, response.toBuffers(), [this, self](boost::system::error_code ec, std::size_t) {
        if (!ec) {
            boost::system::error_code ignored_ec;
            socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
        }
    });
}


