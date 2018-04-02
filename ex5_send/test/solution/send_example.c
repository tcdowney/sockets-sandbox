/*
    Sample solution code for Exercise 5
    send_example.c
*/

#include "send_example.h"

int send_message(socklen_t socket_fildes, char *message) {
    int send_size;
    send_size = send(socket_fildes, message, strlen(message), 0);
    if (send_size == -1) {
        perror("send error");
    }

    return send_size;
}