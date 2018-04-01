#include "../src/getaddrinfo_example.h"

int set_addrinfo(struct addrinfo **my_addrinfo) {
    char *port = "5678";
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    // Setting node to NULL combined with the AI_PASSIVE flag will
    // return us socket addresses that are suitable for a server that
    // will bind to a socket and accept connections
    int getaddr_status = getaddrinfo(NULL, port, &hints, my_addrinfo);
    if (getaddr_status != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(getaddr_status));
        return -1;
    }

    return 0;
}