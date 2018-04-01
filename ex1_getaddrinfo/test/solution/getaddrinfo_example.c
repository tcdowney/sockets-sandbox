/* 
    Sample solution code for Exercise 1
    getaddrinfo_example.c  
*/

#include "getaddrinfo_example.h"

int set_addrinfo(struct addrinfo **my_addrinfo) {
    char *port = "5678";  // Arbitrary port
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int getaddr_status = getaddrinfo(NULL, port, &hints, my_addrinfo);
    if (getaddr_status != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(getaddr_status));
        return -1;
    }

    return 0;
}