/*====================================================================*
 *   
 *   syslogd_flag_names.c - struct syslogd flag name table; 
 *
 *   syslogd.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SYSLOGD_FLAG_NAMES_SOURCE
#define SYSLOGD_FLAG_NAMES_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../sysklogd/syslogd.h"

/*====================================================================*
 *   struct syslogd flag names by bit position; 
 *--------------------------------------------------------------------*/

char const *syslogd_flag_names [] = 

{
	"disabled",
	"condense",
	"synchronize",
	"ignore_priority",
	"single_priority",
	(char const *) (0)
};


/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#endif

