#include "utils.h"
#include <string.h>
#include <sys/stat.h>
#include "mime_types.h"

const char* get_file_extension(const char* filename) {
    if (filename == NULL) {
        return NULL;
    }
    
    return strrchr(filename, '.');
}

const char* get_content_type_using_file_extension(const char* extension) {
  const char* default_content_type = "text/plain";
  
  if (extension == NULL) {
    return default_content_type;
  }
  
  for (int i = 0; mime_mappings[i].extension != NULL; i++) {
    if (strcmp(extension, mime_mappings[i].extension) == 0) {
      return mime_mappings[i].content_type;
    }
  }
  
  return default_content_type;
}

off_t get_file_size_from_fd(int open_fd) {
  struct stat file_stat;
  
  if (fstat(open_fd, &file_stat) < 0) {
    return -1;
  }
  
  return file_stat.st_size;
}