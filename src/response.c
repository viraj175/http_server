#include "response.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <fcntl.h>

void
send_response(int client_fd, char *message)
{
    char response[1024];
    snprintf(response,  sizeof(response), "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: %zu\r\n\r\n%s", strlen(message), message);

    // printf("response:\n%s\n", response);

    send(client_fd, response, sizeof(response), 0);
}

void
read_response(char *message, size_t size)
{
    FILE *fp = fopen("/home/tom/code/projects/http-server/www/index.html", "r");
    if (fp == NULL)
    {
        perror("failed to open file!");
        exit(EXIT_FAILURE);
    }

    size_t bytes = fread(message, 1, size - 1, fp); 
    message[bytes] = '\0';
    printf("%s\n", message);
    fclose(fp);
}
