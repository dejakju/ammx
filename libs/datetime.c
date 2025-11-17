/*
 *  $VER:       datetime.c 1.0
 *  $DATE:      2025-11-17 (2025-11-17)
 *  $AUTHOR:    Goran (dejakju@gmail.com)
*/

////////////////////////////////
//------------------------------- Dependencies
// NOTE(dejakju): 

#include "datetime.h"


////////////////////////////////
//------------------------------- Implementations
// NOTE(dejakju): 

/**
 * Check a year for a leap year
 *
 * @param year int32_t: the year to be checked for a leap year.
 * @return bool: true if year is a leap year, otherwise false.
 */
bool
ammx_is_leap_year(int32_t year)
{
    if (year % 4 != 0) return false;
    else if (year % 100 != 0) return true;
    else if (year % 400 != 0) return false;
    else return true;
}

/**
 * Returns a string representation for the name of the month.
 * The string mapping is defined as a static array.
 *
 * @param day A valid AMMX_MonthTypeDef enum.
 * @return char*: A string representation of the name of the month for the AMMX_MonthTypeDef enum.
 */
char*
ammx_string_from_month(AMMX_MonthTypeDef month)
{
    // 1. Define the static array for string mapping.
    // The index of the array must match the enum value.
    static const char *const MONTH_NAMES[] = {
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"
    };

    // 2. Perform bounds checking and return the string.
    // If the 'day' is out of bounds, return the error string "(null)".
    if (month >= 0 && month < AMMX_MONTH_COUNT) {
        return (char*)MONTH_NAMES[month];
    } else {
        return "(null)";
    }
}

/**
 * Returns a string representation for the name of the day.
 * The string mapping is defined as a static array.
 *
 * @param day A valid AMMX_DayOfWeekTypeDef enum.
 * @return A string representation of the name of the day for the AMMX_DayOfWeekTypeDef enum.
 */
char*
ammx_string_from_dayofweek(AMMX_DayOfWeekTypeDef day)
{
    // 1. Define the static array for string mapping.
    // The index of the array must match the enum value.
    static const char *const DAY_NAMES[] = {
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday"
    };

    // 2. Perform bounds checking and return the string.
    // If the 'day' is out of bounds, return the error string "(null)".
    if (day >= 0 && day < AMMX_DAYOFWEEK_COUNT) {
        return (char*)DAY_NAMES[day];
    } else {
        return "(null)";
    }
}

/**
 * Retrieves the current day, month, and year separately.
 *
 * @param day Pointer to an integer where the day of month (1–31) will be stored.
 * @param month Pointer to an AMMX_MonthTypeDef where the month will be stored.
 * @param year Pointer to an integer where the year (e.g., 2025) will be stored.
 * @return true if successful, false on error.
 */
bool
ammx_get_datestamp(int32_t* day, AMMX_MonthTypeDef* month, int32_t* year)
{
    if (day == NULL || month == NULL || year == NULL) {
        return false;
    }

    // Get current time
    time_t now = time(NULL);
    struct tm* datetime = localtime(&now);
    if (datetime == NULL) {
        return false;
    }

    // Extract values
    *day   = datetime->tm_mday;              // Day of month (1–31)
    *month = (AMMX_MonthTypeDef)datetime->tm_mon; // Month (0–11 mapped to enum)
    *year  = datetime->tm_year + 1900;       // Years since 1900 → full year

    return true;
}

/**
 * Retrieves the current time as hours, minutes, and seconds separately.
 *
 * @param hours Pointer to an integer where the hour (0–23) will be stored.
 * @param minutes Pointer to an integer where the minute (0–59) will be stored.
 * @param seconds Pointer to an integer where the second (0–59) will be stored.
 * @return true if successful, false on error.
 */
bool
ammx_get_timestamp(int32_t* hours, int32_t* minutes, int32_t* seconds)
{
    if (hours == NULL || minutes == NULL || seconds == NULL) {
        return false;
    }

    // Get current time
    time_t now = time(NULL);
    struct tm* datetime = localtime(&now);
    if (datetime == NULL) {
        return false;
    }

    // Extract values
    *hours   = datetime->tm_hour;   // 0–23
    *minutes = datetime->tm_min;    // 0–59
    *seconds = datetime->tm_sec;    // 0–59

    return true;
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
