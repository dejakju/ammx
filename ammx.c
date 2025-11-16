/*
    $VER:       ammx.c 1.1
    $DATE:      2023-12-01 (2025-11-15)
    $AUTHOR:    Goran (dejakju@gmail.com)
*/


//------------------------------- AMMX LIBRARIES
// #include <conio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "libs/toolbox.h"


//------------------------------- MAIN ENTRY
int main()
{
//------------------------------- CODE PLAYGROUND

    ammx_version();


    // 11 characters required (DD.MM.YYYY + null terminator), 16 is safe.
    char date_buffer[16]; 
    if (ammx_getdate(date_buffer, sizeof(date_buffer)) > 0) {
        printf("Current Date: %s\n", date_buffer);
    }

    // Caller allocates the buffer on the stack (no heap required).
    char time_buffer[16];
    if (ammx_gettime(time_buffer, sizeof(time_buffer)) > 0) {
        printf("Current Time: %s\n", time_buffer);
    }

    entire_file_t f = ammx_read_entire_file("README.md");
    printf("file size: %d\n%s\n", f.Size, f.Contents);

    for (int i = 10; i < 20; i++)
        printf("Fib(%ld) = %ld\n", i, ammx_fib(i));

    f = ammx_read_entire_file("ammx.bin");
    printf("file size: %d\n%s\n", f.Size, f.Contents);
    ammx_free_entire_file(&f);

    long long a = 42, b = -12, c = -9, d = 5, e = 17;
    printf("ammx_maxofthree(%ld, %ld, %ld) = %ld\n", a, b, c, ammx_maxofthree(a, b, c));
    printf("ammx_maxofthree(%ld, %ld, %ld) = %ld\n", d, a, e, ammx_maxofthree(d, a, e));
    printf("ammx_maxofthree(%ld, %ld, %ld) = %ld\n", b, c, e, ammx_maxofthree(b, c, e));
    printf("ammx_maxofthree(%ld, %ld, %ld) = %ld\n", b, d, e, ammx_maxofthree(b, d, e));
    printf("ammx_maxofthree(%ld, %ld, %ld) = %ld\n", c, d, e, ammx_maxofthree(c, d, e));

    int initial_value = 42, result_asm = 0;
    result_asm = ammx_decrement(initial_value);
    printf("ammx_decrement(%d) = %d\n", initial_value, result_asm);
    printf("ammx_decrement(%d) = %d\n", -13,  ammx_decrement(-13));
    result_asm = ammx_increment(initial_value);
    printf("ammx_increment(%d) = %d\n", initial_value, result_asm);
    printf("ammx_increment(%d) = %d\n", -13,  ammx_increment(-13));

    struct stat file_stat;
    char filename[] = "ammx.bin";

    // Use stat() to fill the file_stat structure with metadata
    // Returns 0 on success, -1 on error.
    if (stat(filename, &file_stat) == -1) {
        perror("Error getting file stats");
        exit(EXIT_FAILURE);
    }

    // --- 1. File Size ---
    printf("File: %s\n", filename);
    printf("  Size: %ld bytes\n", (long)file_stat.st_size);

    // --- 2. File Modification Date ---
    // st_mtime holds the timestamp (time_t). ctime converts it to a readable string.
    printf("  Last Modified: %s", ctime(&file_stat.st_mtime));

    // --- 3. File Attributes / Type ---
    printf("  Attributes (Type): ");
    
    // S_ISREG, S_ISDIR, etc., are macros defined in <sys/stat.h> for checking st_mode.
    if (S_ISREG(file_stat.st_mode)) {
        printf("File\n");
    } else if (S_ISDIR(file_stat.st_mode)) {
        printf("Directory\n");
    } else {
        printf("Other Type\n");
    }
    
    // --- 4. File Permissions (Optional but useful) ---
    // Permissions are stored as bits in st_mode
    printf("  Permissions: (");
    printf( (file_stat.st_mode & S_IRUSR) ? "r" : "-"); // User Read
    printf( (file_stat.st_mode & S_IWUSR) ? "w" : "-"); // User Write
    printf( (file_stat.st_mode & S_IXUSR) ? "x" : "-"); // User Execute
    printf(")\n");

    printf("Date = %s, Time = %s\n", ammx_getdate_static(), ammx_gettime_static());

//------------------------------- EXIT WITH A SMILE ON YOUR FACE
	return (AMMX_RETURN_OK);
}
