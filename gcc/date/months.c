/*====================================================================*
 *
 *   char const *months[];
 *
 *   date.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef MONTHS_SOURCE
#define MONTHS_SOURCE

#include <stddef.h>

#include "../date/months.h"

char const *months [MONTHS_O_NULL+1] = 

{
	"jan",
	"feb",
	"mar",
	"apr",
	"may",
	"jun",
	"jul",
	"aug",
	"sep",
	"oct",
	"nov",
	"dec",
	"january",
	"februrary",
	"march",
	"april",
	"may",
	"june",
	"july",
	"August",
	"september",
	"october",
	"november",
	"december",
	(char const *)(0)
};


#endif

