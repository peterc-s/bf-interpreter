#include <stdint.h>
#include <stdlib.h>
#include <errno.h>

#include "bf.h"
#include "error.h"

// initialises a BrainFuck struct with the given memory size
BrainFuck bf_init(size_t mem_size) {
    uint_fast8_t* memory = (uint_fast8_t*)calloc(mem_size, sizeof(uint_fast8_t));

    if (!memory && errno) {
        eprint("ERROR");
        exit(errno);
    };

    uint_fast8_t* data_ptr = memory;
    BrainFuck bf = {
        .memory_size = mem_size,
        .memory = memory,
        .data_ptr = data_ptr,
        .data_ptr_pos = 0,
        .open_stack = { NULL },
        .stack_ptr = -1,
    };

    return bf;
}

// frees any heap memory allocated within the BrainFuck struct
void bf_free(BrainFuck* bf) {
    free(bf->memory);
}

// doubles the allocated memory in a BrainFuck struct
void bf_realloc_plus(BrainFuck* bf) {
    //DEBUG
    // bf_dump_memory(bf);

    uint_fast8_t* new_memory = (uint_fast8_t*)realloc(bf->memory, bf->memory_size * 2);

    if (!new_memory && errno) {
        eprint("ERROR");
        exit(errno);
    };

    for(size_t i = bf->memory_size; i < bf->memory_size * 2; ++i) {
        new_memory[i] = 0;
    }

    bf->memory = new_memory;
    bf->memory_size *= 2;
    bf->data_ptr = bf->memory + bf->data_ptr_pos;
}

// prints out the memory
void bf_dump_memory(BrainFuck* bf) {
    printf("\n---MEMORY DUMP---\n");
    for (size_t i = 0; i < bf->memory_size; ++i) {
        printf("%08lu: %d\n", i, bf->memory[i]);
    }
}

// prints out the stack
void bf_dump_stack(BrainFuck* bf) {
    printf("\n---STACK DUMP---\n");
    printf("SP: %ld\n", bf->stack_ptr);
    int64_t i = 0;
    while (++i, bf->open_stack[i] != NULL) {
        printf("%03lu: %p : %c", i, bf->open_stack[i], *bf->open_stack[i]);
        if (i == bf->stack_ptr) printf(" <--");
        printf("\n");
    }
}

void bf_print(BrainFuck* bf) {
    printf("\n");
    for (size_t i = 0; i < bf->memory_size; ++i) printf("%03d ", bf->memory[i]);
    printf("\n");

    for (size_t i = 0; i < bf->data_ptr_pos; ++i) printf("    ");
    printf("^\n");
}

// corresponds to >
void inst_ptr_inc(BrainFuck* bf) {
    //DEBUG
    // printf("PTR_INC\n");

    // check for overflow
    if (bf->data_ptr_pos + 1 == 0) {
        fprintf(stderr, "ERROR: Data pointer overflow at character %lu\n", bf->data_ptr_pos);
        exit(EXIT_FAILURE);
    }
    
    if (bf->data_ptr_pos + 1 >= bf->memory_size) {
        bf_realloc_plus(bf);
    }

    ++bf->data_ptr;
    ++bf->data_ptr_pos;
}

// corresponds to <
void inst_ptr_dec(BrainFuck* bf) {
    //DEBUG
    // printf("PTR_DEC\n");

    // check for underflow
    if (bf->data_ptr_pos - 1 == SIZE_MAX) {
        fprintf(stderr, "ERROR: Data pointer underflow at character %lu\n", bf->data_ptr_pos);
        exit(EXIT_FAILURE);
    }

    --bf->data_ptr;
    --bf->data_ptr_pos;
}

// corresponds to +
void inst_inc(BrainFuck* bf) {
    //DEBUG
    // printf("INC\n");

    ++(*bf->data_ptr);
}

// corresponds to -
void inst_dec(BrainFuck* bf) {
    //DEBUG
    // printf("DEC\n");

    --(*bf->data_ptr);
}

// corresponds to .
void inst_out(BrainFuck* bf) {
    //DEBUG
    // printf("OUT\n");

    printf("%c", *bf->data_ptr);
}

// corresponds to ,
void inst_in(BrainFuck* bf) {
    //DEBUG
    // printf("IN\n");

    *bf->data_ptr = getchar();

    //DEBUG
    // printf("Inputted: %c\n", *bf->data_ptr);
}

// corresponds to [
void inst_open_j(BrainFuck* bf, char** instruction_ptr) {
    //DEBUG
    // printf("Current data: %d\nSP: %ld\n", *bf->data_ptr, bf->stack_ptr);

    // if jump condition
    if (*bf->data_ptr == 0) {
        //DEBUG
        // printf("j");

        // find matching ] or EOF
        int bal = 1;
        do {
            ++(*instruction_ptr);
            switch (**instruction_ptr) {
                case '[': ++bal; /* printf("BAL +\n"); */ break;
                case ']': --bal; /* printf("BAL -\n"); */ break;
                case '\0': eprint("Unmatched brackets."); exit(EXIT_FAILURE); break;
                default:;
            }

            //DEBUG
            // printf("%c", **instruction_ptr);
        } while (bal != 0);
        
        //DEBUG
        // bf_dump_stack(bf);
        return;
    }

    // if not, then we should add to stack
    
    // check for overflow
    if (bf->stack_ptr + 1 > DEFAULT_STACK_SIZE) {
        eprint("Stack overflow.");
        exit(EXIT_FAILURE);
    };

    //DEBUG
    // printf("Adding to stack!\n");

    // create new item on stack
    bf->open_stack[++bf->stack_ptr] = *instruction_ptr;
}

// corresponds to ]
void inst_close_j(BrainFuck* bf, char** instruction_ptr) {
    //DEBUG
    // printf("Current data: %d\nSP: %ld\n", *bf->data_ptr, bf->stack_ptr);

    // if jump condition
    if (*bf->data_ptr != 0) {
        // check for unmatched brackets
        if (bf->stack_ptr == -1) {
            eprint("Unmatched brackets.");
            exit(EXIT_FAILURE);
        };

        // jump
        *instruction_ptr = bf->open_stack[bf->stack_ptr];

        //DEBUG
        // printf("Jumped to: %c\n", **instruction_ptr);
        return;
    }

    // if not we should pop the stack
    
    // check if nothing on stack
    if (bf->stack_ptr == -1) {
        eprint("Unmatched brackets.");
        exit(EXIT_FAILURE);
    };

    // decrement stack pointer
    --bf->stack_ptr;
}

// runs the interpreter with a given BrainFuck struct and source code
int bf_run(BrainFuck* bf, char* source) {
    char* instruction_ptr = source;

    while (*instruction_ptr != '\0') {
        //DEBUG
        // printf("Current instruction: %c\n", *instruction_ptr);
        // printf("%c", *instruction_ptr);
        switch (*instruction_ptr) {
            case '>': inst_ptr_inc(bf); break;
            case '<': inst_ptr_dec(bf); break;
            case '+': inst_inc(bf); break;
            case '-': inst_dec(bf); break;
            case '.': inst_out(bf); break;
            case ',': inst_in(bf); break;
            case '[': inst_open_j(bf, &instruction_ptr); break;
            case ']': inst_close_j(bf, &instruction_ptr); break;
            default:;
        }

        //DEBUG
        // bf_print(bf);
        instruction_ptr++;
    }

    return EXIT_SUCCESS;
}

