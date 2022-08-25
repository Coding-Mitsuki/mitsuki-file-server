#ifndef RESPONSE_H
#define RESPONSE_H

#include "headers.h"

typedef enum StatusCode {
    OK = 200,
    NOT_FOUND = 404,
} StatusCode;

typedef struct Response {
    StatusCode status;
    Headers headers;
    char* body;
} Response;

Response default_response();

size_t response_string_length(const Response* const response);
void response_to_string(const Response* const response, char* dest);

#endif // RESPONSE_H
