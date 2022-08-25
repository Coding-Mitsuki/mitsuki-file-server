#include "../include/headers.h"

#include <stdio.h>
#include <string.h>

// Headers struct with no headers in it
Headers empty_headers() {
    Headers headers = {
        .nb_headers = 0,
        .headers = NULL,
    };

    return headers;
}

// Converts a header to its string representation to respond to a HTTP request
// The dest string should be allocated enough memory using `header_string_length`
void header_to_string(const Header* const header, char* const dest) {
    sprintf(dest, "%s: %s", header_types_str[header->type], header->value);
}

// Compute the size of the header string, adding the size of the type
// and the value plus two characters: ':' and ' '
size_t header_string_length(const Header* const header) {
    return strlen(header->value) + strlen(header_types_str[header->type]) + 2;
}
