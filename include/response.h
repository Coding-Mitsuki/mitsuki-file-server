#ifndef RESPONSE_H
#define RESPONSE_H

#include "headers.h"

typedef struct Response {
    Headers headers;
    char* body;
} Response;

#endif // RESPONSE_H
