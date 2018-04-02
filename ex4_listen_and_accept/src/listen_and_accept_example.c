/*
    Exercise 4 - listen() and accept()

    In this exercise we'll listen() to an already bound socket and attempt to
    accept() connections on it.

    Create a method called "listen_and_accept" that takes a socket file descriptor
    and a backlog size (max ammount of queued up potential connections) that will
    listen on the socket and attempt to accept connections.

    The tests have set this socket to be non-blocking so accept() will not block.

    Run and look at the corresponding tests to see what needs to be fixed.

    Beej's guides:
        http://beej.us/guide/bgnet/html/multi/syscalls.html#listen
        http://beej.us/guide/bgnet/html/multi/syscalls.html#accept
    man pages:
        http://man7.org/linux/man-pages/man2/listen.2.html
        http://man7.org/linux/man-pages/man2/accept.2.html
*/

#include "listen_and_accept_example.h"

int listen_and_accept(int socket_fildes, int backlog_size) {
    (void) socket_fildes; // No-op to avoid compiler warnings around unused var
    (void) backlog_size; // No-op to avoid compiler warnings around unused var

    // listen() here!

    // Helpful structs for accepting connections
    // struct sockaddr_storage connection_addr;
    // socklen_t addr_size = sizeof connection_addr;

    // accept() here!

    return -1; // FIXME!!
}
