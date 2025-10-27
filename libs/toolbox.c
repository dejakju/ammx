/*
    $VER:       toolbox.c 1.0
    $DATE:      2024-10-05 (2025-10-18)
    $AUTHOR:    Goran (dejakju@gmail.com)
*/

////////////////////////////////
//------------------------------- Dependencies
// NOTE(dejakju): 

#include "toolbox.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////////////////////////////
//------------------------------- Implementations
// NOTE(dejakju): 

void
ammx_version() {
    printf("\x1b[1;36m AMMX\x1b[0m version %d.%d (compiled %s, %s)\n", AMMX_VERSION, AMMX_REVISION, __TIME__, __DATE__);
    printf("Email: dejakju@gmail.com\n");
    printf("Web: https://github.com/dejakju/ammx\n");
}

b32_t
ammx_and(b32_t a, b32_t b)
{
	return (a && b);
}

b32_t
ammx_or(b32_t a, b32_t b)
{
	return (a || b);
}

b32_t
ammx_not(b32_t a)
{
	return (!a);
}

b32_t
ammx_nand(b32_t a, b32_t b)
{
	return !(a && b);
}

b32_t
ammx_nor(b32_t a, b32_t b)
{
	return !(a || b);
}

b32_t
ammx_xor(b32_t a, b32_t b)
{
	return (!a && b || a && !b);
}

b32_t
ammx_xnor(b32_t a, b32_t b)
{
	return (a && b || !a && !b);
}

b32_t
ammx_imp(b32_t a, b32_t b)
{
	return !(a && !b);
}

int64_t
ammx_abs(int64_t a)
{
	return (a < 0) ? -a : a;
}

int64_t
ammx_max(int64_t a, int64_t b)
{
	return (a > b) ? a : b;
}

int64_t
ammx_min(int64_t a, int64_t b)
{
	return (a < b) ? a : b;
}

void
ammx_swap(int64_t *a, int64_t *b)
{
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
}

void
ammx_fflush()
{
    while(getchar() != '\n');
}

char*
ammx_strrev(char *string)
{
    int64_t length = strlen(string);
    int64_t middle = length / 2;
    char tmp;
    for (int64_t i = 0; i < middle; i++) {
        tmp = string[i];
        string[i] = string[length - i - 1];
        string[length - i - 1] = tmp;
    }
    return string;
}

void 
ammx_d2c(int64_t number, char *buffer)
{
    int64_t length = 32;
    int64_t idx = 0;

    for (int i = (length - 1); i >= 0; i--) {
        sprintf(&buffer[idx], "%lld", (int64_t)((number >> i) & 1));
        ++idx;
    }

    buffer[idx] = '\0';
}

int64_t 
ammx_c2d(char *string)
{
    int64_t slen = strlen(string);
    int64_t total = 0;
    int64_t decval = 1;

    for (int i = (slen - 1); i >= 0; i--) {
        if (string[i] == '1') total += decval;
        decval *= 2;
    }

    return total;
}

b32_t
ammx_push(stack_t *stack, int32_t value)
{
    if (stack->top >= AMMX_STACK_LENGTH - 1) return 0;

    stack->top++;
    stack->values[stack->top] = value;

    return 1;
}

int32_t 
ammx_peek(stack_t *stack)
{
    if (stack->top == AMMX_STACK_EMPTY) return AMMX_STACK_ISEMPTY;

    int32_t result = stack->values[stack->top];

    return result;
}

int32_t 
ammx_pop(stack_t *stack)
{
    if (stack->top == AMMX_STACK_EMPTY) return AMMX_STACK_ISEMPTY;

    int32_t result = stack->values[stack->top];
    stack->top--;

    return result;
}

b32_t
ammx_is_leap_year(int32_t year)
{
    if (year % 4 != 0) return 0;
    else if (year % 100 != 0) return 1;
    else if (year % 400 != 0) return 0;
    else return 1;
}

char*
ammx_string_from_month(AMMX_MonthTypeDef month)
{
    char *result = "(null)";
    switch (month) {
        case AMMX_JANUARY:
        {
            result = "January";
        } break;
        case AMMX_FEBRUARY:
        {
            result = "February";
        } break;
        case AMMX_MARCH:
        {
            result = "March";
        } break;
        case AMMX_APRIL:
        {
            result = "April";
        } break;
        case AMMX_MAY:
        {
            result = "May";
        } break;
        case AMMX_JUNE:
        {
            result = "June";
        } break;
        case AMMX_JULY:
        {
            result = "July";
        } break;
        case AMMX_AUGUST:
        {
            result = "August";
        } break;
        case AMMX_SEPTEMBER:
        {
            result = "September";
        } break;
        case AMMX_OCTOBER:
        {
            result = "October";
        } break;
        case AMMX_NOVEMBER:
        {
            result = "November";
        } break;
        case AMMX_DECEMBER:
        {
            result = "December";
        } break;
    }
    return (result);
}

char*
ammx_string_from_dayofweek(AMMX_DayOfWeekTypeDef day)
{
    char *result = "(null)";
    switch (day) {
        case AMMX_MONDAY:
        {
            result = "Monday";
        } break;
        case AMMX_TUESDAY:
        {
            result = "Tuesday";
        } break;
        case AMMX_WEDNESDAY:
        {
            result = "Wednesday";
        } break;
        case AMMX_THURSDAY:
        {
            result = "Thursday";
        } break;
        case AMMX_FRIDAY:
        {
            result = "Friday";
        } break;
        case AMMX_SATURDAY:
        {
            result = "Saturday";
        } break;
        case AMMX_SUNDAY:
        {
            result = "Sunday";
        } break;
    }
    return (result);
}

char*
ammx_getdate()
{
    char *fmtdt = "(null)";
    time_t now = time(0);
    struct tm *datetime = localtime(&now);
    int dt_length = strftime(fmtdt, 16, "%d.%m.%Y", datetime);
    return fmtdt;
}

char*
ammx_gettime()
{
    char *fmtdt = "(null)";
    time_t now = time(0);
    struct tm *datetime = localtime(&now);
    int dt_length = strftime(fmtdt, 16, "%H:%M:%S", datetime);
    return fmtdt;
}

/******************************************************* */

entire_file_t
ammx_read_entire_file(char* filename)
{
    entire_file_t Result = {0};

    FILE* file = fopen(filename, "rb");
    if(file)
    {
        fseek(file, 0, SEEK_END);
        Result.Size = ftell(file);
        fseek(file, 0, SEEK_SET);
        
        Result.Contents = (void *)malloc(Result.Size);
        if(Result.Contents)
        {
            if(Result.Size)
            {
                fread(Result.Contents, Result.Size, 1, file);
            }
        }
        else
        {
            Result.Contents = 0;
            Result.Size = 0;
        }
        
        fclose(file);
    }
    else
    {
        printf("ERROR: Unable to load \"%s\"\n", filename);
    }
    
    
    return(Result);
}

void
ammx_free_entire_file(entire_file_t* file)
{
    if(file->Contents)
    {
        free(file->Contents);
        file->Contents = 0;
    }
    
    file->Size = 0;
}
