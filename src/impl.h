#ifndef IMPL_H
#define IMPL_H

#include "public_interface.h"

// ---------------------
// | WINDOWS FUNCTIONS |
// ---------------------
#ifdef WINDOWS


#endif

bool w_init_server(Server* server, Ip_v ipVersion, Http_v httpVersion, unsigned int port);
void w_delete_server(Server* server);

// -----------------------
// | GNU/LINUX FUNCTIONS |
// -----------------------
#ifdef LINUX


#endif

bool l_init_server(Server* server, Ip_v ipVersion, Http_v httpVersion, unsigned int port);
void l_delete_server(Server* server);

#endif
