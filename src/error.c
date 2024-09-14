#include <stdlib.h>
#include <stdio.h>

void error(const char* message) {
    fprintf(stderr, "Error: %s\n", message);
    exit(EXIT_FAILURE);
}
