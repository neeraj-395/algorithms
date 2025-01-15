#ifndef TCP_H
#define TCP_H

#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

extern int client_socket;
extern int server_socket;

struct sockaddr_in create_sockaddr(unsigned family, unsigned port, const char *address) {
    return (struct sockaddr_in) {
        .sin_family = family,
        .sin_port=htons(port),
        .sin_addr.s_addr = inet_addr(address)
    };
}

void sock_cleanup() { close(client_socket); close(server_socket); exit(0);}

#endif // TCP_H