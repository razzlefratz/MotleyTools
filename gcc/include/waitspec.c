/*====================================================================*
 *
 *   time_t waitspec (char const *string);
 *
 *   tools.h
 *
 *   convert a string to a time interval;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef WAITSPEC_SOURCE
#define WAITSPEC_SOURCE

#include <ctype.h>
#include <errno.h>
#include <time.h>

#include "../tools/tools.h"
#include "../tools/error.h"

static unsigned multiple [] = 

{
	3600,
	1800,
	1200,
	900,
	720,
	600,
	360,
	300,
	240,
	180,
	120,
	0
};

time_t waitspec (char const *string) 

{
	time_t seconds = 0;
	size_t index;
	if ((string != (char *) (0)) && (*string != (char) (0))) 
	{
		char const *sp;
		for (sp = string; isdigit (*sp); ++sp) 
		{
			seconds *= 10;
			seconds += *sp - '0';
		}
		switch (*sp) 
		{
		case 'd':
		case 'D':
			seconds *= 24;
		case 'h':
		case 'H':
			seconds *= 60;
		case 'm':
		case 'M':
			seconds *= 60;
		case 's':
		case 'S':
			sp++;
			break;
		}
		if (*sp != (char)(0)) 
		{
			error (1, EINVAL, "%s", string);
		}
		for (index = 0; (multiple [index] != 0) && (seconds % multiple [index] != 0); index++);
		if (multiple [index] == 0) 
		{
			error (1, EINVAL, "time must be a multiple of 60, 30, 20, 15, 12, 10, 6, 5, 4, 3 or 2 minutes");
		}
	}
	return (seconds);
}


#endif

