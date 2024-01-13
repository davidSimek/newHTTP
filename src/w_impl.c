#include <stdio.h>
#include <stdbool.h>

#include "impl.h"
#include "public_interface.h"

bool w_init_server(IPV ipVersion, HTTPV httpVersion, unsigned int port) {
    printf("init server for Windows\n");
    return false;
};
