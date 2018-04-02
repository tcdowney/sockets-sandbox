/*
    Exercise 2 - socket()

    Run these tests using `make test`

    Beej's guide: http://beej.us/guide/bgnet/html/multi/syscalls.html#socket
    man page: http://man7.org/linux/man-pages/man2/socket.2.html
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
#include "../src/socket_example.h"

int set_server_addrinfo(struct addrinfo **my_addrinfo) {
    char *port = "5678";
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

void it_returns_a_socket_file_descriptor_when_given_addrinfo(void)
{
    struct addrinfo *my_addrinfo;
    set_server_addrinfo(&my_addrinfo);

    socklen_t socket_file_descriptor;
    socket_file_descriptor = create_socket(my_addrinfo);

    // Return value of -1 should denote that an error has occurred
    TEST_ASSERT(socket_file_descriptor != -1);

    // Get information about the file descriptor using fstat
    // http://man7.org/linux/man-pages/man3/fstat.3p.html
    struct stat file_stat;
    if (fstat(socket_file_descriptor, &file_stat) != 0) {
        perror("fstat failed");
    }

    // S_ISSOCK is a macro that tests if a given file descriptor is a socket
    // http://pubs.opengroup.org/onlinepubs/009695399/basedefs/sys/stat.h.html
    TEST_ASSERT(S_ISSOCK(file_stat.st_mode));

    freeaddrinfo(my_addrinfo);
    close(socket_file_descriptor);
}

int main(void)
{
    UnityBegin("test/test_socket_example.c");

    RUN_TEST(it_returns_a_socket_file_descriptor_when_given_addrinfo);

    UnityEnd();
    return 0;
}