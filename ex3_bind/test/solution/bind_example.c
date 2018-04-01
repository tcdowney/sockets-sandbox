/*
    Sample solution code for Exercise 3
    bind_example.c
*/

#include "bind_example.h"

int bind_socket(int socket_fildes, struct addrinfo *my_addrinfo) {
    int bind_result = bind(socket_fildes, my_addrinfo->ai_addr, my_addrinfo->ai_addrlen);
    if (bind_result == -1) {
        perror("bind failed");
    }

    return bind_result;
}
