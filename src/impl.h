#ifndef IMPL_H
#define IMPL_H

#include <stdlib.h>
#include <string.h>

#include "public_interface.h"

// ---------------------
// | WINDOWS FUNCTIONS |
// ---------------------
#ifdef WINDOWS

bool w_init_server(Server* server, Ip_v ipVersion, Http_v httpVersion, unsigned int port, int backlog);
void w_delete_server(Server* server);
bool w_get_request(Request* request, Server* server, Client* client);
void w_init_client(Client* client);

#endif

// -----------------------
// | GNU/LINUX FUNCTIONS |
// -----------------------
//
#ifdef LINUX

bool l_init_server(Server* server, Ip_v ipVersion, Http_v httpVersion, unsigned, int port);
void l_delete_server(Server* server);
bool l_get_request(Request* request, Server* server, Client* client);
void l_init_client(Client* client);



#endif

// ---------------------
// | INDEPENDENT ON OS |
// ---------------------

void i_parse_request(char* data, Request* request);
void i_delete_request(Request* request);

#endif
