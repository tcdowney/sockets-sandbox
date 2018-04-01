/*
    Exercise 1 - getaddrinfo()

    In this exercise we'll create a method called set_addrinfo() that
    will take an unitialized addrinfo struct that use getaddrinfo()
    to populate it. The addrinfo struct is not required, but will make
    calling other socket related methods easier.
    
    In this example we'll configure the addrinfo so that it will be suitable
    for later creating a socket that we can bind to and accept connections on.

    The skeleton code below is currently misconfigured. Refer to the documentation
    and Beej's guide to give getaddrinfo() the correct hints to pass our tests!

    Beej's guide: http://beej.us/guide/bgnet/html/multi/syscalls.html#getaddrinfo
    man page: http://man7.org/linux/man-pages/man3/getaddrinfo.3.html
*/

#include "getaddrinfo_example.h"

int set_addrinfo(struct addrinfo **my_addrinfo) {
    char *port = "5678"; // Arbitrary port
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));

    hints.ai_socktype = SOCK_DGRAM;

    // Setting node to NULL combined with the AI_PASSIVE flag will
    // return us socket addresses that are suitable for a server that
    // will bind to a socket and accept connections
    int getaddr_status = getaddrinfo(NULL, port, &hints, my_addrinfo);
    if (getaddr_status != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(getaddr_status));
        return -1;
    }

    return -1; // FIXME!
}