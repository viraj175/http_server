#ifndef RESPONSE_H
#define RESPONSE_H

#include <stdio.h>
#define RESPONSE_SIZE 256

void send_response(int client_fd, char *message);
void read_response(char *message, size_t size);

#endif // !RESPONSE_H
