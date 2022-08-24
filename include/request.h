#ifndef REQUEST_H
#define REQUEST_H

#include "headers.h"

typedef enum RequestType {
    GET,
    POST,
    PUT,
    DELETE,
} RequestType;

typedef struct Request {
    RequestType type;
    Headers headers;
} Request;

#endif // REQUEST_H
