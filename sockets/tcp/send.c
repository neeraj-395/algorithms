#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include "tcp.h" // create_sockaddr, sock_cleanup

int server_socket = -1;
int client_socket = -1;

int main(int argc, const char **argv) {
    signal(SIGINT, sock_cleanup);

    const char *address = argv[1];
    unsigned port = atoi(argv[2]);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_addr = create_sockaddr(AF_INET, port, address);

    bind(server_socket, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    listen(server_socket, 4);

    client_socket = accept(server_socket, NULL, NULL);

    while(1) {
        char message[1024] = {0};
        fgets(message, sizeof(message), stdin);
        send(client_socket, message, strlen(message), 0);
        sleep(1);
    }

    return 0;
}