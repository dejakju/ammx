/*
    $VER:       ammx.c 1.1
    $DATE:      2023-12-01 (2025-11-15)
    $AUTHOR:    Goran (dejakju@gmail.com)
*/
//------------------------------- AMMX LIBRARIES
#include <inttypes.h>
#include <stdlib.h>
#include "libs/toolbox.h"


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


//------------------------------- EXIT WITH A SMILE ON YOUR FACE
	return (AMMX_RETURN_OK);
}
