#include <stdio.h>

void eprint(const char* message) {
    fprintf(stderr, "Error: %s\n", message);
}
