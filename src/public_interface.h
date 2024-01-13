// This header file contains all fucntions and constants you need to run this HTTP server.

#ifndef PUBLIC_INTERFACE_H
#define PUBLIC_INTERFACE_H

#include <stdbool.h>

// -------------
// | CONSTANTS |
// -------------

typedef enum {
    IPV4,
    IPV6
} IPV;

typedef enum {
    HTTP,
    HTTPS
} HTTPV;

// -------------
// | FUNCTIONS |
// -------------

bool init_server(IPV ipVersion, HTTPV httpVersion, const unsigned int port);

#endif

