/*
    Exercise 2 - socket()

    In this exercise we'll create a socket -- or at least a file descriptor
    for a socket!

    Create a method called "create_socket" that takes an addrinfo struct
    and uses it to create a socket! For more information on the addrinfo
    struct, refer to the test for this file or Exercise 1.

    Run and look at the corresponding tests to see what needs to be fixed.

    Beej's guide: http://beej.us/guide/bgnet/html/multi/syscalls.html#socket
    man page: http://man7.org/linux/man-pages/man2/socket.2.html
*/

#include "socket_example.h"

int create_socket(struct addrinfo *my_addrinfo) {
    (void) my_addrinfo; // No-op to avoid compiler warnings around unused var

    socklen_t socket_fd = socket(0, 0, 0);
    if (socket_fd == -1) {
        perror("socket create failed");
        return -1;
    }

    return -1;
}