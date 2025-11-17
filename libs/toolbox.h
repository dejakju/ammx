/*
 *  $VER:       toolbox.h 1.2
 *  $DATE:      2023-12-01 (2025-11-17)
 *  $AUTHOR:    Goran (dejakju@gmail.com)
*/

#ifndef LIBS_TOOLBOX_H
#define LIBS_TOOLBOX_H


////////////////////////////////
//------------------------------- Version / Revison
// NOTE(dejakju): 

#define AMMX_VERSION    1
#define AMMX_REVISION   1


////////////////////////////////
//------------------------------- Dependencies
// NOTE(dejakju): 

#include <stdio.h>
#include <stdint.h>
#include "datetime.h"
#include "stack.h"


////////////////////////////////
//------------------------------- Macros
// NOTE(dejakju): 

#define CLR_MEM_ZERO(Destination,Length) memset((Destination),0,(Length))
#define CLR_MEM_VAL(Destination,Length,X) memset((Destination),(X),(Length))
#define ARRAY_SIZE(X) (sizeof(X)/sizeof(X[0]))
#define SET_BIT(BF, N) (BF |= ((uint64_t)0x0000000000000001 << N))
#define CLR_BIT(BF, N) (BF &= ~((uint64_t)0x0000000000000001 << N))
#define IS_BIT_SET(BF, N) ((BF >> N) & 0x1)


////////////////////////////////
//------------------------------- Basic Types
// NOTE(dejakju): 

typedef float               f32_t;
typedef double              f64_t;
typedef char*               string_t;
typedef signed char         byte_t;
typedef unsigned char       ubyte_t;
typedef unsigned char       bytebits_t;
typedef short               word_t;
typedef unsigned short      uword_t;
typedef unsigned short      wordbits_t;
typedef long long           long_t;
typedef unsigned long long  ulong_t;
typedef unsigned long long  longbits_t;


////////////////////////////////
//------------------------------- Enum Types
// NOTE(dejakju): 

typedef enum AMMX_ReturnCodeTypeDef {
    AMMX_RETURN_OK      = 0x00U,
    AMMX_RETURN_WARN    = 0x05U,
    AMMX_RETURN_ERROR   = 0x0AU,
    AMMX_RETURN_FAIL    = 0x14U
} AMMX_ReturnCodeTypeDef;

typedef enum AMMX_StdHandleTypeDef {
    AMMX_STD_INPUT_HANDLE   = 0x00U,
    AMMX_STD_OUTPUT_HANDLE  = 0x01U,
    AMMX_STD_ERROR_HANDLE   = 0x02U
} AMMX_StdHandleTypeDef;

typedef enum AMMX_StatusTypeDef {
    AMMX_STATUS_OK      = 0x00U,
    AMMX_STATUS_ERROR   = 0x01U,
    AMMX_STATUS_BUSY    = 0x02U,
    AMMX_STATUS_TIMEOUT = 0x03U
} AMMX_StatusTypeDef;

typedef enum AMMX_ExecTypeDef {
    AMMX_EXEC_DEFAULT   = 0x1,
    AMMX_EXEC_DOS       = 0x2,
    AMMX_EXEC_EVENT     = 0x4,
    AMMX_EXEC_EXEC      = 0x8,
    AMMX_EXEC_LIBRARY   = 0x10,
    AMMX_EXEC_LIST      = 0x20,
    AMMX_EXEC_NODE      = 0x40,
    AMMX_EXEC_SEMAPHORE = 0x80,
    AMMX_EXEC_TASK      = 0x100
} AMMX_ExecTypeDef;


////////////////////////////////
//------------------------------- Basic Constants
// NOTE(dejakju):

static f32_t pi_f32 = 3.14159265359f;
static f32_t e_f32  = 2.71828182846f;
static f64_t pi_f64  = 3.14159265359;
static f64_t tau_f64 = 6.28318530718;


////////////////////////////////
//------------------------------- Compound Types
// NOTE(dejakju): 

typedef struct entire_file_t
{
    size_t Size;
    void *Contents;
} entire_file_t ;

typedef struct v2s32_t {
    int32_t x;
    int32_t y;
} v2s32_t;

typedef struct v3s32_t {
    int32_t x;
    int32_t y;
    int32_t z;
} v3s32_t;

typedef struct v4s32_t {
    int32_t x;
    int32_t y;
    int32_t z;
    int32_t w;
} v4s32_t;

typedef struct v2f32_t {
    f32_t x;
    f32_t y;
} v2f32_t;

typedef struct v3f32_t {
    f32_t x;
    f32_t y;
    f32_t z;
} v3f32_t;

typedef struct v4f32_t {
    f32_t x;
    f32_t y;
    f32_t z;
    f32_t w;
} v4f32_t;

typedef struct v2f64_t {
    f64_t x;
    f64_t y;
} v2f64_t;

typedef struct v3f64_t {
    f64_t x;
    f64_t y;
    f64_t z;
} v3f64_t;

typedef struct v4f64_t {
    f64_t x;
    f64_t y;
    f64_t z;
    f64_t w;
} v4f64_t;


////////////////////////////////
//------------------------------- String Types
// NOTE(dejakju): 

typedef struct string8_t {
    uint8_t *str;
    uint64_t size;
} string8_t;

typedef struct string16_t {
    uint16_t *str;
    uint64_t size;
} string16_t;

typedef struct string32_t {
    uint32_t *str;
    uint64_t size;
} string32_t;

typedef struct string_node_t {
    struct string_node_t *next;
    string8_t string;
} string_node_t;

typedef struct string_list_t {
    string_node_t *first;
    string_node_t *last;
    uint64_t node_count;
    uint64_t total_size;
} string_list_t;

typedef struct string_join_t {
    string8_t pre;
    string8_t mid;
    string8_t post;
} string_join_t;


////////////////////////////////
//------------------------------- Assembler Modules
// NOTE(dejakju): 

extern char*    ammx_build(void);
extern int64_t  ammx_decrement(int64_t);
extern int64_t  ammx_fib(int64_t);
extern int64_t  ammx_fact(int64_t);
extern int64_t  ammx_getch(void);
extern int64_t  ammx_getchar(void);
extern int64_t  ammx_increment(int64_t);
extern int64_t  ammx_maxofthree(int64_t, int64_t, int64_t);
extern int64_t  ammx_ncr(int64_t, int64_t);
extern int64_t  ammx_puts(const char*);


////////////////////////////////
//------------------------------- Function Declarations
// NOTE(dejakju): 

void ammx_version();

int64_t ammx_and(int64_t a, int64_t b);
int64_t ammx_or(int64_t a, int64_t b);
int64_t ammx_not(int64_t a);
int64_t ammx_nand(int64_t a, int64_t b);
int64_t ammx_nor(int64_t a, int64_t b);
int64_t ammx_xor(int64_t a, int64_t b);
int64_t ammx_xnor(int64_t a, int64_t b);
int64_t ammx_imp(int64_t a, int64_t b);
int64_t ammx_nimp(int64_t a, int64_t b);

int64_t ammx_abs(int64_t a);
int64_t ammx_max(int64_t a, int64_t b);
int64_t ammx_min(int64_t a, int64_t b);

void ammx_swap(int64_t *a, int64_t *b);
void ammx_fflush();

char* ammx_strrev(char *string);
void ammx_d2c(int64_t number, char *buffer);
int64_t ammx_c2d(char *string);

entire_file_t ammx_read_entire_file(char* filename);
void ammx_free_entire_file(entire_file_t* file);

#endif
