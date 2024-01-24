// This header file contains all fucntions and constants you need to run this HTTP server.

//#define LINUX

#ifndef PUBLIC_INTERFACE_H
#define PUBLIC_INTERFACE_H

#ifdef LINUX
#include <netinet/in.h>
#endif
#ifdef WINDOWS
#include <ws2tcpip.h>
#include <winsock2.h>
#endif

#include <stdlib.h>

#include <stdbool.h>

// -------------
// | CONSTANTS |
// -------------

typedef enum {
    IPV4,
    IPV6
} Ip_v;

typedef enum {
    HTTP,
    HTTPS
} Http_v;

// --------------
// | STRUCTURES |
// --------------

#ifdef LINUX

typedef struct {
    struct sockaddr_in server_address;
    struct sockaddr_in6 server_address6;
    Ip_v ip_version;
    Http_v http_version;
    int port;
    int server_socket;
} Server;

#endif
#ifdef WINDOWS

typedef struct {
    struct sockaddr_in server_address;
    struct sockaddr_in6 server_address6;
    Ip_v ip_version;
    Http_v http_version;
    int port;
    SOCKET server_socket;
} Server;

#endif

typedef struct {
    struct sockaddr_in client_address;
    socklen_t client_address_length;
    int client_socket;
    int id;
} Client;

typedef struct {        // ALLOCATED 
    char* raw;          // yes
    size_t raw_size;    // no
    char* method;       // yes
    char* host;         // yes
    char* path;         // yes
    char* http_version; // no
    char** headers;     // yes (in one block -> <frst\0scnd\0thrd\0>)
    int headers_count;  // no
    char* body;         // yes
    bool is_valid;      // no
} Request;

// -------------
// | FUNCTIONS |
// -------------

bool init_server(Server* server, Ip_v ipVersion, Http_v httpVersion, const unsigned int port, int backlog);
void delete_server(Server* server);

bool init_request(Request* request, size_t max_request_size);
bool get_request(Request* request, Server* server, Client* client);
void delete_request(Request* request);

#endif

