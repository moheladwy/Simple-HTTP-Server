#ifndef STATUS_CODES_H
#define STATUS_CODES_H

/**
 * Structure representing an HTTP status code and its message
 */
typedef struct {
    int code;           // HTTP status code (e.g., 200, 404)
    const char* message; // HTTP status message (e.g., "OK", "Not Found")
} HttpStatus;

// Common HTTP status codes
extern const HttpStatus HTTP_OK;
extern const HttpStatus HTTP_CREATED;
extern const HttpStatus HTTP_BAD_REQUEST;
extern const HttpStatus HTTP_UNAUTHORIZED;
extern const HttpStatus HTTP_FORBIDDEN;
extern const HttpStatus HTTP_NOT_FOUND;
extern const HttpStatus HTTP_INTERNAL_SERVER_ERROR;

// Function to get a status by code
const HttpStatus* get_status_by_code(int code);

#endif /* STATUS_CODES_H */
