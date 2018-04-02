/* 
    Sample solution code for Exercise 2
    socket_example.c  
*/

#include "socket_example.h"

int create_socket(struct addrinfo *my_addrinfo) {
    int domain = my_addrinfo->ai_family;
    int type = my_addrinfo->ai_socktype;
    int protocol = my_addrinfo->ai_protocol;

    socklen_t socket_fd = socket(domain, type, protocol);
    if (socket_fd == -1) {
        perror("socket create failed");
        return -1;
    }

    return socket_fd;
}