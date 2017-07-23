#ifndef RESPONSE_H
#define RESPONSE_H
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include "header.h"

enum class StatusType {
    ok = 200,
    created = 201,
    accepted = 202,
    no_content = 204,
    multiple_choices = 300,
    moved_permanently = 301,
    moved_temporarily = 302,
    not_modified = 304,
    bad_request = 400,
    unauthorized = 401,
    forbidden = 403,
    not_found = 404,
    internal_server_error = 500,
    not_implemented = 501,
    bad_gateway = 502,
    service_unavailable = 503
};

class Response {
public:
    std::vector<boost::asio::const_buffer> toBuffers();
    static Response getStockResp(StatusType currentStatus);
    void setStatus(StatusType newStatus);
    void setContent(std::string newContent);
    void setHeaders(std::vector<header> newHeaders);
    int getContentLength();
private:
    StatusType status_;
    std::vector<header> headers;
    std::string content;
};

#endif // RESPONSE_H
