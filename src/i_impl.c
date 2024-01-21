#include "impl.h"
#include "logs.h"
#include <stdio.h>

void i_parse_request(char* data, Request* request) {
    log_info("parsing");
    request->headers = (char**)malloc(2 * sizeof(char*)); 
    request->headers[0] = (char*)malloc(sizeof(char*) * 6);
    request->headers[1] = request->headers[0] + 3;
    log_info("headers allocated");
    memcpy(request->headers[0], "no", 3);
    log_info("first header set");
    memcpy(request->headers[1], "no", 3);
    log_info("headers set");
    request->headers_count = 2;
    request->http_version = "HTTP3";
    request->path = (char*)malloc(sizeof(char) * 6);
    memcpy(request->path, "/hello", 6);
    request->method = "GET";
    request->body = (char*)malloc(sizeof(char) * 6);
    memcpy(request->body, "nanan", 6);
    request->host = (char*)malloc(sizeof(char) * 5);
    memcpy(request->host, "hello", 5);
}

void i_delete_request(Request* request) {
    free(request->host);
    request->host = 0;
    free(request->path);
    request->path = 0;
    free(request->headers[0]);
    request->headers = 0;
    free(request->body);
    request->body = 0;
    free(request->raw);
    request->raw = 0;
}
