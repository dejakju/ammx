/*
 *   $VER:       toolbox.c 1.1
 *   $DATE:      2023-12-01 (2025-11-15)
 *   $AUTHOR:    Goran (dejakju@gmail.com)
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

    char *build_info_string = NULL;

    // 1. Call the assembly function
    build_info_string = ammx_build(); 

    // 2. Check and use the string
    if (build_info_string != NULL) {
        printf("\x1b[1;36m AMMX\x1b[0m version %d.%d - %s\n", AMMX_VERSION, AMMX_REVISION, build_info_string);
        printf("Email: dejakju@gmail.com\n");
        printf("Web: https://github.com/dejakju/ammx\n");
        
        // 3. Free the heap memory
        free(build_info_string);
    }

    // 4. Good practice cleanup
    build_info_string = NULL;
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
ammx_swap(f64_t *a, f64_t *b)
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
ammx_push(stack_t *stack, int64_t value)
{
    if (stack->top >= AMMX_STACK_LENGTH - 1) return 0;

    stack->top++;
    stack->values[stack->top] = value;

    return 1;
}

int64_t 
ammx_peek(stack_t *stack)
{
    if (stack->top == AMMX_STACK_EMPTY) return AMMX_STACK_ISEMPTY;

    int64_t result = stack->values[stack->top];

    return result;
}

int64_t 
ammx_pop(stack_t *stack)
{
    if (stack->top == AMMX_STACK_EMPTY) return AMMX_STACK_ISEMPTY;

    int64_t result = stack->values[stack->top];
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
    // 1. Define the static array for string mapping.
    // The index of the array must match the enum value.
    static const char *const DAY_NAMES[] = {
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday",
        "Sunday"
    };

    // Calculate the size of the array for bounds checking.
    // The use of AMMX_DAYOFWEEK_COUNT from the enum is safer if available.
    const size_t ARRAY_LEN = ARRAY_SIZE(DAY_NAMES);

    // 2. Perform bounds checking and return the string.
    // If the 'day' is out of bounds, return the error string "(null)".
    if (day >= 0 && day < ARRAY_LEN) {
        return (char*)DAY_NAMES[day];
    } else {
        return "(null)";
    }
}

/**
 * Returns the current date string (format "DD.MM.YYYY").
 * * WARNING: This function is NOT thread-safe. 
 * If two threads call this function simultaneously, they will both try to write 
 * to the same static buffer, leading to a race condition and corrupted data.
 *
 * @return A pointer to a static, internal char buffer containing the date string.
 */
char*
ammx_getdate_static()
{
    // The 'static' keyword ensures the memory for 'fmt' is allocated once in 
    // the data segment and persists across all function calls.
    // Because it's not heap memory, NO 'free()' is needed, eliminating the leak.
    static char sdate[16];
    
    // Get current time
    time_t now = time(0);
    struct tm *datetime = localtime(&now);
    
    // strftime formats the date into the static buffer.
    strftime(sdate, 16, "%d.%m.%Y", datetime);
    
    // Return the pointer to the static buffer.
    return sdate;
}

/**
 * Returns the current time string (format "HH:mm:ss").
 * * WARNING: This version is NOT thread-safe as it uses a static buffer.
 * If two threads call this function simultaneously, they will both try to write 
 * to the same static buffer, leading to a race condition and corrupted data.
 *
 * @return A pointer to a static, internal char buffer containing the time string.
 */
char*
ammx_gettime_static()
{
    // Static storage duration: The buffer exists for the program's lifetime.
    // It is allocated in the data segment, NOT the heap, so no free() is needed.
    static char stime[16];
    
    time_t now = time(0);
    struct tm *datetime = localtime(&now);
    
    strftime(stime, 16, "%H:%M:%S", datetime);
    
    return stime; // Return pointer to the static buffer.
}

/**
 * Stores the current date string (format "DD.MM.YYYY") in the provided buffer.
 * The caller is responsible for allocating and managing the buffer memory.
 *
 * @param buffer Pointer to the caller-allocated buffer.
 * @param buffer_size The size of the buffer in bytes.
 * @return The number of characters placed in the array (excluding the null terminator), or 0 on error.
 */
int
ammx_getdate(char* buffer, size_t buffer_size)
{
    // The buffer is managed by the caller, so no heap allocation is needed here.

    if (buffer == NULL || buffer_size == 0) {
        return 0; // Return 0 for failure (similar to strftime standard)
    }

    // Get current time
    time_t now = time(0);
    struct tm *datetime = localtime(&now);

    // strftime writes the formatted date directly to the caller's buffer.
    size_t dt_length = strftime(buffer, buffer_size, "%d.%m.%Y", datetime);

    return (int)dt_length;
}

/**
 * Stores the current time string (format "HH:mm:ss") in the provided buffer.
 * The caller is responsible for allocating and managing the buffer memory.
 *
 * @param buffer Pointer to the caller-allocated buffer.
 * @param buffer_size The size of the buffer in bytes.
 * @return The number of characters placed in the array (excluding the null terminator), or -1 on error.
 */
int
ammx_gettime(char* buffer, size_t buffer_size)
{
    // The buffer is passed in by the caller, so we don't need malloc/free here.

    if (buffer == NULL || buffer_size == 0) {
        return -1; // Error check for invalid buffer
    }

    time_t now = time(0);
    struct tm *datetime = localtime(&now);

    // strftime writes directly to the caller's buffer.
    size_t dt_length = strftime(buffer, buffer_size, "%H:%M:%S", datetime);

    return (int)dt_length;
}


/**
 * Reads the entire contents of a file into a newly allocated buffer.
 * The caller is responsible for freeing the Result.Contents buffer when done.
 *
 * @param filename The path to the file.
 * @return An entire_file_t structure. On success, Size > 0 and Contents != NULL.
 * On failure, Size = 0 and Contents = NULL.
 */
entire_file_t
ammx_read_entire_file(char* filename)
{
    entire_file_t Result = {0};
    FILE* file = NULL;
    long file_size_l = 0; // Use long for ftell, then cast/check against size_t

    // 1. Attempt to open the file for reading in binary mode.
    file = fopen(filename, "rb");
    if (!file)
    {
        // Use fprintf(stderr, ...) for better error reporting outside the main flow.
        fprintf(stderr, "ERROR: Unable to open file \"%s\"\n", filename);
        // Result is already {0, NULL}, so we return immediately.
        return Result;
    }

    // 2. Determine file size.
    // Error check for fseek and ftell is robust.
    if (fseek(file, 0, SEEK_END) != 0 || (file_size_l = ftell(file)) == -1)
    {
        fprintf(stderr, "ERROR: Cannot determine size of file \"%s\"\n", filename);
        // Jump to the cleanup label to close the file.
        goto cleanup;
    }

    // A. Check for potential overflow: long to size_t.
    // Although rare on modern systems, it ensures size_t can hold the size.
    if (file_size_l < 0 || (size_t)file_size_l != file_size_l)
    {
        fprintf(stderr, "ERROR: File \"%s\" is too large to handle with size_t (%ld bytes).\n", filename, file_size_l);
        goto cleanup;
    }
    Result.Size = (size_t)file_size_l;

    // 3. Allocate memory, including an extra byte for a null terminator (optional but safe).
    // Note: If Result.Size is 0 (empty file), malloc(0) might return NULL or a valid pointer.
    // The conditional check below handles both cases gracefully.
    
    // Allocate space for the file contents + 1 byte for null terminator (for text safety)
    Result.Contents = malloc(Result.Size + 1);
    
    if (!Result.Contents)
    {
        fprintf(stderr, "ERROR: Failed to allocate %zu bytes for file \"%s\".\n", Result.Size + 1, filename);
        goto cleanup;
    }

        // B. Safely null-terminate the allocated buffer (even for binary data, for safety).
    ((char*)Result.Contents)[Result.Size] = '\0';
    
    // 4. Read contents.
    // Reset file pointer to the beginning.
    fseek(file, 0, SEEK_SET);

    // Read the file. fread returns the number of items successfully read.
    size_t items_read = fread(Result.Contents, Result.Size, 1, file);
    
    if (items_read != 1)
    {
        // An error occurred during reading, or not all bytes were read.
        // This is a critical failure.
        fprintf(stderr, "ERROR: Failed to read all bytes from file \"%s\".\n", filename);
        
        // We must free the memory we successfully allocated before jumping to cleanup.
        free(Result.Contents);
        Result.Contents = NULL;
        Result.Size = 0;
        
        goto cleanup;
    }

    // 5. Final Cleanup (always executed).
cleanup:
    // This label ensures fclose is called regardless of where an error occurred.
    if (file)
    {
        fclose(file);
    }

    return Result;
}

/**
 * Safely frees the memory allocated for file contents and resets the structure members.
 * This function is robust against being called with a NULL pointer.
 *
 * @param file A pointer to the entire_file_t structure to be cleaned up.
 */
void
ammx_free_entire_file(entire_file_t* file)
{
    // 1. Robustness Check: Ensure the input pointer itself is not NULL.
    // Accessing 'file->Contents' when 'file' is NULL causes a segmentation fault/crash.
    if (!file)
    {
        return; // Safety first: Do nothing if the pointer to the structure is invalid.
    }

    // 2. Core Cleanup: Check and free the contents buffer.
    if (file->Contents)
    {
        free(file->Contents);
        // Best practice: Set the pointer to NULL after freeing to prevent
        // "double-free" or "use-after-free" bugs if the function is called again.
        file->Contents = NULL; 
    }
    
    // 3. Cleanup Metadata: Reset the size.
    // This is good practice to ensure the structure is marked as "empty" or "cleared."
    file->Size = 0;
}
