/*
    Exercise 5 - send()

    Run these tests using `make test`.
    These tests are a little more complicated than usual. They spin up a second thread
    that will listen and accept connections on a socket and attempt to send a message out.

    You will implement the send_message() method that this thread invokes to send a
    message back to our test client.

    Beej's guide: http://beej.us/guide/bgnet/html/multi/syscalls.html#sendrecv
    man page: http://man7.org/linux/man-pages/man2/sendmsg.2.html
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
#include <pthread.h>
#include "../../vendor/unity/unity.h"
#include "../src/send_example.h"

#define BUFSIZE 256

void *accepting_thread(void *socket_fildes) {
    struct sockaddr_storage connection_addr;
    socklen_t addr_size = sizeof connection_addr;

    int connected_socket_fildes = accept(*(socklen_t *) socket_fildes, (struct sockaddr *)&connection_addr, &addr_size);
    if (connected_socket_fildes == -1) {
        perror("accept failed");
    }

    // IMPLEMENT THIS
    send_message(connected_socket_fildes, "Sockets rule");

    return 0;
}

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

int client_connect_and_receive(char *port, char *message) {
    struct addrinfo *client_addrinfo;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    int getaddr_status = getaddrinfo("localhost", port, &hints, &client_addrinfo);
    if (getaddr_status != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(getaddr_status));
        return -1;
    }

    int socket_fildes = socket(client_addrinfo->ai_family, client_addrinfo->ai_socktype, client_addrinfo->ai_protocol);
    if (socket_fildes == -1) {
        perror("socket create failed");
        return socket_fildes;
    }

    int connect_result = connect(socket_fildes, client_addrinfo->ai_addr, client_addrinfo->ai_addrlen);
    if (connect_result == -1) {
        perror("connecting to socket failed");
        return connect_result;
    }
    freeaddrinfo(client_addrinfo);

    // Set a five second timeout for the recv
    // This will result in a "Resource temporarily unavailable" error
    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    setsockopt(socket_fildes, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

    char recv_buffer[BUFSIZE];
    int recv_size = recv(socket_fildes, recv_buffer, BUFSIZE, 0);
    if (recv_size == -1) {
        perror("recv failed");
        close(socket_fildes);
        return recv_size;
    }

    strcpy(message, recv_buffer);
    return recv_size;
}

void it_sends_a_message_to_connecting_clients(void)
{
    struct addrinfo *my_addrinfo;
    set_server_addrinfo(&my_addrinfo);

    int socket_fildes = socket(my_addrinfo->ai_family, my_addrinfo->ai_socktype, my_addrinfo->ai_protocol);
    if (socket_fildes == -1) {
        perror("socket create failed");
    }
    TEST_ASSERT_MESSAGE(socket_fildes != -1, "Test failed to create socket");

    int bind_result = bind(socket_fildes, my_addrinfo->ai_addr, my_addrinfo->ai_addrlen);
    if (bind_result == -1) {
        perror("binding socket failed");
    }
    freeaddrinfo(my_addrinfo);
    TEST_ASSERT_MESSAGE(bind_result != -1, "Test failed to bind to socket");

    int listen_result = listen(socket_fildes, 10);
    if (listen_result == -1) {
        perror("listen on socket failed");
    }
    TEST_ASSERT_MESSAGE(listen_result != -1, "Test failed to listen on socket");

    // Create a thread that will handle accepting the connection and will
    // invoke the `send_message()` function that you'll define
    pthread_t thread;
    pthread_create(&thread, NULL, *accepting_thread, (void *) &socket_fildes);

    char message[BUFSIZE];
    int recv_size = client_connect_and_receive("65001", (char *) &message);
    if (recv_size == -1) {
        perror("client_connect_and_receive failed");
        close(socket_fildes);
        TEST_ASSERT_MESSAGE(recv_size != -1, "Test client failed to connect and receive message from send_message()");
    }

    TEST_ASSERT_EQUAL_STRING_MESSAGE(
        "Sockets rule",
        &message,
        "Did not receive expected message back from send_message()"
    );

    close(socket_fildes);
}

int main(void)
{
    UnityBegin("test/test_send_example.c");

    RUN_TEST(it_sends_a_message_to_connecting_clients);

    UnityEnd();
    return 0;
}
