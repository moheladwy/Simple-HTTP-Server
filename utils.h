#ifndef UTILS_H
#define UTILS_H

// Returns the file extension (including the dot) of a filename
// Returns NULL if no extension is found
const char* get_file_extension(const char* filename);

// Returns the content type of a file extension
// Returns "text/plain" if no content type is found
const char* get_content_type_using_file_extension(const char* extension);

// Returns the size of a file from a file descriptor
// Returns -1 if an error occurs
int get_file_size_from_fd(int open_fd);

#endif /* UTILS_H */
