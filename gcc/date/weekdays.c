/*====================================================================*
 *   
 *   weekdays.c - weekday name table;               
 *
 *   weekdays.h
 *
 *   long and short weekday names appear in numerical order; search
 *   the table for a match then compute the modulo 7 of that index; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef WEEKDAYS_SOURCE
#define WEEKDAYS_SOURCE

#include "../date/weekdays.h"

char const *weekdays [WEEKDAYS_O_NULL+1] = 

{
	"sun",
	"mon",
	"tue",
	"wed",
	"thu",
	"fri",
	"sat",
	"sunday",
	"monday",
	"tuesday",
	"wednesday",
	"thursday",
	"friday",
	"saturday",
	(char const *)(0)
};


#endif

