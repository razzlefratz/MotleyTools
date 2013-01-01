/*====================================================================*
 *
 *   date.h - date and time related functions; 
 *
 *   this file version is a subset of a larger one by the same name
 *   that is used in other applications;
 *
 *.  Motley Tools by Charles Maier
 *:  compiled for debian gnu/linux environment using gcc 2.95 compiler;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef DATE_HEADER
#define DATE_HEADER

/*====================================================================*
 *   system header files; 
 *--------------------------------------------------------------------*/

#include <sys/types.h>
#include <time.h>

/*====================================================================*
 *   datetime string formats; 
 *--------------------------------------------------------------------*/

#define LOGTIME_MAX 24
#define DAYTIME_MAX 28

#ifdef NEEDED
#define LOGTIME "%F %T %Z"
#define DAYTIME "%T %a %d %b %Y %Z"
#else
#define LOGTIME "%Y-%m-%d %T %Z"
#define DAYTIME "%H:%M:%S %a %d %b %Y %Z"
#endif

/*====================================================================*
 *   conversion constants; 
 *--------------------------------------------------------------------*/

#define SQUARES_IN_MONTH 42
#define SECONDS_IN_MINUTE 60 
#define SECONDS_IN_HOUR 3600 
#define SECONDS_IN_DAY 86400
#define SECONDS_IN_WEEK 604800 
#define SECONDS_IN_PERIOD 2419200 
#define MINUTES_IN_HOUR 60 
#define MINUTES_IN_DAY 1440 
#define MINUTES_IN_WEEK 10080 
#define HOURS_IN_DAY 24
#define HOURS_IN_WEEK 168
#define HOURS_IN_PERIOD 672
#define DATES_IN_MONTH 31
#define DAYS_IN_WEEK 7
#define DAYS_IN_PERIOD 28
#define DAYS_IN_YEAR 352
#define WEEKS_IN_PERIOD 4
#define WEEKS_IN_MONTH 6
#define WEEKS_IN_YEAR 52
#define PERIODS_IN_YEAR 13
#define MONTHS_IN_YEAR 12
#define MONTHS_IN_QUARTER 3
#define QUARTERS_IN_YEAR 4
#define YEARS_IN_CENTURY 100
#define YEARS_IN_DECADE 10

/*====================================================================*
 *   struct tm comparison functions;
 *--------------------------------------------------------------------*/

int datecomp (struct tm *thisdate, struct tm *thatdate);
int timecomp (struct tm *thisdate, struct tm *thatdate);
char const *daytime (struct tm *tm);
char const *logtime (struct tm *tm);
char const *rawtime (time_t time);
time_t midnight (time_t when);

/*====================================================================*
 *   end definitions and declarations;
 *--------------------------------------------------------------------*/

#endif

