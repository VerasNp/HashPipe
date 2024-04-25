#include <stdio.h>
#include <stdlib.h>

#include "file.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("\nInforme o arquivo de entrada!");
        exit(EXIT_FAILURE);
    } else {
        printf(&(fileread(argv[0])));
        return 0;
    }
}

