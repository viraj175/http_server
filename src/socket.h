#ifndef SOCKET_H
#define SOCKET_H

#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>

typedef struct socket_ {
    struct sockaddr_in addr;
    int socket_fd;
} http_socket_t;

void create_socket(http_socket_t *sock);

#endif // !SOCKET_H
