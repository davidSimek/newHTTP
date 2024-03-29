// #define LINUX
#ifdef LINUX


// delete this !!!!!
#include <stdio.h>

#include <stdbool.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include <string.h>
#include "public_interface.h"
#include "impl.h"
#include "logs.h"

bool l_init_server(Server* server, Ip_v ipVersion, Http_v httpVersion, unsigned int port, int backlog) {
    log_info("starting server for GNU/Linux");

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

    int reuse = 1;
    if (setsockopt(server->server_socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse)) < 0) {
        log_error("Couldn't set setsockopt(SO_REUSEADDR).");
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

    if (listen(server->server_socket, backlog) == -1) {
        log_error("Server couldn't start listening");
        return false;
    }

    return true;
}

void l_delete_server(Server* server) {
    log_info("delete server for GNU/Linux");
    close(server->server_socket);
}

bool l_get_request(Request* request, Server* server, Client* client) {
   
    if ((client->client_socket = accept(server->server_socket, (struct sockaddr *)&client->client_address, &client->client_address_length)) == -1) {
            log_error("Couldn't accept request.");
            exit(EXIT_FAILURE);
    }
    printf("Connection accepted from %s:%d\n", inet_ntoa(client->client_address.sin_addr), ntohs(client->client_address.sin_port));

    log_info(request->raw);

    int bytes_recieved = recv(client->client_socket, request->raw, request->raw_size, 0);

    if (bytes_recieved == -1) {
        log_error("Couldn't recieve data.");
        return false;
    }

    i_parse_request(request);
    i_preview_request(request);

    // delete this !!!!!
    const char* response = "lol man";
    size_t responseLength = strlen(response);
    send(client->client_socket, response, responseLength, 0); 
    close(client->client_socket);
    
    return true;
}

 #endif
