#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "file.h"
#include "bf.h"

#define DEFAULT_MEM_SIZE 256


int main(int argc, char* argv[]) {
    // check for correct number of args
    if (argc != 2) {
        fprintf(stdout, "Usage: %s <src_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char* src_file_buf = read_file(argv[1]);

    // here for debug purposes
    printf("File contents:\n%s", src_file_buf);
   
    BrainFuck bf = bf_init(DEFAULT_MEM_SIZE);

    free(src_file_buf);
    bf_free(&bf);
    return EXIT_SUCCESS;
}
