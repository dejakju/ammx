/*
    $VER:       ammx.c 1.0
    $DATE:      2023-12-01 (2025-10-18)
    $AUTHOR:    Goran (dejakju@gmail.com)
*/


//------------------------------- AMMX LIBRARIES
#include <conio.h>
#include <stdlib.h>
#include "libs/toolbox.h"

//------------------------------- MAIN ENTRY
int main()
{
//------------------------------- CODE PLAYGROUND

	ammx_version();

    stack_t mystack;

    ammx_push(&mystack, 0b100111011000);
    ammx_push(&mystack, 360);
    ammx_push(&mystack, 7);
    ammx_push(&mystack, AMMX_EXEC_NODE | AMMX_EXEC_EVENT);

    for (int i = 1; i < 3; i++)
        for (int j = 17; j < 1005; j++)
            ammx_push(&mystack, j*i);

    int32_t result = ammx_peek(&mystack);
    printf("peek result = %d\n\n", result);

    while (mystack.top > 0)
    {
        int32_t result = ammx_pop(&mystack);
        printf("pop result = %d\n", result);
    }

//------------------------------- EXIT WITH A SMILE ON YOUR FACE
	return (AMMX_RETURN_OK);
}
