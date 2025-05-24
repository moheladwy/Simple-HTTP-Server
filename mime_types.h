#include <stdlib.h>

typedef struct {
    const char* extension;
    const char* content_type;
} mime_mapping_t;

static const mime_mapping_t mime_mappings[] = {
    {".html", "text/html"},
    {".htm", "text/html"},
    {".css", "text/css"},
    {".js", "application/javascript"},
    {".txt", "text/plain"},
    {".ts", "text/typescript"},
    {".jpg", "image/jpeg"},
    {".jpeg", "image/jpeg"},
    {".png", "image/png"},
    {".gif", "image/gif"},
    {NULL, NULL}
};
