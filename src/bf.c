#include <stdint.h>
#include <stdlib.h>

#include "bf.h"
#include "error.h"

// initialises a BrainFuck struct with the given memory size
BrainFuck bf_init(size_t mem_size) {
    uint_fast8_t* memory = (uint_fast8_t*)calloc(mem_size, sizeof(uint_fast8_t));

    if (memory == NULL) error("Couldn't allocate memory.");

    uint_fast8_t* data_ptr = memory;
    BrainFuck bf = {
        .memory_size = mem_size,
        .memory = memory,
        .data_ptr = data_ptr,
        .data_ptr_pos = 0,
    };

    return bf;
}

// frees any heap memory allocated within the BrainFuck struct
void bf_free(BrainFuck* bf) {
    free(bf->memory);
}

// doubles the allocated memory in a BrainFuck struct
void bf_realloc_plus(BrainFuck* bf) {
    uint_fast8_t* new_memory = (uint_fast8_t*)realloc(bf->memory, bf->memory_size * 2);

    if (new_memory == NULL) error("Couldn't reallocate memory.");

    bf->memory = new_memory;
    bf->memory_size *= 2;
}

// prints out the memory
void bf_dump_memory(BrainFuck* bf) {
    for (size_t i = 0; i < bf->memory_size; ++i) {
        printf("%08lu: %d\n", i, bf->memory[i]);
    }
}

// corresponds to >
void inst_ptr_inc(BrainFuck* bf) {
    //DEBUG
    // printf("PTR_INC\n");

    if (bf->data_ptr_pos + 1 == 0) {
        fprintf(stderr, "Error: Data pointer overflow at character %lu\n", bf->data_ptr_pos);
        exit(EXIT_FAILURE);
    }
    
    if (bf->data_ptr_pos > bf->memory_size) {
        bf_realloc_plus(bf);
    }

    bf->data_ptr++;
    bf->data_ptr_pos++;
}

// corresponds to <
void inst_ptr_dec(BrainFuck* bf) {
    //DEBUG
    // printf("PTR_DEC\n");

    if (bf->data_ptr_pos - 1 == SIZE_MAX) {
        fprintf(stderr, "Error: Data pointer underflow at character %lu\n", bf->data_ptr_pos);
        exit(EXIT_FAILURE);
    }

    bf->data_ptr--;
    bf->data_ptr_pos--;
}

// corresponds to +
void inst_inc(BrainFuck* bf) {
    //DEBUG
    // printf("INC\n");

    (*bf->data_ptr)++;
}

// corresponds to -
void inst_dec(BrainFuck* bf) {
    //DEBUG
    // printf("DEC\n");

    (*bf->data_ptr)--;
}

// corresponds to .
void inst_out(BrainFuck* bf) {
    //DEBUG
    // printf("OUT\n");

    printf("%c", *bf->data_ptr);
}

// runs the interpreter with a given BrainFuck struct and source code
int bf_run(BrainFuck* bf, char* source) {
    char* instruction_ptr = source;

    while (*instruction_ptr != '\0') {
        // printf("Current instruction: %c\n", *instruction_ptr);
        switch (*instruction_ptr) {
            case '>': inst_ptr_inc(bf); break;
            case '<': inst_ptr_dec(bf); break;
            case '+': inst_inc(bf); break;
            case '-': inst_dec(bf); break;
            case '.': inst_out(bf); break;
            default:;
        }
        instruction_ptr++;
    }

    return EXIT_SUCCESS;
};

