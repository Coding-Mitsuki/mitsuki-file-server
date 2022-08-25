#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include "request.h"
#include "response.h"

#define BUF_SIZE 2048
#define MAX_PENDING_CONS 5
#define PORT 8080

// Represent a HTTP route and the code to execute
// when a request to this route is received.
// Routes are specific to request types.
typedef struct Route {
    RequestType type;
    char* path;
    Response (*handler)(Request);
} Route;

typedef struct HttpServer {
    int socket;
    size_t nb_routes;
    Route* routes;
} HttpServer;

HttpServer setup_server();
void add_route(HttpServer* const server, RequestType type, char* route, Response (*handler)(Request));
int run_server(HttpServer* server);

#endif // HTTP_SERVER_H
