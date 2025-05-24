#include "status_codes.h"
#include <stdlib.h>

// Define common HTTP status codes
const HttpStatus HTTP_OK = {200, "OK"};
const HttpStatus HTTP_CREATED = {201, "Created"};
const HttpStatus HTTP_BAD_REQUEST = {400, "Bad Request"};
const HttpStatus HTTP_UNAUTHORIZED = {401, "Unauthorized"};
const HttpStatus HTTP_FORBIDDEN = {403, "Forbidden"};
const HttpStatus HTTP_NOT_FOUND = {404, "Not Found"};
const HttpStatus HTTP_INTERNAL_SERVER_ERROR = {500, "Internal Server Error"};

// Array of all supported status codes
static const HttpStatus STATUS_CODES[] = {
    {200, "OK"},
    {201, "Created"},
    {400, "Bad Request"},
    {401, "Unauthorized"},
    {403, "Forbidden"},
    {404, "Not Found"},
    {500, "Internal Server Error"},
    // Add more status codes as needed
};

static const int STATUS_CODES_COUNT = sizeof(STATUS_CODES) / sizeof(HttpStatus);

/**
 * @brief Retrieves the HTTP status information for a given status code.
 *
 * Searches the set of supported HTTP status codes and returns a pointer to the corresponding `HttpStatus` structure if the code is found.
 *
 * @param code The numeric HTTP status code to look up.
 * @return Pointer to the matching `HttpStatus` structure, or `NULL` if the code is not supported.
 */
const HttpStatus* get_status_by_code(int code) {
    for (int i = 0; i < STATUS_CODES_COUNT; i++) {
        if (STATUS_CODES[i].code == code) {
            return &STATUS_CODES[i];
        }
    }
    
    // If status code is not found, return NULL
    return NULL;
}
