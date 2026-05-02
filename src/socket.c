#include "socket.h"
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void
create_socket(http_socket_t *sock)
{
    sock->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock->socket_fd == -1)
    {
        perror("socket faild");
        exit(EXIT_FAILURE);
    }

    sock->addr.sin_family = AF_INET;
    sock->addr.sin_port = htons(8080);
    sock->addr.sin_addr.s_addr = INADDR_ANY;
}
