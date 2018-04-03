/*
    Exercise 3 - bind()

    Run these tests using `make test`

    Beej's guide: http://beej.us/guide/bgnet/html/multi/syscalls.html#bind
    man page: http://man7.org/linux/man-pages/man2/bind.2.html
*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netdb.h>
#include "../../vendor/unity/unity.h"
#include "../src/bind_example.h"

int set_server_addrinfo(struct addrinfo **my_addrinfo) {
    char *port = "65001";
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    // See http://beej.us/guide/bgnet/html/multi/syscalls.html#getaddrinfo
    // or Exercise 1 for more information on getaddrinfo()
    int getaddr_status = getaddrinfo(NULL, port, &hints, my_addrinfo);
    if (getaddr_status != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(getaddr_status));
        return -1;
    }

    return 0;
}

void it_binds_to_the_given_socket_using_info_from_addrinfo(void)
{
    struct addrinfo *my_addrinfo;
    set_server_addrinfo(&my_addrinfo);

    int socket_fildes = socket(my_addrinfo->ai_family, my_addrinfo->ai_socktype, my_addrinfo->ai_protocol);
    if (socket_fildes == -1) {
        perror("socket create failed");
    }
    TEST_ASSERT_MESSAGE(socket_fildes != -1, "Test failed to create the socket");

    // Return value of -1 should denote that an error has occurred
    int bind_result = bind_socket(socket_fildes, my_addrinfo);
    TEST_ASSERT_MESSAGE(bind_result != -1, "bind_socket() failed to bind to the socket");

    // sockaddr_in will only work if you're using IPV4
    // Should be the case since we specified hints.ai_family = AF_INET above
    // Use sockaddr_in6 if you're using IPV6
    struct sockaddr_in bound_sockaddr;
    socklen_t bound_sockaddr_size = sizeof(struct sockaddr_in);

    // http://man7.org/linux/man-pages/man2/getsockname.2.html
    int getsockname_result = getsockname(socket_fildes, (struct sockaddr *)&bound_sockaddr, &bound_sockaddr_size);
    if (getsockname_result == -1) {
        perror("getsockname failed");
    }
    TEST_ASSERT_MESSAGE(getsockname_result != -1, "Test failed to get information about the bound socket");

    // Test that we bound the socket to the port specified in my_addrinfo
    // GOTCHA: `sin_port` is in "network byte order". We need to convert to host byte order using ntohs
    // ntohs = network to host short (uint16_t in this case)
    // http://man7.org/linux/man-pages/man3/ntohl.3p.html
    int converted_port = ntohs(bound_sockaddr.sin_port);
    TEST_ASSERT_EQUAL_INT_MESSAGE(65001, converted_port, "bind_socket() did not bind to the correct port");

    freeaddrinfo(my_addrinfo);
    close(socket_fildes);
}

int main(void)
{
    UnityBegin("test/test_bind_example.c");

    RUN_TEST(it_binds_to_the_given_socket_using_info_from_addrinfo);

    UnityEnd();
    return 0;
}
