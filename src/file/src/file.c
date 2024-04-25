#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "file.h"

FILE *
_file_open(const char *file, const char *mode);

byte *
fileread(const char *file) {
    int n = 0, size = 128, ch;
    byte *line;
    line = malloc(size + 1);
    FILE * infile = _file_open(file, "r");
    while ((ch = getc(infile)) != '\n' && ch != EOF) {
        if (n == size) {
            size *= 2;
            line = realloc(line, size + 1);
        }
        line[n++] = ch;
    }
    if (n == 0 && ch == EOF) {
        free(line);
        return NULL;
    }
    line[n] = '\0';
    line = realloc(line, n + 1);
    return line;
}

FILE *
_file_open(const char *file, const char *mode) {
    FILE *fp;
    if (access(file, F_OK) == 0) {
        fp = fopen(file, mode);
        if (fp == NULL)
            exit(EXIT_FAILURE);
        return fp;
    } else {
        exit(EXIT_FAILURE);
    }
}