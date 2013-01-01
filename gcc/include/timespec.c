/*====================================================================*
 *
 *   time_t timespec (char const *string, char const *notime);
 *
 *   tools.h
 *
 *   convert a string specification to a duration in minutes;
 *
 *   duration may be specified in relative terms "[+]mmm", absolute 
 *   terms "hh:mm" or verbal "none" or "now"; relative specifcation 
 *   may be suffixed with 'h' or 'H' to mean hours or 'm' or 'M' to 
 *   mean minutes; 
 *
 *   return -1 for invalid or illegal time; durations over 24 hours 
 *   are illegal; 
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
#include <errno.h>
#include <time.h>

#include "../tools/tools.h"
#include "../tools/error.h"

time_t timespec (char const *string, char const *notime) 

{
	signed minutes = 0;
	char const *sp;
	if ((string == (char *) (0)) || (*string == (char) (0))) 
	{
		error (1, 0, "time is null or empty");
	}
	if (!strcmp (string, notime)) 
	{
		return (0);
	}
	if (*string == '+') 
	{
		string++;
	}
	for (sp = string; isdigit (*sp); sp++) 
	{
		minutes *= 10;
		minutes += *sp - '0';
	}
	if (*sp == ':') 
	{
		time_t now = time (&now);
		struct tm tm = *localtime (&now);
		int hours = minutes;
		minutes = 0;
		for (sp++; isdigit (*sp); sp++) 
		{
			minutes *= 10;
			minutes += *sp - '0';
		}
		if ((hours > 23) || (minutes > 59)) 
		{
			error (1, 0, "time '%s' is illegal clocktime", string);
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
	if (*sp != (char) (0)) 
	{
		error (1, 0, "time '%s' has invalid syntax", string);
	}
	if (minutes > 1440) 
	{
		error (1, 0, "time '%s' exceeds 24 hours", string);
	}
	return (minutes);
}


#endif

