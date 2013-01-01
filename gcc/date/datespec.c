/*====================================================================*
 *
 *   static int datespec(char const *string);
 *
 *   tools.h
 *
 *   convert the shutdown time to minutes; allow either relative time
 *   as "[+]mmm" or absolute time as "hh:mm" or "now"; durations more
 *   the 24 hours are illegal; return -1 for invalid or illegal time;
 *
 *   additionally, the relative specifcation can be suffixed with 'h'
 *   or 'H' to indicate hours or with 'm' or 'M' to indicate minutes; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef DATESPEC_SOURCE
#define DATESPEC_SOURCE

#include <time.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "../tools/tools.h"
#include "../tools/error.h"

time_t datespec (char const *string) 

{
	time_t now = time (&now);
	struct tm *tm = localtime (&now);
	if (string == (char *) (0)) 
	{
		error (1, EINVAL, "date argument is null");
	}
	if (strcmp (string, "now")) 
	{
		char const *sp = string;
		tm->tm_year = 0;
		while (isdigit (*sp)) 
		{
			tm->tm_year *= 10;
			tm->tm_year += *sp++ - '0';
		}
		if ((tm->tm_year < 1900) || (tm->tm_year > 2099)) 
		{
			error (1, ERANGE, "Year %s exceeds range 1900 to 2099", string);
		}
		tm->tm_year -= 1900;
		if (*sp == '-') 
		{
			tm->tm_mon = 0;
			for (sp++; isdigit (*sp); sp++) 
			{
				tm->tm_mon *= 10;
				tm->tm_mon += *sp - '0';
			}
			if ((tm->tm_mon < 1) || (tm->tm_mon > 12)) 
			{
				error (1, ERANGE, "Month %s exceeds range 1 to 12", string);
			}
			tm->tm_mon--;
			if (*sp == '-') 
			{
				tm->tm_mday = 0;
				for (sp++; isdigit (*sp); sp++) 
				{
					tm->tm_mday *= 10;
					tm->tm_mday += *sp - '0';
				}
				if ((tm->tm_mday < 1) || (tm->tm_mday > 31)) 
				{
					error (1, ERANGE, "Day %s exceeds range 1 to 31", string);
				}
			}
		}
		if (*sp) 
		{
			error (1, EINVAL, "[%s]", string);
		}
	}
	return (mktime (tm));
}


#endif

