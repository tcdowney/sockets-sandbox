/*
    Exercise 6 - Parrot Server

    Implement a simple "Parrot" server that listens on a given port and echoes (send)
    back any messages that it receives (recv).

    Feel free to go back and look at the functions you've implemented in the earlier
    exercises and draw inspiration from some of the test code.

    Good luck!

    Beej's guide: http://beej.us/guide/bgnet/html/multi/clientserver.html#simpleserver
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

    sprintf(port_string, "%d", port);

    /* YOUR CODE HERE */
    /* BIND/LISTEN/ETC */

    while (1) {
        printf("hello ther port: %d\n", port);
        /* YOUR CODE HERE */
        /* ACCEPT/RECV/SEND/ETC */
    }
}