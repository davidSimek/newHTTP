#include "public_interface.h"

int main(void)
{
    Server server;
    init_server(&server, IPV4, HTTP, 1234);
    delete_server(&server);

    init_server(&server, IPV6, HTTP, 1234);
    delete_server(&server);

}
