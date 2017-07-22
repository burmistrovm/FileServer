#include <iostream>
#include <string>
#include "unistd.h"

int main(int argc, char* argv[])
{
    int option;
    std::string port;
    if ((option = getopt(argc, argv, "p:")) != -1) {
        port = std::string(optarg);
    }
    else {
        port = "8080";
    }
    std::cout << port;
    return 0;
}
