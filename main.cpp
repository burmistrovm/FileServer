#include <iostream>
#include <boost/asio.hpp>
#include "unistd.h"
#include <string>
#include "server/server.h"

int main(int argc, char* argv[]) {
    int option;
    std::string port;
    if ((option = getopt(argc, argv, "p:")) != -1) {
        port = optarg;
    }
    else {
        port = "8080";
    }
    Server server("127.0.0.1", port);
    server.run();
    return 0;
}
