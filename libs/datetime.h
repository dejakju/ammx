/*
 *  $VER:       datetime.h 1.0
 *  $DATE:      2025-11-17 (2025-11-17)
 *  $AUTHOR:    Goran (dejakju@gmail.com)
*/

#ifndef LIBS_DATETIME_H
#define LIBS_DATETIME_H


////////////////////////////////
//------------------------------- Dependencies
// NOTE(dejakju): 

#include <stdbool.h>
#include <stdint.h>
#include <time.h>


////////////////////////////////
//------------------------------- Enum Types
// NOTE(dejakju): 

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
    AMMX_DECEMBER,
    AMMX_MONTH_COUNT
} AMMX_MonthTypeDef;

typedef enum AMMX_DayOfWeekTypeDef {
    AMMX_SUNDAY,
    AMMX_MONDAY,
    AMMX_TUESDAY,
    AMMX_WEDNESDAY,
    AMMX_THURSDAY,
    AMMX_FRIDAY,
    AMMX_SATURDAY,
    AMMX_DAYOFWEEK_COUNT
} AMMX_DayOfWeekTypeDef;

////////////////////////////////
//------------------------------- Function Declarations
// NOTE(dejakju): 

bool ammx_is_leap_year(int32_t year);
char* ammx_string_from_month(AMMX_MonthTypeDef month);
char* ammx_string_from_dayofweek(AMMX_DayOfWeekTypeDef day);
bool ammx_get_datestamp(int32_t* day, AMMX_MonthTypeDef* month, int32_t* year);
bool ammx_get_timestamp(int32_t* hours, int32_t* minutes, int32_t* seconds);
char* ammx_getdate_static();
char* ammx_gettime_static();
int ammx_getdate(char* buffer, size_t buffer_size);
int ammx_gettime(char* buffer, size_t buffer_size);

#endif
