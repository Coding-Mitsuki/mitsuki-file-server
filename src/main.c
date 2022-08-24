#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const int PORT = 8080;
const int MAX_PENDING_CONS = 5;

#define BUF_SIZE 2048

int main() {
    int server_fd;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Cannot create socket: ");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Cannot bind socket: ");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, MAX_PENDING_CONS) < 0) {
        perror("Cannot listen: ");
        exit(EXIT_FAILURE);
    }

    for (;;) {
        int new_socket;
        socklen_t addr_len;

        if ((new_socket = accept(server_fd, (struct sockaddr*)&address, &addr_len)) < 0) {
            perror("Cannot accept connection: ");
            exit(EXIT_FAILURE);
        }

        char buffer[BUF_SIZE] = {0};
        int read_len = read(new_socket, buffer, BUF_SIZE);

        buffer[read_len] = '\0';

        printf("%s\n", buffer);

        close(new_socket);
    }

    return 0;
}
