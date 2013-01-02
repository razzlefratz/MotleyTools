/*====================================================================*
 *
 *   envp.c - display environment vector;
 *
 *   this program is a simple debugging tool that displays the environment
 *   vector envp[] on stdout for inspection.
 *
 *   use it to see how your host system presents environment variables;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <time.h>

#include "../tools/tools.h"
#include "../tools/number.h"
#include "../date/date.h"

#ifndef MAKEFILE
#include "../tools/uintspec.c"
#include "../tools/todigit.c"
#include "../tools/error.c"
#include "../tools/serial.c"
#endif

#ifndef MAKEFILE
#include "../date/startofperiod.c"
#include "../date/encodetime.c"
#include "../date/datecomp.c"
#include "../date/daytime.c"
#include "../date/strtime.c"
#include "../date/strtm.c"
#endif

char const *program_name = "date";

/*====================================================================*
 *
 *   time_t startofperiod (time_t anydate, time_t refdate, unsigned period);
 *
 *   period is a duration in days, such as a week or a fortnight, that 
 *   starts on some reference date; given anydate and a reference date
 *   return the first date of the period in which anydate falls; 
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STARTOFPERIOD_SOURCE
#define STARTOFPERIOD_SOURCE

#include <time.h>

#include "../date/date.h"

time_t startofperiod (time_t anydate, time_t refdate, unsigned period) 

{
	return (anydate + (refdate - anydate) % (period * 86400) - (period *86400));
}


#endif

void showdate (char const *title, time_t anytime) 

{
	char buffer [100];
	encodetime (buffer, sizeof (buffer), (char)(0), localtime (&anytime));
	printf ("%s %s  ", title, buffer);
	return;
}

int main (int argc, char const *argv [], char const *envp []) 

{
	extern long timezone;
	struct tm date1;
	struct tm date2;
	int period;
	time_t anydate;
	time_t refdate;
	memset (&date1, 0, sizeof (struct tm));
	memset (&date2, 0, sizeof (struct tm));
	if (argc > 6) 
	{
		date1.tm_year = uintspec (*++argv, 1950, 2050) - 1900;
		date1.tm_mon = uintspec (*++argv, 1, 50) - 1;
		date1.tm_mday = uintspec (*++argv, 1, 50);
		refdate = mktime (&date1);
		date2.tm_year = uintspec (*++argv, 1950, 2050) - 1900;
		date2.tm_mon = uintspec (*++argv, 1, 50) - 1;
		date2.tm_mday = uintspec (*++argv, 1, 50);
		anydate = mktime (&date2);
		for (period = -15; period < 15; period++) 
		{
			showdate ("refdate", refdate);
			showdate ("anydate", refdate + period * 86400);
			showdate (" < ", startofperiod (refdate + period * 86400, refdate, -7));
			showdate (" > ", startofperiod (refdate + period * 86400, refdate, 7));
			printf ("\n");
		}
	}
	exit (0);
}

