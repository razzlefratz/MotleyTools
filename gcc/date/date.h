/*====================================================================*
 *
 *   date.h - custom time/date functions and constants,
 *
 *.  Motley Tools by Charles Maier
 *:  modified sun 07 sep 03 by user root on host zeus;
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
 *   buffer lengths;
 *--------------------------------------------------------------------*/

#define ARCTIME_LEN 14
#define LOGTIME_LEN 24
#define DAYTIME_LEN 28

/*====================================================================*
 *   datetime string formats; 
 *--------------------------------------------------------------------*/

#define ARCTIME	"%y%m%d-%H%M%S"
#define LOGTIME "%F %T %Z"
#define DAYTIME "%T %a %d %b %Y %Z"
#define NOWTIME " on %a %d %b %Y at %T %Z" 
#define USERWHO " by %s@%s" 

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
 *   
 *--------------------------------------------------------------------*/

#define event() (time((time_t *)(0)))
#define since(timer) (event() - timer)

/*====================================================================*
 *   define string vector sizes,
 *--------------------------------------------------------------------*/

extern char const * sv_date1 [];
extern char const * sv_date2 [];
extern char const * sv_month [];
extern char const * sv_wkday [];

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
time_t midnight (time_t time);
time_t weekdate (time_t time, unsigned weekday);
time_t workdate (time_t time);
time_t mondate (time_t time);
time_t fridate (time_t time);

/*====================================================================*
 *   date difference functions;
 *--------------------------------------------------------------------*/

int annum (struct tm *thisdate, struct tm *);
int datecomp (struct tm *thisdate, struct tm *);
int timecomp (struct tm *thistime, struct tm *);
char * encodetime (char buffer [], size_t length, unsigned c, struct tm *);
char const * daytime (struct tm *);
char const * logtime (struct tm *);
char const * strtm (struct tm *);
char const * strtime (time_t *);
char const * logtm (struct tm *);

/*====================================================================*
 *   time and date specification functions;
 *--------------------------------------------------------------------*/

time_t timespec (char const *string);
time_t waitspec (char const *string);
time_t datespec (char const *string);

/*====================================================================*
 *    end definitions
 *--------------------------------------------------------------------*/

#endif

