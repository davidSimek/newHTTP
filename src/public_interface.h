// This header file contains all fucntions and constants you need to run this HTTP server.

//#define LINUX

#ifndef PUBLIC_INTERFACE_H
#define PUBLIC_INTERFACE_H

#ifdef LINUX
#include <netinet/in.h>
#endif
#ifdef WINDOWS
#pragma comment(lib, "ws2_32.lib")
#include <ws2tcpip.h>
#include <winsock2.h>
#endif

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

// -------------
// | FUNCTIONS |
// -------------

bool init_server(Server* server, Ip_v ipVersion, Http_v httpVersion, const unsigned int port);
void delete_server(Server* server);

#endif

