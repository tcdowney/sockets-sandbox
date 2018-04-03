/*
    Sample solution code for Exercise 6
    parrot_server.c
*/

#include "parrot_server.h"

#define BUFSIZE 256
#define MESSAGE_BUFSIZE 4096
#define DEFAULT_PORT 9001
#define MAX_CONNECTIONS 10

#define HELP_TEXT                                                \
"usage:\n"                                                       \
"  parrot_server [options]\n"                                    \
"options:\n"                                                     \
"  -p                   Port (Default: 9001)\n"                  \
"  -h                   Display this help message\n"             \

static struct option option_definitions[] = {
  {"port",          required_argument,      NULL,           'p'},
  {"help",          no_argument,            NULL,           'h'},
  {NULL,            0,                      NULL,             0}
};

int main(int argc, char **argv) {
    int  option_char;
    int  port = DEFAULT_PORT;
    char port_string[BUFSIZE];

    while ((option_char = getopt_long(argc, argv, "p:m:hx", option_definitions, NULL)) != -1) {
        switch (option_char) {
            case 'h': // help
                printf("%s \n", HELP_TEXT);
                exit(0);
                break;
            case 'p': // port
                port = atoi(optarg);
                break;
            default:
                fprintf(stderr, "%s \n", HELP_TEXT);
                exit(1);
        }
    }

    // Disable buffering for the sake of this exercise so that we don't have to worry about it
    // https://www.gnu.org/software/libc/manual/html_node/Controlling-Buffering.html
    setbuf(stdout, NULL);

    // Validate port is reasonable
    // https://en.wikipedia.org/wiki/Registered_port
    if ((port < 1024) || (port > 65535)) {
        fprintf(stderr, "Invalid port number (%d). Port must be between 1024-65535\n", port);
        exit(1);
    }

    // Convert port back into a string for use by getaddrinfo()
    sprintf(port_string, "%d", port);

    struct addrinfo *server_addrinfo;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int getaddr_status = getaddrinfo(NULL, port_string, &hints, &server_addrinfo);
    if (getaddr_status != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(getaddr_status));
        exit(1);
    }

    int socket_fildes;
    struct addrinfo *addrinfo_p;

    // Loop through all of the addrinfos returned by getaddrinfo() and bind to the first one that works
    for(addrinfo_p = server_addrinfo; addrinfo_p != NULL; addrinfo_p = addrinfo_p->ai_next) {
        if ((socket_fildes = socket(addrinfo_p->ai_family, addrinfo_p->ai_socktype, addrinfo_p->ai_protocol)) == -1) {
            perror("socket failed");
            continue;
        }

        // Reuse the socket to avoid "Address already in use" errors
        // See http://beej.us/guide/bgnet/html/multi/syscalls.htm
        int please_reuse=1;
        if (setsockopt(socket_fildes, SOL_SOCKET, SO_REUSEADDR, &please_reuse, sizeof please_reuse) == -1) {
            perror("setsockopt failed");
            exit(1);
        }

        if (bind(socket_fildes, addrinfo_p->ai_addr, addrinfo_p->ai_addrlen) == -1) {
            close(socket_fildes);
            perror("bind failed");
            continue;
        }

        break;
    }

    // Do not need this anymore, let it go :)
    freeaddrinfo(server_addrinfo);

    // If this is NULL it means we went through all of the addrinfo structs
    // that getaddrinfo() returned and were not able to bind to any of them
    if (addrinfo_p == NULL)  {
        perror("failed to successfully bind to results of getaddrinfo()");
        exit(1);
    }

    if (listen(socket_fildes, MAX_CONNECTIONS) == -1) {
        perror("listen on socket failed");
        exit(1);
    }

    printf("Listening on port: %d\n", port);
    while (1) {
        struct sockaddr_storage connection_addr;
        socklen_t addr_size = sizeof connection_addr;

        int connected_socket_fildes = accept(socket_fildes, (struct sockaddr *)&connection_addr, &addr_size);
        if (connected_socket_fildes == -1) {
            perror("accept failed");
            continue;
        }

        char recv_buffer[MESSAGE_BUFSIZE];
        memset(&recv_buffer, 0, sizeof(recv_buffer));

        ssize_t recv_size;
        recv_size = recv(connected_socket_fildes, recv_buffer, MESSAGE_BUFSIZE, 0);
        if (recv_size == -1) {
            perror("recv error");
            close(connected_socket_fildes);
            continue;
        }

        ssize_t send_size;
        send_size = send(connected_socket_fildes, recv_buffer, recv_size, 0);
        if (send_size == -1) {
            perror("send error");
            close(connected_socket_fildes);
            continue;
        }

        close(connected_socket_fildes);
    }
}