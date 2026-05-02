#include "response.h"
#include "request.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <fcntl.h>

void
send_response(int client_fd, char *message, size_t size, char *path)
{
    char response[RESPONSE_SIZE];
    size_t bytes_read;
    if (strcmp(path, "/") == 0) snprintf(path, PATH_SIZE, "/index.html");
    printf("\n\npath: %s\n\n", path);
    if(read_response(path, message, size, &bytes_read) == FILE_NOT_FOUND)
    {
        const char *error_message = "<h1>404 Not Found</h1>";
        int len = snprintf(response,  sizeof(response), 
                "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\nContent-Length: %zu\r\n\r\n%s",
                strlen(error_message), error_message);
        send(client_fd, response, len, 0);
        return;
    }
    else 
    {
        // printf("\n\npath: %s\n\n", path);
        const char *type = get_extension(path);
        int len = snprintf(response,  sizeof(response), 
                "HTTP/1.1 200 OK\r\nContent-Type: %s\r\nContent-Length: %zu\r\n\r\n",
                type, bytes_read);
        send(client_fd, response, len, 0);
        send(client_fd, message, bytes_read, 0);
    }
    printf("PATH_SIZE: %d", PATH_SIZE);
    // printf("response:\n%s\n", response);
}

status_t
read_response(char *path, char *message, size_t size, size_t *bytes_read)
{
    char filename[PATH_SIZE + 4];
    snprintf(filename, sizeof(filename), "www%s", path);
    printf("filename: %s\n", filename);
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        perror("failed to open file!");
        return FILE_NOT_FOUND;
    }

    *bytes_read = fread(message, 1, size - 1, fp); 
    message[*bytes_read] = '\0';
    printf("%s\n", message);
    fclose(fp);
    return READ_SUCCESS;
}

char*
get_extension(char *path)
{
    char *ptr = strrchr(path, '.');

    if (!ptr) return "text/html";
    if (strcmp(ptr, ".html") == 0) return "text/html";
    else if (strcmp(ptr, ".css") == 0) return "text/css";
    else if (strcmp(ptr, ".js") == 0) return "application/javascript";
    else if (strcmp(ptr, ".png") == 0) return "image/png";
    else if (strcmp(ptr, ".jpeg") == 0) return "image/jpeg";
    else if (strcmp(ptr, ".ico") == 0) return "image/x-icon";
    else return "unknown";
}
