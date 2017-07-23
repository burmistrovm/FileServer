#ifndef SERVER_H
#define SERVER_H
#include <string>
#include <boost/asio.hpp>
#include "connection.h"
#include "serverhandler.h"
#include <boost/thread.hpp>
#include <memory>
#include <vector>


class Server {
public:
    Server() = delete;
    Server(std::string address, std::string port);
    void run();
private:
    boost::asio::io_service service;
    boost::asio::ip::tcp::acceptor acceptor;
    boost::asio::signal_set signalSet;

    ServerHandler handler;
    ConnectionPtr connection;
    void doStop();
    void accept();
};

#endif // SERVER_H
