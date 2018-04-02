/*
    Sample solution code for Exercise 4
    listen_and_accept_example.c
*/

#include "listen_and_accept_example.h"

int listen_and_accept(int socket_fildes, int backlog_size) {
    int listen_result = listen(socket_fildes, backlog_size);
    if (listen_result == -1) {
        perror("listen failed");
    }

    struct sockaddr_storage connection_addr;
    socklen_t addr_size = sizeof connection_addr;

    int accept_result = accept(socket_fildes, (struct sockaddr *)&connection_addr, &addr_size);;
    if (accept_result == -1) {
        perror("accept failed");
    }

    return accept_result;
}