#include <stdlib.h>

#include "bf.h"
#include "error.h"

BrainFuck bf_init(size_t mem_size) {
    uint_fast8_t* memory = (uint_fast8_t*)calloc(mem_size, sizeof(uint_fast8_t));

    if (memory == NULL) error("Couldn't allocate memory.");

    uint_fast8_t* data_ptr = memory;
    BrainFuck bf = {
        .memory_size = mem_size,
        .memory = memory,
        .data_ptr = data_ptr,
    };

    return bf;
}

void bf_free(BrainFuck* bf) {
    free(bf->memory);
}

void bf_realloc_plus(BrainFuck* bf) {
    uint_fast8_t* new_memory = (uint_fast8_t*)realloc(bf->memory, bf->memory_size * 2);

    if (new_memory == NULL) error("Couldn't reallocate memory.");

    bf->memory = new_memory;
    bf->memory_size *= 2;
}
