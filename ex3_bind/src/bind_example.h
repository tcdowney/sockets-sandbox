#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#ifndef GETADDRINFO_EXAMPLE_H
#define GETADDRINFO_EXAMPLE_H

int bind_socket(int socket_fildes, struct addrinfo *my_addrinfo);

#endif
