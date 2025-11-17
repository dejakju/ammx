/*
 *  $VER:       ammx.c 1.2
 *  $DATE:      2023-12-01 (2025-11-17)
 *  $AUTHOR:    Goran (dejakju@gmail.com)
 */

//------------------------------- AMMX LIBRARIES
#include "libs/toolbox.h"
//------------------------------- MAIN ENTRY
int main()
{
    //------------------------------- CODE PLAYGROUND
    
    ammx_version();

    int32_t day, year;
    int32_t hours, minutes, seconds;
    AMMX_MonthTypeDef month;

    if (ammx_get_datestamp(&day, &month, &year) && ammx_get_timestamp(&hours, &minutes, &seconds))
        printf("Current date: %d. %s %d - Current time: %d:%d:%d\n", day, ammx_string_from_month(month), year, hours, minutes, seconds);

    entire_file_t f = ammx_read_entire_file("ammx.bin");
    printf("(binary size = %ld bytes)\n", f.Size);
    printf("Upper case letters: %.*s\n", 26, (char*) f.Contents + 0x41);
    printf("Lower case letters: %.*s\n", 26, (char*) f.Contents + 0x61);
    printf("Numbers: %.*s\n", 10, (char*) f.Contents + 0x30);
    ammx_free_entire_file(&f);

    stack_t myStack;
    init_stack(&myStack);

    for (int i = 16; i <= 20; i++) {
        push(&myStack, ammx_fib(i));
        push(&myStack, ammx_fact(i));
        printf("fib(%lld) = %lld, fact(%lld) = %lld\n", i, pop(&myStack), i, pop(&myStack));
    }

    for (int i = 2024; i < 2029; i++) {
        push(&myStack, i);
        push(&myStack, ammx_is_leap_year(i));
        printf("Year = %lld %s a leap year\n", pop(&myStack), (pop(&myStack) ? "is" : "is not"));
    }

    uint64_t flags = 0;
    flags = AMMX_EXEC_LIST | AMMX_EXEC_NODE | AMMX_EXEC_TASK;
    flags |= AMMX_EXEC_SEMAPHORE;
    flags &= ~(AMMX_EXEC_NODE);
    flags &= ~(AMMX_EXEC_LIST);
    flags |= AMMX_EXEC_DOS;
    flags &= ~(AMMX_EXEC_SEMAPHORE);

    for (int i = 0; i < 64; i++) {
        if (IS_BIT_SET(flags, i)) {
            printf("+");
        } else {
            printf(".");
        }
    }
    printf("\n");

    // logic tests

    int32_t x, y, z;
    int64_t a, b;

    /*** AND ***/
    x = true; y = true;
    z = ammx_and(x, y);
    printf("AND(%ld, %ld) = %ld\n", x, y, z);
    x = true; y = false;
    z = ammx_and(x, y);
    printf("AND(%ld, %ld) = %ld\n", x, y, z);
    x = false; y = true;
    z = ammx_and(x, y);
    printf("AND(%ld, %ld) = %ld\n", x, y, z);
    x = false; y = false;
    z = ammx_and(x, y);
    printf("AND(%ld, %ld) = %ld\n", x, y, z);

    /*** OR ***/
    x = true; y = true;
    z = ammx_or(x, y);
    printf("OR(%ld, %ld) = %ld\n", x, y, z);
    x = true; y = false;
    z = ammx_or(x, y);
    printf("OR(%ld, %ld) = %ld\n", x, y, z);
    x = false; y = true;
    z = ammx_or(x, y);
    printf("OR(%ld, %ld) = %ld\n", x, y, z);
    x = false; y = false;
    z = ammx_or(x, y);
    printf("OR(%ld, %ld) = %ld\n", x, y, z);

    /*** NOT ***/
    x = true;
    z = ammx_not(x);
    printf("NOT(%ld) = %ld\n", x, z);
    x = false;
    z = ammx_not(x);
    printf("NOT(%ld) = %ld\n", x, z);

    /*** NAND ***/
    x = true; y = true;
    z = ammx_nand(x, y);
    printf("NAND(%ld, %ld) = %ld\n", x, y, z);
    x = true; y = false;
    z = ammx_nand(x, y);
    printf("NAND(%ld, %ld) = %ld\n", x, y, z);
    x = false; y = true;
    z = ammx_nand(x, y);
    printf("NAND(%ld, %ld) = %ld\n", x, y, z);
    x = false; y = false;
    z = ammx_nand(x, y);
    printf("NAND(%ld, %ld) = %ld\n", x, y, z);

    /*** NOR ***/
    x = true; y = true;
    z = ammx_nor(x, y);
    printf("NOR(%ld, %ld) = %ld\n", x, y, z);
    x = true; y = false;
    z = ammx_nor(x, y);
    printf("NOR(%ld, %ld) = %ld\n", x, y, z);
    x = false; y = true;
    z = ammx_nor(x, y);
    printf("NOR(%ld, %ld) = %ld\n", x, y, z);
    x = false; y = false;
    z = ammx_nor(x, y);
    printf("NOR(%ld, %ld) = %ld\n", x, y, z);

    /*** XOR ***/
    x = true; y = true;
    z = ammx_xor(x, y);
    printf("XOR(%ld, %ld) = %ld\n", x, y, z);
    x = true; y = false;
    z = ammx_xor(x, y);
    printf("XOR(%ld, %ld) = %ld\n", x, y, z);
    x = false; y = true;
    z = ammx_xor(x, y);
    printf("XOR(%ld, %ld) = %ld\n", x, y, z);
    x = false; y = false;
    z = ammx_xor(x, y);
    printf("XOR(%ld, %ld) = %ld\n", x, y, z);

    /*** XNOR ***/
    x = true; y = true;
    z = ammx_xnor(x, y);
    printf("XNOR(%ld, %ld) = %ld\n", x, y, z);
    x = true; y = false;
    z = ammx_xnor(x, y);
    printf("XNOR(%ld, %ld) = %ld\n", x, y, z);
    x = false; y = true;
    z = ammx_xnor(x, y);
    printf("XNOR(%ld, %ld) = %ld\n", x, y, z);
    x = false; y = false;
    z = ammx_xnor(x, y);
    printf("XNOR(%ld, %ld) = %ld\n", x, y, z);

    /*** IMP ***/
    x = true; y = true;
    z = ammx_imp(x, y);
    printf("IMP(%ld, %ld) = %ld\n", x, y, z);
    x = true; y = false;
    z = ammx_imp(x, y);
    printf("IMP(%ld, %ld) = %ld\n", x, y, z);
    x = false; y = true;
    z = ammx_imp(x, y);
    printf("IMP(%ld, %ld) = %ld\n", x, y, z);
    x = false; y = false;
    z = ammx_imp(x, y);
    printf("IMP(%ld, %ld) = %ld\n", x, y, z);

    /*** NIMP ***/
    x = true; y = true;
    z = ammx_nimp(x, y);
    printf("NIMP(%ld, %ld) = %ld\n", x, y, z);
    x = true; y = false;
    z = ammx_nimp(x, y);
    printf("NIMP(%ld, %ld) = %ld\n", x, y, z);
    x = false; y = true;
    z = ammx_nimp(x, y);
    printf("NIMP(%ld, %ld) = %ld\n", x, y, z);
    x = false; y = false;
    z = ammx_nimp(x, y);
    printf("NIMP(%ld, %ld) = %ld\n", x, y, z);

    /*** ABS ***/
    x = -2520;
    z = ammx_abs(x);
    printf("ABS(%ld) = %ld\n", x, z);
    x = 171;
    z = ammx_abs(x);
    printf("ABS(%ld) = %ld\n", x, z);

    /*** MAX ***/
    x = 42; y = 13;
    z = ammx_max(x, y);
    printf("MAX(%ld, %ld) = %ld\n", x, y, z);
    x = -42; y = 13;
    z = ammx_max(x, y);
    printf("MAX(%ld, %ld) = %ld\n", x, y, z);
    x = 13; y = 42;
    z = ammx_max(x, y);
    printf("MAX(%ld, %ld) = %ld\n", x, y, z);
    x = 13; y = -42;
    z = ammx_max(x, y);
    printf("MAX(%ld, %ld) = %ld\n", x, y, z);

    /*** MIN ***/
    x = 42; y = 13;
    z = ammx_min(x, y);
    printf("MIN(%ld, %ld) = %ld\n", x, y, z);
    x = -42; y = 13;
    z = ammx_min(x, y);
    printf("MIN(%ld, %ld) = %ld\n", x, y, z);
    x = 13; y = 42;
    z = ammx_min(x, y);
    printf("MIN(%ld, %ld) = %ld\n", x, y, z);
    x = 13; y = -42;
    z = ammx_min(x, y);
    printf("MIN(%ld, %ld) = %ld\n", x, y, z);

    /*** SWAP ***/
    a = 5; b = 7;
    printf("Before SWAP(): a = %ld, b = %ld\n", a, b);
    ammx_swap(&a, &b);
    printf("After  SWAP(): a = %ld, b = %ld\n", a, b);
    a = -5; b = -7;
    printf("Before SWAP(): a = %ld, b = %ld\n", a, b);
    ammx_swap(&a, &b);
    printf("After  SWAP(): a = %ld, b = %ld\n", a, b);
    a = -5; b = 7;
    printf("Before SWAP(): a = %ld, b = %ld\n", a, b);
    ammx_swap(&a, &b);
    printf("After  SWAP(): a = %ld, b = %ld\n", a, b);

//------------------------------- EXIT WITH A SMILE ON YOUR FACE
	return (AMMX_RETURN_OK);
}
