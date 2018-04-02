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

int listen_and_accept(int socket_fildes, int backlog_size);

#endif
