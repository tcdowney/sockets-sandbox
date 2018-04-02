/*
    Exercise 5 - send()

    Implement send_message() which sends a string to clients on the given
    socket.

    Beej's guide: http://beej.us/guide/bgnet/html/multi/syscalls.html#sendrecv
    man page: http://man7.org/linux/man-pages/man2/sendmsg.2.html
*/

#include "send_example.h"

int send_message(int socket_fildes, char *message) {
    (void) socket_fildes; // No-op to avoid compiler warnings around unused var
    (void) message; // No-op to avoid compiler warnings around unused var

    return -1; // FIXME!!
}
