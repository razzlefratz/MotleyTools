/*====================================================================*
 *
 *   date.h - custom time/date functions and constants,
 *
 *.  published 2003 by charles maier associates limited for internal use;
 *:  modified sun 07 sep 03 by user root on host zeus;
 *;  compiled for debian gnu/linux using gcc compiler;
 *
 *--------------------------------------------------------------------*/

#ifndef DATE_HEADER
#define DATE_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <unistd.h>
#include <time.h>

/*====================================================================*
 *   buffer lengths;
 *--------------------------------------------------------------------*/

#define LOGTIME_MAX 24
#define DAYTIME_MAX 28

/*====================================================================*
 *   datetime string formats; 
 *--------------------------------------------------------------------*/

#define LOGTIME "%F %T %Z"
#define DAYTIME "%T %a %d %b %Y %Z"

/*====================================================================*
 *   vector lengths;
 *--------------------------------------------------------------------*/

#define SV_DATE1  32
#define SV_DATE2  32
#define SV_MONTH  12
#define SV_WKDAY   7

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
 *   define string vector sizes,
 *--------------------------------------------------------------------*/

extern char const *sv_date1[];
extern char const *sv_date2[];
extern char const *sv_month[];
extern char const *sv_wkday[];

/*====================================================================*
 *   define enumerated data types,
 *--------------------------------------------------------------------*/

enum Month

{
   January = 1,
   February = 2,
   March = 3,
   April = 4,
   May = 5,
   June = 6,
   July = 7,
   August = 8,
   September = 9,
   October = 10,
   November = 11,
   December = 12
};

enum Weekday

{
   Sunday = 1,
   Monday = 2,
   Tuesday = 3,
   Wednesday = 4,
   Thursday = 5,
   Friday = 6,
   Saturday = 7
};

/*====================================================================*
 *    
 *--------------------------------------------------------------------*/

#define _midnight(datetime, timezone) ((datetime)-((datetime)%(SECONDS_IN_DAY))+(timezone));
#define _absmonth(month) ((((month)%=(MONTHS_IN_YEAR))>0)?(month):((month)+(MONTHS_IN_YEAR)));
#define _absyear(month, year) (((year)*(MONTHS_IN_YEAR)+(month))/(MONTHS_IN_YEAR))

/*====================================================================*
 *    prototype calendar date functions;
 *--------------------------------------------------------------------*/

unsigned endofmo (unsigned year, signed month);
unsigned dayofwk (unsigned year, signed month, signed date);
unsigned dayofyr (unsigned year, signed month, signed date);
unsigned isleap (unsigned year);

/*====================================================================*
 *   cyclic date functions; 
 *--------------------------------------------------------------------*/

time_t startofperiod (time_t now, time_t due, int period);

time_t midnight(time_t time);
time_t weekdate(time_t time, unsigned weekday);
time_t workdate(time_t time);
time_t mondate(time_t time);
time_t fridate(time_t time);

/*====================================================================*
 *   date difference functions;
 *--------------------------------------------------------------------*/

int annum (struct tm *thisdate, struct tm *thatdate);
int datecomp(struct tm *thisdate, struct tm *thatdate);
int timecomp(struct tm *thistime, struct tm *thattime);

char *encodetime(char buffer[], size_t length, unsigned c, struct tm *tm);
char const *daytime(struct tm * when);
char const *logtime(struct tm * when);

char const *strtm(struct tm *tm);
char const *strtime(time_t *time);

char const *logtm(struct tm *tm);
/* char const *logtime(time_t *time); */

/*====================================================================*
 *    end definitions
 *--------------------------------------------------------------------*/

#endif

