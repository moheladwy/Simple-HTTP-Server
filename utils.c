#include "utils.h"
#include <string.h>
#include <sys/stat.h>

const char* get_file_extension(const char* filename) {
    if (filename == NULL) {
        return NULL;
    }
    
    return strrchr(filename, '.');
}

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

int get_file_size_from_fd(int open_fd) {
  struct stat file_stat;
  
  if (fstat(open_fd, &file_stat) < 0) {
    return -1;
  }
  
  return file_stat.st_size;
}