//#define LINUX
#ifdef LINUX

#include <stdbool.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

#include <string.h>
#include "public_interface.h"
#include "impl.h"
#include "logs.h"

bool l_init_server(Server* server, Ip_v ipVersion, Http_v httpVersion, unsigned int port) {
    log_info("init server for GNU/Linux");

    // Create a socket
    if (httpVersion == HTTP)
        server->server_socket = socket(AF_INET, SOCK_STREAM, 0);
    else {
        server->server_socket = socket(AF_INET6, SOCK_STREAM, 0);
    } 

    if (server->server_socket == -1) {
        log_error("Couldn't create server socket.");
        return false;
    }

    // Bind the socket
    if (httpVersion == HTTP) {
        server->server_address.sin_family = AF_INET;
        server->server_address.sin_addr.s_addr = INADDR_ANY;
        server->server_address.sin_port = htons(port);
    } else {
        memset(&server->server_address6, 0, sizeof(server->server_address6)); 
    }
    server->server_address.sin_addr.s_addr = INADDR_ANY;
    server->server_address.sin_port = htons(port);

    if (bind(server->server_socket, (struct sockaddr*)&server->server_address, sizeof(server->server_address)) == -1) {
        log_error("Couldn't bind the socket.");
        close(server->server_socket);
        return false;
    }

    return true;
}

void l_delete_server(Server* server) {
    log_info("delete server for GNU/Linux");
    close(server->server_socket);
}

#endif
