#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include "socket.h"
#include "request.h"
#include "response.h"

#define MESSAGE_SIZE 1024

int
main()
{
    http_socket_t sock;
    create_socket(&sock);

    int opt = 1;
    setsockopt(sock.socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));

    if (bind(sock.socket_fd, (struct sockaddr *)&sock.addr, sizeof(sock.addr)) == -1)
    {
        perror("bind failed");   
        exit(EXIT_FAILURE);
    }

    listen(sock.socket_fd, 5);
    printf("listening on port 8080!\n");

    while(1)
    {
        int client_fd = accept(sock.socket_fd, NULL, NULL);
        if (client_fd == -1)
        {
            perror("socket faild");
            exit(EXIT_FAILURE);
        }

        char raw_request[REQUEST_SIZE];
        int n = recv(client_fd, raw_request, REQUEST_SIZE, 0);
        if (n == -1)
        {
            perror("recv failed");
            exit(EXIT_FAILURE);
        }
        raw_request[n] = '\0';

        request_t request = {"", "", ""};
        char message[MESSAGE_SIZE];

        parse_request(&request, raw_request);
        send_response(client_fd, message, MESSAGE_SIZE, request.path);

        close(client_fd);
    }

    close(sock.socket_fd);
    return 0;
}
