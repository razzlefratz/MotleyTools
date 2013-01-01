/*====================================================================*
 *
 *   unsigned setumask (char const *string);
 *
 *   linux.h
 *
 *   set umask value using octal string; do not set mask if string
 *   sintax is invalid or illegal; 
 *
 *   the string is not length checked at this time; sigh !
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SETUMASK_SOURCE
#define SETUMASK_SOURCE

#include <sys/stat.h>
#include <sys/types.h>

#include "../linux/linux.h"
#include "../chrlib/chrlib.h"

mode_t setumask (char const *string) 

{
	mode_t mask;

#ifdef LOCAL_SAFEMODE

	if (string == (char *)(0)) 
	{
		return ((mode_t)(0));
	}

#endif

	for (mask = (mode_t)(0); isoctal (*string); mask = (mask << 3) + (*string - '0'));
	if ((*string == (char) (0)) && (mask != (mode_t)(0))) 
	{
		umask (mask);
		return (mask);
	}
	return ((mode_t)(0));
}


#endif

