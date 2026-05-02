#include "request.h"
#include <stdio.h>

void
parse_request(request_t *req, char *raw_request)
{
    sscanf(raw_request, "%s %s %s", req->method, req->path, req->version);
    printf("raw_request:\n%s\n", raw_request);
    printf("\n\npath: %s\n\n", req->path);
}
