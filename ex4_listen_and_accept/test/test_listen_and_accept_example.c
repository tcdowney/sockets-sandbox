/*
    Exercise 4 - listen() and accept()

    Run these tests using `make test`

    Beej's guides:
        http://beej.us/guide/bgnet/html/multi/syscalls.html#listen
        http://beej.us/guide/bgnet/html/multi/syscalls.html#accept
    man pages:
        http://man7.org/linux/man-pages/man2/listen.2.html
        http://man7.org/linux/man-pages/man2/accept.2.html
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
#include <fcntl.h>
#include "../../vendor/unity/unity.h"
#include "../src/listen_and_accept_example.h"

int set_server_addrinfo(struct addrinfo **my_addrinfo) {
    char *port = "65001";
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_UNSPEC;
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

void it_listens_and_accepts_connections(void)
{
    struct addrinfo *my_addrinfo;
    set_server_addrinfo(&my_addrinfo);

    int socket_fildes = socket(my_addrinfo->ai_family, my_addrinfo->ai_socktype, my_addrinfo->ai_protocol);
    if (socket_fildes == -1) {
        perror("socket create failed");
    }
    TEST_ASSERT_MESSAGE(socket_fildes != -1, "Test failed to create the socket");

    // Make socket non-blocking so that this test does not block forever on accept()
    int socket_flags = fcntl(socket_fildes, F_GETFL, 0);
    if (socket_flags == -1) {
        perror("retrieving socket flags failed");
    }
    TEST_ASSERT_MESSAGE(socket_flags != -1, "Test failed to retrieve socket flags");
    socket_flags |= O_NONBLOCK;

    socket_flags = fcntl(socket_fildes, F_SETFL, socket_flags);
    if (socket_flags == -1) {
        perror("setting socket to nonblocking mode failed");
    }
    TEST_ASSERT_MESSAGE(socket_flags != -1, "Test failed to set the O_NONBLOCK flag");

    int bind_result = bind(socket_fildes, my_addrinfo->ai_addr, my_addrinfo->ai_addrlen);
    if (bind_result == -1) {
        perror("binding socket failed");
    }
    TEST_ASSERT_MESSAGE(bind_result != -1, "Test failed to bind to the socket");

    int backlog_size = 10;
    listen_and_accept(socket_fildes, backlog_size);

    // These errors are raised when "The socket is marked nonblocking and no connections are present to be accepted."
    // Since we purposefully put the socket in non-blocking mode, these are expected and are a roundabout way of testing
    // that we were listening and accepting correctly
    bool no_connections_present_error_occurred = (errno == EAGAIN) || (errno == EWOULDBLOCK);
    TEST_ASSERT_MESSAGE(
        no_connections_present_error_occurred,
        "listen_and_accept() did not result in a EAGAIN or EWOULDBLOCK error"
    );

    freeaddrinfo(my_addrinfo);
    close(socket_fildes);
}

int main(void)
{
    UnityBegin("test/test_listen_and_accept_example.c");

    RUN_TEST(it_listens_and_accepts_connections);

    UnityEnd();
    return 0;
}
