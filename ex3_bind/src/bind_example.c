/*
    Exercise 3 - bind()

    In this exercise we'll bind to a socket (as identified by a socket file descriptor)
    using address info that we fetched previously using getaddrinfo().

    Create a method called "bind_socket" that takes a socket file descriptor
    and an addrinfo struct which is used to bind to the socket!
    
    For more information on the addrinfo struct, refer to the test for this file
    or Exercise 1.

    Run and look at the corresponding tests to see what needs to be fixed.

    Beej's guide: http://beej.us/guide/bgnet/html/multi/syscalls.html#bind
    man page: http://man7.org/linux/man-pages/man2/bind.2.html
*/

#include "bind_example.h"

int bind_socket(int socket_fildes, struct addrinfo *my_addrinfo) {
    (void) socket_fildes; // No-op to avoid compiler warnings around unused var
    (void) my_addrinfo; // No-op to avoid compiler warnings around unused var

    int bind_result = bind(0, 0, 0);
    if (bind_result == -1) {
        perror("bind failed");
    }

    return bind_result;
}
