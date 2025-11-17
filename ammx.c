/*
 *  $VER:       ammx.c 1.1
 *  $DATE:      2023-12-01 (2025-11-16)
 *  $AUTHOR:    Goran (dejakju@gmail.com)
*/

//------------------------------- AMMX LIBRARIES
#include <inttypes.h>
#include <stdlib.h>
#include "libs/toolbox.h"
#include "libs/stack.h"


//------------------------------- MAIN ENTRY
int main()
{
//------------------------------- CODE PLAYGROUND

    ammx_version();

    entire_file_t f = ammx_read_entire_file("ammx.bin");
    printf("(binary size = %ld bytes)\n", f.Size);
    printf("Upper case letters: %.*s\n", 26, (char*) f.Contents + 0x41);
    printf("Lower case letters: %.*s\n", 26, (char*) f.Contents + 0x61);
    printf("Numbers: %.*s\n", 10, (char*) f.Contents + 0x30);
    ammx_free_entire_file(&f);

    stack_t myStack;
    init_stack(&myStack);

    for (int i = 15; i <= 20; i++) {
        push(&myStack, ammx_fib(i));
        push(&myStack, ammx_fact(i));
        printf("fib(%lld) = %lld, fact(%lld) = %lld\n", i, pop(&myStack), i, pop(&myStack));
    }

    char buffer[255];
    sprintf(buffer, "Date & Time: %s %s\n", ammx_getdate_static(), ammx_gettime_static());
    ammx_puts(buffer);

    printf("Press any key: ");
    int64_t c = ammx_getch();
    printf("\nYou pressed: %c [%lld]\n", (char)c, c);


//------------------------------- EXIT WITH A SMILE ON YOUR FACE
	return (AMMX_RETURN_OK);
}
