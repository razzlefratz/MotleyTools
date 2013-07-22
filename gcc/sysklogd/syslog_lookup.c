/*====================================================================*
 *
 *   int syslog_lookup (char const *string, struct _code_ table[]);
 *
 *   syslog.h
 *
 *   convert string to a code defined in table; return the code on
 *   success or -1 on failure;
 *
 *   struct _code_ table contains string and integer pairs; the last
 *   entry contains a null and -1; attempt to
 *   match either the string or the integer or both;
 *
 *   if string is numeric then convert it to an integer; otherwise 
 *   use -1 as the default value; search table until NULL; attempt 
 *   to match string, first, then value;
 *
 *   if string is, in fact numeric, then the value must appear in 
 *   the table to be valid; if not then the string must appear in
 *   the table;  
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SYSLOG_LOOKUP_SOURCE
#define SYSLOG_LOOKUP_SOURCE

#include <ctype.h>
#include <string.h>

#include "../linux/syslog.h"
#include "../tools/types.h"

int syslog_lookup (char const * string, const struct _code_ table []) 

{ 
	code_t code = 0; 
	char const * sp; 
	for (sp = string; isdigit (* sp); ++ sp) 
	{ 
		code *= 10; 
		code += (int) (* sp - '0'); 
	} 
	if (* sp != (char) (0)) 
	{ 
		code = - 1; 
	} 
	while (table->name != (char const *) (0)) 
	{ 
		if (strcmp (string, table->name) == 0) 
		{ 
			break; 
		} 
		if (code == table->code) 
		{ 
			break; 
		} 
		table++; 
	} 
	return (table->code); 
} 

#endif



