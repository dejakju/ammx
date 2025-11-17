/*
 *  $VER:       toolbox.c 1.1
 *  $DATE:      2023-12-01 (2025-11-16)
 *  $AUTHOR:    Goran (dejakju@gmail.com)
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

    build_info_string = ammx_build(); 

    if (build_info_string != NULL) {
        printf("\x1b[1;36m AMMX\x1b[0m version %d.%d - %s\n", AMMX_VERSION, AMMX_REVISION, build_info_string);
        printf("Email: dejakju@gmail.com\n");
        printf("Web: https://github.com/dejakju/ammx\n");
        
        free(build_info_string);
    }

    build_info_string = NULL;
}

int64_t
ammx_and(int64_t a, int64_t b)
{
	return (a && b);
}

int64_t
ammx_or(int64_t a, int64_t b)
{
	return (a || b);
}

int64_t
ammx_not(int64_t a)
{
	return (!a);
}

int64_t
ammx_nand(int64_t a, int64_t b)
{
	return !(a && b);
}

int64_t
ammx_nor(int64_t a, int64_t b)
{
	return !(a || b);
}

int64_t
ammx_xor(int64_t a, int64_t b)
{
	return (!a && b || a && !b);
}

int64_t
ammx_xnor(int64_t a, int64_t b)
{
	return (a && b || !a && !b);
}

int64_t
ammx_imp(int64_t a, int64_t b)
{
	return !(a && !b);
}

int64_t
ammx_nimp(int64_t a, int64_t b)
{
	return (a && !b);
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
