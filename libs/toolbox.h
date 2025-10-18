/*
    $VER:       toolbox.h 1.0
    $DATE:      2024-10-05 (2025-10-18)
    $AUTHOR:    Goran (dejakju@gmail.com)
*/

#ifndef LIBS_TOOLBOX_H
#define LIBS_TOOLBOX_H


////////////////////////////////
//------------------------------- Version
// NOTE(dejakju): 

#define AMMX_VERSION    1
#define AMMX_REVISION   0


////////////////////////////////
//------------------------------- Dependencies
// NOTE(dejakju): 

#include <stdio.h>
#include <stdint.h>
#include <time.h>


////////////////////////////////
//------------------------------- Basic Types
// NOTE(dejakju): 

typedef int8_t  b8_t;
typedef int16_t b16_t;
typedef int32_t b32_t;
typedef int64_t b64_t;
typedef float   f32_t;
typedef double  f64_t;
typedef char*   string_t;

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
//------------------------------- Basic Constants
// NOTE(dejakju):

static int8_t  min_uint8_t  = (uint8_t) 0x80;
static int16_t min_uint16_t = (uint16_t)0x8000;
static int32_t min_uint32_t = (uint32_t)0x80000000;
static int64_t min_uint64_t = (uint64_t)0x8000000000000000llu;

static int8_t  max_int8_t  = (int8_t) 0x7f;
static int16_t max_int16_t = (int16_t)0x7fff;
static int32_t max_int32_t = (int32_t)0x7fffffff;
static int64_t max_int64_t = (int64_t)0x7fffffffffffffffllu;

static uint8_t  max_U8  = 0xff;
static uint16_t max_U16 = 0xffff;
static uint32_t max_U32 = 0xffffffff;
static uint64_t max_U64 = 0xffffffffffffffffllu;

static uint64_t magic_number = 0b100111011000;

static f32_t pi_f32 = 3.14159265359f;
static f32_t e_f32  = 2.71828182846f;

static f64_t pi_f64  = 3.14159265359;
static f64_t tau_f64 = 6.28318530718;


////////////////////////////////
//------------------------------- Compound Types
// NOTE(dejakju): 

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
//------------------------------- Macros
// NOTE(dejakju): 

#define CLR_MEM_ZERO(Destination,Length) memset((Destination),0,(Length))
#define CLR_MEM_VAL(Destination,Length,X) memset((Destination),(X),(Length))
#define ARRAY_SIZE(X) (sizeof(X)/sizeof(X[0]))
#define SET_BIT(BF, N) (BF |= ((uint64_t)0x0000000000000001 << N))
#define CLR_BIT(BF, N) (BF &= ~((uint64_t)0x0000000000000001 << N))
#define IS_BIT_SET(BF, N) ((BF >> N) & 0x1)


////////////////////////////////
//------------------------------- Preferences
// NOTE(dejakju): 

typedef struct preferences_t {

    /* Preference Name and Id */
    string_t PreferenceName;
    size_t Id;

    /* CLI enable */
    b32_t EnableCLI;

    /* Cursor offset for top lefthand corner, X and Y dimensions */
    int8_t XOffset;
    int8_t YOffset;
    int16_t InitX;
    int16_t InitY;

    /* Positioning Data for the View */
    int8_t ViewXOffset;
    int8_t ViewYOffset;
    int16_t ViewInitX;
    int16_t ViewInitY;

    /* Width, Height */
    int32_t Width;
    int32_t Height;


} preferences_t;

typedef struct entire_file_t
{
    size_t Size;
    void *Contents;
} entire_file_t ;


////////////////////////////////
//------------------------------- Enum Types
// NOTE(dejakju): 

typedef enum AMMX_ReturnCodeTypeDef {
    AMMX_RETURN_OK      = 0x00U,
    AMMX_RETURN_WARN    = 0x05U,
    AMMX_RETURN_ERROR   = 0x0AU,
    AMMX_RETURN_FAIL    = 0x14U
} AMMX_ReturnCodeTypeDef;

typedef enum AMMX_ExecTypeDef {
    AMMX_DEFAULT    = 0x00U,
    AMMX_DOS        = 0x01U,
    AMMX_EXEC       = 0x02U,
    AMMX_LIBRARY    = 0x03U,
    AMMX_LIST       = 0x04U,
    AMMX_NODE       = 0x05U,
    AMMX_SEMAPHORE  = 0x06U,
    AMMX_TASK       = 0x07U,
    AMMX_EVENT      = 0x08U
} AMMX_ExecTypeDef;

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

typedef enum AMMX_StackTypeDef {
    AMMX_STACK_EMPTY    = (uint64_t) 0xffffffffffffffff,
    AMMX_STACK_LENGTH   = (uint64_t) 0x0000000000007fff,
    AMMX_STACK_ISEMPTY  = (uint64_t) 0x000000007fffffff
} AMMX_StackTypeDef;

typedef struct stack_t {
    uint32_t values[AMMX_STACK_LENGTH];
    uint32_t top;
} stack_t;

typedef enum AMMX_MonthTypeDef {
    AMMX_JANUARY,
    AMMX_FEBRUARY,
    AMMX_MARCH,
    AMMX_APRIL,
    AMMX_MAY,
    AMMX_JUNE,
    AMMX_JULY,
    AMMX_AUGUST,
    AMMX_SEPTEMBER,
    AMMX_OCTOBER,
    AMMX_NOVEMBER,
    AMMX_DECEMBER
} AMMX_MonthTypeDef;

typedef enum AMMX_DayOfWeekTypeDef {
    AMMX_SUNDAY,
    AMMX_MONDAY,
    AMMX_TUESDAY,
    AMMX_WEDNESDAY,
    AMMX_THURSDAY,
    AMMX_FRIDAY,
    AMMX_SATURDAY
} AMMX_DayOfWeekTypeDef;


////////////////////////////////
//------------------------------- Function Declarations
// NOTE(dejakju): 

void ammx_version();
b32_t ammx_and(b32_t a, b32_t b);
b32_t ammx_or(b32_t a, b32_t b);
b32_t ammx_not(b32_t a);
b32_t ammx_nand(b32_t a, b32_t b);
b32_t ammx_nor(b32_t a, b32_t b);
b32_t ammx_xor(b32_t a, b32_t b);
b32_t ammx_xnor(b32_t a, b32_t b);
b32_t ammx_imp(b32_t a, b32_t b);
int64_t ammx_abs(int64_t a);
int64_t ammx_max(int64_t a, int64_t b);
int64_t ammx_min(int64_t a, int64_t b);
void ammx_swap(int64_t *a, int64_t *b);
void ammx_fflush();
char* ammx_strrev(char *string);
void ammx_d2c(int64_t number, char *buffer);
int64_t ammx_c2d(char *string);
b32_t ammx_stack_push(stack_t *stack, int32_t value);
int32_t ammx_stack_pop(stack_t *stack);
b32_t ammx_is_leap_year(int32_t year);
char* ammx_string_from_month(AMMX_MonthTypeDef month);
char* ammx_string_from_dayofweek(AMMX_DayOfWeekTypeDef day);
char* ammx_getdate();
char* ammx_gettime();
void ammx_datetime();
entire_file_t ammx_read_entire_file(char* filename);
void ammx_free_entire_file(entire_file_t* file);


#endif //LIBS_TOOLBOX_H
