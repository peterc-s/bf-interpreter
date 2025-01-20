#ifndef BF_H
#define BF_H

#include <stdint.h>
#include <stdio.h>

#define DEFAULT_STACK_SIZE 64
#define DEFAULT_MEM_SIZE 64

typedef struct BrainFuck {
    uint_fast8_t* memory;   // the actual bf memory strip
    uint_fast8_t* data_ptr; // the data pointer
    size_t memory_size;     // the current size of the bf memory strip
    size_t data_ptr_pos;    // the index of the data pointer
    size_t open_stack[DEFAULT_STACK_SIZE]; // the stack of [ instructions
    int64_t stack_ptr;      // the index of the open_stack pointer
} BrainFuck;


BrainFuck bf_init();
void bf_free(BrainFuck* bf);
void bf_realloc_plus(BrainFuck* bf);
void bf_realloc_minus(BrainFuck* bf);
void bf_dump_memory(BrainFuck* bf);
void bf_dump_stack(BrainFuck* bf, char* instruction_base);
void bf_print(BrainFuck* bf);
int bf_run(BrainFuck* bf, char* source);

#endif
