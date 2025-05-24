#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include "utils.h"
#include "status_codes.h"

#define PORT 8080
#define ANY_ADDRESS 0
#define MAX_PENDING_CONNECTIONS 10
#define BUFFER_SIZE 1024
#define FLAGS 0

int main(int argc, char *argv[])
{
    // Create a socket
    printf("Creating socket...\n");
    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0)
    {
        perror("socket");
        return 1;
    }
    printf("Socket created successfully.\n");

    // Create a sockaddr_in structure
    printf("Creating sockaddr_in structure...\n");
    int port = htons(PORT);
    const struct sockaddr_in addr = {
        AF_INET,    // Address family
        port,       // Port number in network byte order
        ANY_ADDRESS // Any address (INADDR_ANY)
    };
    printf("sockaddr_in structure created successfully.\n");

    // Bind the socket to the address
    printf("Binding socket to address...\n");
    int b = bind(s, (struct sockaddr *)&addr, sizeof(addr));
    if (b < 0)
    {
        perror("bind");
        return 1;
    }
    printf("Socket bound to address successfully.\n");

    // Listen for incoming connections
    printf("Listening for incoming connections wiht max %d pending connections...\n", MAX_PENDING_CONNECTIONS);
    listen(
        s,                      // Socket file descriptor
        MAX_PENDING_CONNECTIONS // Maximum number of pending connections
    );
    printf("Listening for incoming connections successfully.\n");

    // Accept a connection
    printf("Accepting incoming connection...\n");
    int client_fd = accept(s, 0, 0);
    if (client_fd < 0)
    {
        perror("accept");
        return 1;
    }
    printf("Accepted incoming connection successfully.\n");

    // Buffer to store received data
    char buffer[BUFFER_SIZE] = {0};

    // Receive data from the client
    printf("Receiving data from client...\n");
    recv(client_fd, buffer, sizeof(buffer), FLAGS);
    printf("Received data from client successfully.\n");

    // file.html ...
    char *file = buffer + 5; // Skip the first 5 characters "GET /"
    *strchr(file, ' ') = 0;  // Replace the first space with a null terminator so that we can use it as a string.
    printf("The Received file is: %s\n", file);

    // Open the file
    int open_fd = open(file, O_RDONLY);
    if (open_fd < 0)
    {
        perror("open");
        char error_response[BUFFER_SIZE];
        int content_length = strlen(HTTP_NOT_FOUND.message);
        sprintf(error_response, "HTTP/1.0 %d %s\r\nContent-Type: text/plain\r\nContent-Length: %d\r\n\r\n%s",
                HTTP_NOT_FOUND.code, HTTP_NOT_FOUND.message, content_length, HTTP_NOT_FOUND.message);
        send(client_fd, error_response, strlen(error_response), 0);
        close(client_fd);
        close(s);
        return 1;
    }

    // Get file size
    off_t file_size = get_file_size_from_fd(open_fd);
    if (file_size < 0)
    {
        perror("get_file_size");
        close(open_fd);
        close(client_fd);
        close(s);
        return 1;
    }

    // Determine content type based on file extension
    const char *ext = get_file_extension(file);
    const char *content_type = get_content_type_using_file_extension(ext);

    // Prepare and send HTTP header
    char header[BUFFER_SIZE];
    sprintf(header, "HTTP/1.0 %d %s\r\nContent-Type: %s\r\nContent-Length: %ld\r\n\r\n",
            HTTP_OK.code, HTTP_OK.message, content_type, (long)file_size);
    send(client_fd, header, strlen(header), 0);

    // Send the file to the client.
    printf("Sending file to client...\n");
    sendfile(
        client_fd, // Socket file descriptor
        open_fd,   // File descriptor of the file to send
        0,         // Offset in the file (0 means start from the beginning)
        file_size  // Length of data to send (0 means send the whole file)
    );
    printf("File sent to client successfully.\n");

    // Close the file descriptors
    printf("Closing file descriptors...\n");
    close(open_fd);
    close(client_fd);
    printf("File descriptors closed successfully.\n");

    // Close the socket
    printf("Closing socket...\n");
    close(s);
    printf("Socket closed successfully.\n");

    return 0;
}
