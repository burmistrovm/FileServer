#include "server.h"
#include <iostream>

Server::Server(std::string address, std::string port):
    service(),
    acceptor(service),
    signalSet(service),
    handler("./")
{
    signalSet.add(SIGINT);
    signalSet.add(SIGTERM);
    doStop();

    boost::asio::ip::tcp::resolver resolver(service);
    boost::asio::ip::tcp::resolver::query query(address, port);
    boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);

    acceptor.open(endpoint.protocol());
    acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    acceptor.bind(endpoint);
    acceptor.listen();
    accept();
}

void Server::run() {
    std::cout << "accepted" << std::endl;
    std::vector <std::shared_ptr <boost::thread> > threads;
    for (std::size_t i = 0; i < 5; ++i) {
        std::shared_ptr <boost::thread> thread(new boost::thread([this] () {
            service.run();
        }));
        threads.push_back(thread);
    }

    for (std::size_t i = 0; i < threads.size(); ++i) {
        threads[i]->join();
    }
}

void Server::doStop() {
    signalSet.async_wait([this] (const boost::system::error_code& e, int signal_no) {
        service.stop();
    });
}

void Server::accept() {
    connection.reset(new Connection(service, handler));
    acceptor.async_accept(connection -> getSocket(),[this] (const boost::system::error_code& e) {
        if (!e) {
            connection->start();
        }
        accept();
    });
}
