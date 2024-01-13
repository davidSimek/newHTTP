#include <stdbool.h>
#include <stdio.h>

#include "impl.h"

#include "public_interface.h"

bool init_server(IPV ipVersion, HTTPV httpVersion, const unsigned int port) {
    
    #ifdef LINUX
    
    return l_init_server(ipVersion, httpVersion, port);

    #endif
    #ifdef WINDOWS

    return w_init_server(ipVersion, httpVersion, port);

    #endif

    return false;
}
