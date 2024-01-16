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

bool init_server(Server* server, Ip_v ipVersion, Http_v httpVersion, const unsigned int port) {
    return l_init_server(server, ipVersion, httpVersion, port);
}

void delete_server(Server* server) {
    l_delete_server(server);
}

#endif

// -----------
// | WINDOWS |
// -----------

#ifdef WINDOWS

bool init_server(Server* server, Ip_v ipVersion, Http_v httpVersion, const unsigned int port) {
    return w_init_server(server, ipVersion, httpVersion, port);
}


void delete_server(Server* server) {
    w_delete_server(server);
}

#endif

// -----------------------
// | NO OS WAS SPECIFIED |
// -----------------------

#if !defined(LINUX) && !defined(WINDOWS)

bool init_server(Server* server, Ip_v ipVersion, Http_v httpVersion, const unsigned int port) {
    log_error("You have to rebuild system with either WINDOWS or LINUX spicified. Maybe you have changed Makefile?");
    exit(-1);
}


void delete_server(Server* server) {
    log_error("You have to rebuild system with either WINDOWS or LINUX spicified. Maybe you have changed Makefile?");
    exit(-1);
}

#endif
