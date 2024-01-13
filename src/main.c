#include "public_interface.h"
#include "logs.h"

#include <stdio.h>

int main(void)
{
    puts("HI");
    init_server(IPV4, HTTP, 1234);
    log_error("HAHAH");
    log_info("UUUU");
}
