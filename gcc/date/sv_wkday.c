/*====================================================================*
 *
 *   char const *sv_wkday[];
 *
 *   date.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SV_WKDAY_SOURCE
#define SV_WKDAY_SOURCE

#include <stddef.h>

#include "../date/date.h"

char const *sv_wkday [DAYS_IN_WEEK+1] = 

{
	"Sunday",
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday",
	(char const *)(0)
};


#endif

