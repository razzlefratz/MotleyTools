/*====================================================================*
 *
 *   char const *sv_month[];
 *
 *   date.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SV_MONTH_SOURCE
#define SV_MONTH_SOURCE

#include <stddef.h>

#include "../date/date.h"

char const *sv_month [MONTHS_IN_YEAR+1] = 

{
	"January",
	"Februrary",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December",
	(char const *)(0)
};


#endif

