#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#define BUF_SIZE 2048
#define MAX_PENDING_CONS 5
#define PORT 8080

int setup_server();
void run_server();

#endif // HTTP_SERVER_H
