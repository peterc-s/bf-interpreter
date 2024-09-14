#ifndef BF_H
#define BF_H

#include <stdint.h>
#include <stdio.h>

typedef struct BrainFuck {
    size_t memory_size;
    uint_fast8_t* memory;
    uint_fast8_t* data_ptr;
} BrainFuck;


BrainFuck bf_init(size_t mem_size);
void bf_free(BrainFuck* bf);
void bf_realloc_plus(BrainFuck* bf);

#endif
