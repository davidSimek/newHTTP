// #define LINUX

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "impl.h"
#include "logs.h"

#include "public_interface.h"

// -------------
// | GNU/LINUX |
// -------------

#ifdef LINUX

bool init_server(Server* server, Ip_v ipVersion, Http_v httpVersion, const unsigned int port, int backlog) {
    return l_init_server(server, ipVersion, httpVersion, port, backlog);
}


void delete_server(Server* server) {
    l_delete_server(server);
}

bool init_request(Request* request, size_t max_request_size) {
    request->raw = (char*)malloc(max_request_size);
    if (request->raw_size == 0) {
        log_error("Couldn't create request buffer");
        return false;
    }
    request->raw_size = max_request_size;
    return true;
}

bool get_request(Request* request, Server* server, Client* client) {
    l_get_request(request, server, client);
}

void delete_request(Request* request) {
    i_delete_request(request);
}


#endif

// -----------
// | WINDOWS |
// -----------

#ifdef WINDOWS

bool init_server(Server* server, Ip_v ipVersion, Http_v httpVersion, const unsigned int port, int backlog) {
    return w_init_server(server, ipVersion, httpVersion, port, backlog);
}


void delete_server(Server* server) {
    w_delete_server(server);
}

bool init_request(Request* request, size_t max_request_size) {
    request->raw = (char*)malloc(max_request_size);
    if (request->raw_size == 0) {
        log_error("Couldn't create request buffer");
        return false;
    }
    request->raw_size = max_request_size;
    return true;
}

bool get_request(Request* request, Server* server, Client* client) {
    w_get_request(request, server, client);
}

void delete_request(Request* request) {
    i_delete_request(request);
}

#endif

// -----------------------
// | NO OS WAS SPECIFIED |
// -----------------------

#if !defined(LINUX) && !defined(WINDOWS)

bool init_server(Server* server, Ip_v ipVersion, Http_v httpVersion, const unsigned int port, int backlog) {
    log_error("You have to rebuild system with either WINDOWS or LINUX spicified. Maybe you have changed Makefile?");
    exit(-1);
}


void delete_server(Server* server) {
    log_error("You have to rebuild system with either WINDOWS or LINUX spicified. Maybe you have changed Makefile?");
    exit(-1);
}

#endif
