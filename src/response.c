#include "../include/response.h"

Response default_response() {
    Response response = {
        .status = NOT_FOUND,
        .headers = empty_headers(),
        .body = "",
    };

    return response;
}
