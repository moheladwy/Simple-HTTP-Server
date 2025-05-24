# Simple HTTP Server

A lightweight HTTP server implementation in C that demonstrates fundamental web server functionality. This project serves static files and handles basic HTTP requests.

## Features

- Serves static files from the filesystem
- Proper MIME type detection based on file extensions
- Standard HTTP status codes and responses
- Minimalist and educational codebase

## Project Structure

- `server.c` - Main server implementation
- `utils.h/utils.c` - Utility functions for file operations and content type handling
- `status_codes.h/status_codes.c` - HTTP status codes implementation
- `Makefile` - Build configuration

## Requirements

- GCC compiler
- POSIX-compliant operating system (Linux, macOS, etc.)

## Building and Running

### Build the server

```bash
make build
```

### Run the server

```bash
make run
```

### Clean build files

```bash
make clean
```

## Usage

1. Start the server using `make run`
2. Navigate to <http://localhost:8080/index.html> in your web browser
   - Replace `index.html` with any file in the server directory you want to access

## How It Works

1. The server creates a socket and binds it to port 8080
2. Listens for incoming HTTP requests
3. Parses the request to determine which file is being requested
4. Checks if the file exists and sends appropriate status code
5. Determines the content type based on file extension
6. Sends the file content to the client with proper HTTP headers


## Limitations

This is a simple demonstration server intended for educational purposes. It doesn't support:

- Multiple concurrent connections
- HTTP methods other than GET
- Dynamic content generation
- Security features


## License

This project is open source and available for educational purposes.
