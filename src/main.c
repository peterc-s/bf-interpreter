#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "file.h"
#include "bf.h"

#define DEFAULT_MEM_SIZE 16

int main(int argc, char* argv[]) {
    // check for correct number of args
    if (argc != 2) {
        fprintf(stdout, "Usage: %s <src_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // read in the file
    char* src_file_buf = read_file(argv[1]);

    // DEBUG
    // printf("File contents:\n%s", src_file_buf);
   
    // create a new BrainFuck struct
    BrainFuck bf = bf_init(DEFAULT_MEM_SIZE);

    // run the interpreter on the source file
    bf_run(&bf, src_file_buf);

    //debug
    // bf_dump_memory(&bf);
    // bf_dump_stack(&bf);
    bf_print(&bf);


    // free any memory
    free(src_file_buf);
    bf_free(&bf);

    return EXIT_SUCCESS;
}
