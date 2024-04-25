#ifndef HASHPIPE_FILE_H
#define HASHPIPE_FILE_H


typedef unsigned char byte;

#include <stdbool.h>

byte *
fileread(const char *file);

#endif //HASHPIPE_FILE_H