#ifndef BF_H
#define BF_H

#include <stdint.h>
#include <stdio.h>

typedef struct BrainFuck {
    size_t memory_size;
    uint_fast8_t* memory;
    uint_fast8_t* data_ptr;
    size_t data_ptr_pos;
} BrainFuck;


BrainFuck bf_init(size_t mem_size);
void bf_free(BrainFuck* bf);
void bf_realloc_plus(BrainFuck* bf);
void bf_dump_memory(BrainFuck* bf);
int bf_run(BrainFuck* bf, char* source);

#endif
