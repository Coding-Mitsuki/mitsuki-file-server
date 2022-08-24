#include "../include/http_server.h"

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int setup_server() {
    int server_socket;

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Cannot create socket: ");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Cannot bind socket: ");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, MAX_PENDING_CONS) < 0) {
        perror("Cannot listen: ");
        exit(EXIT_FAILURE);
    }

    return server_socket;
}

void run_server(int server_socket) {
    for (;;) {
        int new_socket;
        socklen_t addr_len;
        struct sockaddr address;

        if ((new_socket = accept(server_socket, &address, &addr_len)) < 0) {
            perror("Cannot accept connection: ");
            exit(EXIT_FAILURE);
        }

        char buffer[BUF_SIZE] = {0};
        int read_len = read(new_socket, buffer, BUF_SIZE);

        buffer[read_len] = '\0';

        printf("%s\n", buffer);

        char* response =
            "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length\n\nHello world!";

        write(new_socket, response, strlen(response));

        close(new_socket);
    }
}
