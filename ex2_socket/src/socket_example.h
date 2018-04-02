#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#ifndef SOCKET_EXAMPLE_H
#define SOCKET_EXAMPLE_H

int create_socket(struct addrinfo *my_addrinfo);

#endif
