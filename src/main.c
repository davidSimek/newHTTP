#include "logs.h"
#include "public_interface.h"

int main(void)
{
    Server server;
    Client client;
    Request request;

    init_server(&server, IPV4, HTTP, 1234, 10);
    log_info("init_server() called");

    init_request(&request, 1024);
    log_info("init_request() called");

    log_info("calling get_request()");
    get_request(&request, &server, &client);

    delete_request(&request);
    delete_server(&server);
}
