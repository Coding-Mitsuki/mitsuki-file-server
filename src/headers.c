#include "../include/headers.h"

#include <stdio.h>
#include <string.h>

// Converts a header to its string representation to respond to a HTTP request
// The dest string should be allocated enough memory using `header_string_length`
void header_to_string(const Header header, char* const dest) {
    sprintf(dest, "%s: %s", header_types_str[header.type], header.value);
}

// Compute the size of the header string, adding the size of the type
// and the value plus two characters: ':' and ' '
size_t header_string_length(const Header header) {
    return strlen(header.value) + strlen(header_types_str[header.type]) + 2;
}
