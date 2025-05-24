#include "utils.h"
#include <string.h>
#include <sys/stat.h>

/**
 * @brief Returns a pointer to the file extension in a filename.
 *
 * If the filename contains a dot, returns a pointer to the last occurrence of '.' in the string, including the dot itself. Returns NULL if the input is NULL or if no dot is found.
 *
 * @param filename The name of the file as a null-terminated string.
 * @return Pointer to the file extension within the filename, or NULL if not found.
 */
const char* get_file_extension(const char* filename) {
    if (filename == NULL) {
        return NULL;
    }
    
    return strrchr(filename, '.');
}

/**
 * @brief Returns the MIME content type string for a given file extension.
 *
 * If the extension is recognized, returns the corresponding MIME type.
 * Defaults to "text/plain" if the extension is NULL or unrecognized.
 *
 * @param extension File extension string, including the dot (e.g., ".html").
 * @return const char* MIME content type string.
 */
const char* get_content_type_using_file_extension(const char* extension) {
  const char* content_type = "text/plain";
  
  if (extension == NULL) {
    return content_type;
  }
  
  if (strcmp(extension, ".html") == 0 || strcmp(extension, ".htm") == 0) {
      content_type = "text/html";
  }
  else if (strcmp(extension, ".css") == 0) {
      content_type = "text/css";
  }
  else if (strcmp(extension, ".js") == 0) {
      content_type = "application/javascript";
  }
  else if (strcmp(extension, ".jpg") == 0 || strcmp(extension, ".jpeg") == 0) {
      content_type = "image/jpeg";
  }
  else if (strcmp(extension, ".png") == 0) {
      content_type = "image/png";
  }
  else if (strcmp(extension, ".gif") == 0) {
      content_type = "image/gif";
  }
  
  return content_type;
}

/**
 * @brief Returns the size of a file in bytes given its open file descriptor.
 *
 * Uses `fstat` to retrieve the file size. Returns -1 if the operation fails.
 *
 * @param open_fd An open file descriptor for the file.
 * @return int Size of the file in bytes, or -1 on failure.
 */
int get_file_size_from_fd(int open_fd) {
  struct stat file_stat;
  
  if (fstat(open_fd, &file_stat) < 0) {
    return -1;
  }
  
  return file_stat.st_size;
}