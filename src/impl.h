#ifndef IMPL_H
#define IMPL_H

#include "public_interface.h"

// ---------------------
// | WINDOWS FUNCTIONS |
// ---------------------
#ifdef WINDOWS


#endif

bool w_init_server(IPV ipVersion, HTTPV httpVersion, unsigned int port);

// -----------------------
// | GNU/LINUX FUNCTIONS |
// -----------------------
#ifdef LINUX


#endif

bool l_init_server(IPV ipVersion, HTTPV httpVersion, unsigned int port);

#endif
