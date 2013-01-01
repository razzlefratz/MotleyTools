/*====================================================================*
 *   
 *   syslogd_type_names.c - struct syslogd type name table;
 *
 *   syslogd.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SYSLOGD_TYPE_NAMES_SOURCE
#define SYSLOGD_TYPE_NAMES_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../sysklogd/syslogd.h"

/*====================================================================*
 *   struct syslogd type names by type code; 
 *--------------------------------------------------------------------*/

char const *syslogd_type_names [] = 

{
	"none",
	"file",
	"pipe",
	"term",
	"console",
	"user",
	"site",
	"host",
	(char const *)(0)
};


/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#endif

