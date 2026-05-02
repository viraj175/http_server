#ifndef REQUEST_H
#define REQUEST_H

#define PATH_SIZE 256
#define METHOD_SIZE 8
#define VERSION_SIZE 16
#define REQUEST_SIZE 4096

typedef struct request {
    char method[METHOD_SIZE];
    char path[PATH_SIZE];
    char version[VERSION_SIZE];
} request_t;

void parse_request(request_t *req, char *raw_request);

#endif // !REQUEST_H
