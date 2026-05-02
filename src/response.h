#ifndef RESPONSE_H
#define RESPONSE_H

#include <stdio.h>
#define RESPONSE_SIZE 4096

typedef enum status_ {
    FILE_NOT_FOUND,
    READ_SUCCESS
} status_t;

void send_response(int client_fd, char *message, size_t size, char *path);
status_t read_response(char *path, char *message, size_t size, size_t *byte_read);
char *get_extension(char *path);

#endif // !RESPONSE_H
