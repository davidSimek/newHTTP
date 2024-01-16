//#define WINDOWS
#ifdef WINDOWS

#include <stdbool.h>
#include <stdlib.h>

#include "impl.h"
#include "public_interface.h"
#include "logs.h"

bool w_init_server(Server* server, Ip_v ipVersion, Http_v httpVersion, unsigned int port) {
    log_info("init server for GNU/Linux");

    // Initiate Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        log_error("Couldn't initiate Winsock.");
        return false;
    }

    // Create a socket
    if (httpVersion == HTTP)
        server->server_socket = socket(AF_INET, SOCK_STREAM, 0);
    else {
        server->server_socket = socket(AF_INET6, SOCK_STREAM, 0);
    } 

    if (server->server_socket == -1) {
        log_error("Couldn't create server socket.");
        WSACleanup();
        return false;
    }

    // Bind the socket
    if (httpVersion == HTTP) {
        server->server_address.sin_family = AF_INET;
        server->server_address.sin_addr.s_addr = INADDR_ANY;
        server->server_address.sin_port = htons(port);
    } else {
        memset(&server->server_address6, 0, sizeof(server->server_address6));
        
        server->server_address6.sin6_family = AF_INET6;
        server->server_address6.sin6_addr = in6addr_any;
        server->server_address6.sin6_port = htons(port);     }
    
    if (bind(server->server_socket, (struct sockaddr*)&server->server_address, sizeof(server->server_address)) == SOCKET_ERROR) {
        log_error("Couldn't bind the socket.");
        closesocket(server->server_socket);
        WSACleanup();
        return false;
    }

    return true;
};

void w_delete_server(Server* server) {
    log_info("delete server for Windows");
    closesocket(server->server_socket);
    WSACleanup();
}

#endif
