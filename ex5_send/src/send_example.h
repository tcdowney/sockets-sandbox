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

int send_message(socklen_t socket_fildes, char *message);

#endif
