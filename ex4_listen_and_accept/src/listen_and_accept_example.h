#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#ifndef LISTED_AND_ACCEPT_EXAMPLE_H
#define LISTED_AND_ACCEPT_EXAMPLE_H

int listen_and_accept(int socket_fildes, int backlog_size);

#endif
