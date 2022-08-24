#include "../include/http_server.h"

int main() {
    int server_socket = setup_server();
    run_server(server_socket);

    return 0;
}
