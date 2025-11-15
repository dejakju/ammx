/*
    $VER:       ammx.c 1.1
    $DATE:      2023-12-01 (2025-11-15)
    $AUTHOR:    Goran (dejakju@gmail.com)
*/


//------------------------------- AMMX LIBRARIES
// #include <conio.h>
#include <inttypes.h>
#include <stdlib.h>
#include "libs/toolbox.h"


//------------------------------- MAIN ENTRY
int main()
{
//------------------------------- CODE PLAYGROUND

    ammx_version();

    long long a = 42, b = -12, c = -9, d = 5, e = 17;
   
    printf("ammx_maxofthree(%ld, %ld, %ld) = %ld\n", a, b, c, ammx_maxofthree(a, b, c));
    printf("ammx_maxofthree(%ld, %ld, %ld) = %ld\n", d, a, e, ammx_maxofthree(d, a, e));
    printf("ammx_maxofthree(%ld, %ld, %ld) = %ld\n", b, c, e, ammx_maxofthree(b, c, e));
    printf("ammx_maxofthree(%ld, %ld, %ld) = %ld\n", a, d, e, ammx_maxofthree(a, d, e));
    printf("ammx_maxofthree(%ld, %ld, %ld) = %ld\n", c, d, e, ammx_maxofthree(c, d, e));

    int initial_value = 42;
    int result_asm = 0;

    result_asm = ammx_decrement(initial_value);
    printf("Assembly Function Call: ammx_decrement(%d) = %d\n", initial_value, result_asm);
    printf("Assembly Function Call: ammx_decrement(%d) = %d\n", -13,  ammx_decrement(-13));

    result_asm = ammx_increment(initial_value);
    printf("Assembly Function Call: ammx_increment(%d) = %d\n", initial_value, result_asm);
    printf("Assembly Function Call: ammx_increment(%d) = %d\n", -13,  ammx_increment(-13));

//------------------------------- EXIT WITH A SMILE ON YOUR FACE
	return (AMMX_RETURN_OK);
}
