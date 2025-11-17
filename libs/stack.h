/*
 *  $VER:       stack.c 1.0
 *  $DATE:      2025-11-16 (2025-11-16)
 *  $AUTHOR:    Goran (dejakju@gmail.com)
*/

#ifndef LIBS_STACK_H
#define LIBS_STACK_H


////////////////////////////////
//------------------------------- Dependencies
// NOTE(dejakju): 

#include <stdint.h>
#include <stdbool.h>


////////////////////////////////
//------------------------------- Enum Types
// NOTE(dejakju): 

typedef enum AMMX_StackTypeDef {
    AMMX_STACK_EMPTY    = (uint64_t) 0x000000007FFFFFFF,    // 01111111111111111111111111111111 as binary
    AMMX_STACK_LENGTH   = (uint64_t) 0x0000000000007FFF,    // 32767 as decimal or 0111111111111111 as binary
    AMMX_STACK_ISEMPTY  = (uint64_t) 0x000000007FFFFFFF     // 2147483647 as decimal
} AMMX_StackTypeDef;

typedef struct stack_t {
    int64_t values[AMMX_STACK_LENGTH];
    int64_t top;                                            // index of top element (-1 means empty)
    int64_t size;                                           // size of stack (# of elements)
} stack_t;


////////////////////////////////
//------------------------------- Function Declarations
// NOTE(dejakju): 

void init_stack(stack_t *s);
bool is_empty_stack(stack_t *s);
bool is_full_stack(stack_t *s);
bool push(stack_t *s, int64_t value);
int64_t peek(stack_t *s);
int64_t pop(stack_t *s);
int64_t sizeof_stack(stack_t *s);

#endif
