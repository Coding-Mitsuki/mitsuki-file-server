#include "../include/http_server.h"

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

HttpServer setup_server() {
    HttpServer server;
    memset(&server, 0, sizeof(server));

    if ((server.socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Cannot create socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(PORT);

    if (bind(server.socket, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Cannot bind socket");
        exit(EXIT_FAILURE);
    }

    if (listen(server.socket, MAX_PENDING_CONS) < 0) {
        perror("Cannot listen");
        exit(EXIT_FAILURE);
    }

    return server;
}

void add_route(
    HttpServer* const server,
    RequestType type,
    char* const path,
    Response (*handler)(Request)
) {
    Route route = {
        .type = type,
        .path = path,
        .handler = handler,
    };

    server->nb_routes++;
    server->routes = realloc(server->routes, server->nb_routes * sizeof(Route));

    if (server->routes == NULL) {
        perror("Couldn't allocate memory for route");
        exit(EXIT_FAILURE);
    }

    server->routes[server->nb_routes - 1] = route;
}

int run_server(HttpServer* const restrict server) {
    for (;;) {
        int new_socket;
        struct sockaddr address;
        socklen_t addr_len = sizeof(address);

        if ((new_socket = accept(server->socket, &address, &addr_len)) < 0) {
            perror("Cannot accept connection");
            continue;
        }

        char* buffer = calloc(BUF_SIZE, sizeof(char));
        int buffer_size = 0;
        int nb_reads = 0;

        while (buffer_size < BUF_SIZE * nb_reads) {
            buffer_size += read(new_socket, buffer, BUF_SIZE);
            nb_reads++;

            if (buffer_size >= BUF_SIZE * nb_reads) {
                buffer = realloc(buffer, buffer_size + BUF_SIZE);
            }
        }

        buffer[buffer_size] = '\0';
        printf("%s\n", buffer);

        Request request = handle_request(buffer);
        Response response = default_response();

        for (int i = 0; i < server->nb_routes; i++) {
            if (request.type == server->routes[i].type && request.path == server->routes[i].path) {
                response = (server->routes[i].handler)(request);
                break;
            }
        }

        /* char* response = */
        /*     "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length\n\nHello world!"; */

        char* response_string = malloc(response_string_length(&response));
        write(new_socket, response_string, strlen(response_string));

        free(buffer);
        free(response_string);
        close(new_socket);
    }
}
