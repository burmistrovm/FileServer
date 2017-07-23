#ifndef SERVER_H
#define SERVER_H
#include <string>
#include <boost/asio.hpp>


class Server {
public:
    Server() = delete;
    Server(std::string address, std::string port);
    void run();
private:
    boost::asio::io_service service;
    boost::asio::ip::tcp::acceptor acceptor;

};

#endif // SERVER_H
