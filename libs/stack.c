/*
 *  $VER:       stack.c 1.0
 *  $DATE:      2025-11-16 (2025-11-16)
 *  $AUTHOR:    Goran (dejakju@gmail.com)
*/

////////////////////////////////
//------------------------------- Dependencies
// NOTE(dejakju): 

#include "stack.h"
#include <stdbool.h>
#include <stdint.h>


////////////////////////////////
//------------------------------- Implementations
// NOTE(dejakju): 

/* Initialize stack */
void init_stack(stack_t *s) {
    s->top = -1;
    s->size = 0;
}

/* Check if stack is empty */
bool is_empty_stack(stack_t *s) {
    return (s->top == -1);
}

/* Check if stack is full */
bool is_full_stack(stack_t *s) {
    return (s->top >= (AMMX_STACK_LENGTH - 1));
}

/* Push an element onto the stack */
bool push(stack_t *s, int64_t value) {
    if (is_full_stack(s)) {
        // Stack overflow!
        return false;
    }
    s->size++;
    s->values[++(s->top)] = value;
    return true;
}

/* Peek at the top element without removing it */
int64_t peek(stack_t *s) {
    if (is_empty_stack(s)) {
        // Stack is empty!
        return AMMX_STACK_EMPTY;    // Return sentinel value
    }
    return s->values[s->top];
}

/* Pop the top element */
int64_t pop(stack_t *s) {
    if (is_empty_stack(s)) {
        // Stack underflow!
        return AMMX_STACK_EMPTY;    // Return sentinel value
    }
    s->size--;
    return s->values[(s->top)--];
}

/* Return number of elements in the stack */
int64_t sizeof_stack(stack_t *s) {
    return s->size;
}

