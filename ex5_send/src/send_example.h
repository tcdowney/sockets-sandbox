#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#ifndef SEND_EXAMPLE_H
#define SEND_EXAMPLE_H

int send_message(int socket_fildes, char *message);

#endif
