/*====================================================================*
 *
 *   bool isleap(register unsigned year)
 *
 *   Returns true if year is a leap year; a leap year occurs every four
 *   years excluding centeniums except that every fourth centenium is a
 *   leap year;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef ISLEAP_SOURCE
#define ISLEAP_SOURCE

#include "../date/date.h"
#include "../tools/tools.h"
#include "../tools/types.h"

bool isleap (register unsigned year) 

{
	return ((bool)((year%4 == 0) && ((year%100 != 0) || (year%400 == 0))));
}


#endif

