#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "tcp.h" // create_sockadrr, sock_cleanup

int client_socket = -1;
int server_socket = -1;

int main(int argc, const char **argv) {
    signal(SIGINT, sock_cleanup); 

    const char *address = argv[1];
    unsigned port = atoi(argv[2]);

    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_addr = create_sockaddr(AF_INET, port, address);

    if(connect(client_socket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        return EXIT_FAILURE;
    }

    char buffer[1024] = {0};

    while(1) {
        ssize_t bytes = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        buffer[bytes] = '\0';
        write(STDOUT_FILENO, buffer, bytes);
        sleep(1);
    }

    return EXIT_SUCCESS;
}