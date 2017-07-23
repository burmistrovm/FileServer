#ifndef CONNECTION_H
#define CONNECTION_H
#include "serverhandler.h"
#include "../http/parser.h"
#include "../http/request.h"
#include "../http/response.h"
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <memory>
#include <tuple>

class Connection: public boost::enable_shared_from_this<Connection> {
public:
    Connection() = delete;
    Connection(boost::asio::io_service& service, ServerHandler& handler);
    boost::asio::ip::tcp::socket& getSocket();
    void start();
private:
    void read(const boost::system::error_code &e, std::size_t bytes_transferred);
    void write();

    boost::asio::io_service::strand strand;
    boost::asio::ip::tcp::socket socket;
    boost::array<char, 1024> buffer;

    ServerHandler& serverHandler;
    http_request request;
    Parser parser;
    Response response;
};

typedef boost::shared_ptr<Connection> ConnectionPtr;
#endif // CONNECTION_H
