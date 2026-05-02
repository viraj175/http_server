#ifndef REQUEST_H
#define REQUEST_H

typedef struct request {
    char method[8];
    char path[256];
    char version[16];
} request_t;

void parse_request(request_t *req, char *raw_request);

#endif // !REQUEST_H
