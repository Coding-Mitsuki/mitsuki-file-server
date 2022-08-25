#include "../include/http_server.h"

int main() {
    HttpServer server = setup_server();

    return run_server(&server);
}
