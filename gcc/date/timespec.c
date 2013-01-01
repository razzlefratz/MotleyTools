/*====================================================================*
 *
 *   time_t timespec(char const *string);
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

#ifndef TIMESPEC_SOURCE
#define TIMESPEC_SOURCE

#include <ctype.h>
#include <string.h>
#include <time.h>

#include "../tools/tools.h"
#include "../tools/error.h"

time_t timespec (char const *string) 

{
	signed minutes = 0;
	if ((string) && (*string)) 
	{
		if (strcmp (string, "now")) 
		{
			char const *sp = string;
			if (*sp == '+') 
			{
				sp++;
			}
			while (isdigit (*sp)) 
			{
				minutes *= 10;
				minutes += *sp++ - '0';
			}
			if (*sp == ':') 
			{
				time_t now = time ((time_t *)(0));
				struct tm tm = *localtime (&now);
				int hours = minutes;
				minutes = 0;
				sp++;
				while (isdigit (*sp)) 
				{
					minutes *= 10;
					minutes += *sp++ - '0';
				}
				if ((hours > 23) || (minutes > 59)) 
				{
					error (1, EINVAL, "Time %s is illegal clocktime", string);
				}
				minutes += 60 * hours;
				minutes -= 60 * tm.tm_hour;
				minutes -= tm.tm_min;
				if (minutes < 0) 
				{
					minutes += 1440;
				}
			}
			else if ((*sp == 'h') || (*sp == 'H')) 
			{
				minutes *= 60;
				sp++;
			}
			else if ((*sp == 'm') || (*sp == 'M')) 
			{
				sp++;
			}
			if (*sp) 
			{
				error (1, EINVAL, "[%s]", string);
			}
			if (minutes > 1440) 
			{
				error (1, ERANGE, "Time %s exceeds 24 hours", string);
			}
		}
	}
	return (minutes);
}


#endif

