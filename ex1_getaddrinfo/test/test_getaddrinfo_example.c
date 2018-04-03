/*
    Exercise 1 - getaddrinfo()

    Run these tests using `make test`

    References:
    struct addrinfo {
        int              ai_flags;
        int              ai_family;
        int              ai_socktype;
        int              ai_protocol;
        socklen_t        ai_addrlen;
        struct sockaddr *ai_addr;
        char            *ai_canonname;
        struct addrinfo *ai_next;
    };

    Beej's guide: http://beej.us/guide/bgnet/html/multi/syscalls.html#getaddrinfo
    man page: http://man7.org/linux/man-pages/man3/getaddrinfo.3.html
*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../vendor/unity/unity.h"
#include "../src/getaddrinfo_example.h"

void it_returns_0_when_no_errors_occur(void)
{
    struct addrinfo *my_addrinfo;
    int ret;
    ret = set_addrinfo(&my_addrinfo);
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, ret, "set_addrinfo() did not return 0");

    freeaddrinfo(my_addrinfo);
}

void it_does_not_specify_an_address_family(void)
{
    struct addrinfo *my_addrinfo;
    set_addrinfo(&my_addrinfo);

    bool is_ipv4_or_ipv6 = (my_addrinfo->ai_family == AF_INET) || (my_addrinfo->ai_family == AF_INET6);
    TEST_ASSERT_MESSAGE(is_ipv4_or_ipv6, "Address familly is not IPv4 or IPv6");

    freeaddrinfo(my_addrinfo);
}

void it_specifies_a_tcp_stream_socket(void)
{
    struct addrinfo *my_addrinfo;
    set_addrinfo(&my_addrinfo);

    TEST_ASSERT_EQUAL_INT_MESSAGE(SOCK_STREAM, my_addrinfo->ai_socktype, "Socket type is not STREAM");

    freeaddrinfo(my_addrinfo);
}

void it_sets_the_ai_passive_flag(void)
{
    struct addrinfo *my_addrinfo;
    set_addrinfo(&my_addrinfo);

    bool ai_passive_flag_present = (my_addrinfo->ai_flags & AI_PASSIVE) == AI_PASSIVE;
    TEST_ASSERT_MESSAGE(ai_passive_flag_present, "AI_PASSIVE flag is not present");

    freeaddrinfo(my_addrinfo);
}

int main(void)
{
    UnityBegin("test/test_getaddrinfo_example.c");

    RUN_TEST(it_returns_0_when_no_errors_occur);
    RUN_TEST(it_does_not_specify_an_address_family);
    RUN_TEST(it_specifies_a_tcp_stream_socket);
    RUN_TEST(it_sets_the_ai_passive_flag);

    UnityEnd();
    return 0;
}