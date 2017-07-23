#ifndef SERVERHANDLER_H
#define SERVERHANDLER_H
#include <string>
#include <fstream>
#include "../http/request.h"
#include "../http/response.h"
#include "../http/mime.h"
struct response;
struct request;

class ServerHandler {
public:
  ServerHandler() = delete;
  ServerHandler(const std::string& root);
  void handle_request(const http_request& req, Response& resp);
private:
  std::string docRoot;
  static bool url_decode(const std::string& in, std::string& out);
};

#endif // SERVERHANDLER_H
