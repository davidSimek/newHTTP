#include <stdio.h>
#include <stdbool.h>

#include "public_interface.h"
#include "impl.h"

bool l_init_server(IPV ipVersion, HTTPV httpVersion, unsigned int port) {
    printf("init server for GNU/Linux\n");
    return false;
}
