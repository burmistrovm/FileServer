#include "serverhandler.h"
#include <iostream>

ServerHandler::ServerHandler(const std::string& root):
    docRoot(root) {
}

void ServerHandler::handle_request(const http_request& req, Response& resp) {
    std::string requestPath;
    if (!url_decode(req.uri, requestPath)) {
        resp = resp.getStockResp(StatusType::bad_request);
        return;
    }

    if (requestPath.empty() || requestPath[0] != '/' || requestPath.find("..") != std::string::npos) {
        resp = resp.getStockResp(StatusType::bad_request);
        return;
    }

    if (requestPath[requestPath.size() - 1] == '/') {
        requestPath += "index.html";
    }

    std::size_t last_slash_pos = requestPath.find_last_of("/");
    std::size_t last_dot_pos = requestPath.find_last_of(".");
    std::string extension;
    if (last_dot_pos != std::string::npos && last_dot_pos > last_slash_pos) {
        extension = requestPath.substr(last_dot_pos + 1);
    }

    std::string full_path = docRoot + requestPath;
    std::ifstream is(full_path.c_str(), std::ios::in | std::ios::binary);
    if (!is) {
        resp = resp.getStockResp(StatusType::not_found);
        return;
    }

    resp.setStatus(StatusType::ok);
    char buf[512];
    std::string content;
    std::vector<header> headers;
    while (is.read(buf, sizeof(buf)).gcount() > 0) {
        content.append(buf, is.gcount());
    }
    std::cout << content;
    resp.setContent(content);
    headers.resize(2);
    headers[0].name = "Content-Length";
    headers[0].value = std::to_string(resp.getContentLength());
    headers[1].name = "Content-Type";
    headers[1].value = extensionToType(extension);
    resp.setHeaders(headers);
}

bool ServerHandler::url_decode(const std::string& in, std::string& out) {
    out.clear();
    out.reserve(in.size());
    for (std::size_t i = 0; i < in.size(); ++i) {
        if (in[i] == '%') {
            if (i + 3 <= in.size()) {
                int value = 0;
                std::istringstream is(in.substr(i + 1, 2));
                if (is >> std::hex >> value) {
                    out += static_cast<char>(value);
                    i += 2;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else if (in[i] == '+') {
            out += ' ';
        } else {
            out += in[i];
        }
    }
    std::cout << out;
    return true;
}
