/*
    Beej's guide: http://beej.us/guide/bgnet/html/multi/syscalls.html#getaddrinfo
    man page: http://man7.org/linux/man-pages/man3/getaddrinfo.3.html
    
    The getaddrinfo() method takes a few parameters and will populate
    an addrinfo struct that we will use in later socket related calls.

    In this example we'll configure it in "server mode" and provide it some hints
    to help accomplish that.

    int getaddrinfo(const char *node, const char *service,
        const struct addrinfo *hints,
        struct addrinfo **res);
*/

#include "getaddrinfo_example.h"

int set_addrinfo(struct addrinfo **my_addrinfo) {
    char *port = "5678";
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