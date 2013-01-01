/*====================================================================*
 * 
 *   signals.c - signal name/code translation functions;
 *
 *   signals.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SIGNALS_SOURCE
#define SIGNALS_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <signal.h>
#include <ctype.h>
#include <string.h>
#include <error.h>
#include <errno.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../linux/signals.h"

/*====================================================================*
 *
 *   signed signalcode (char const *signalname);
 *
 *   return the signal code associated with a POSIX signal name
 *   or 0 if the signal name is illegal or invalid; 
 *    
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signal_t signalcode (char const *signalname) 

{
	extern const struct _code_ signal_codes [];
	size_t lower = 0;
	size_t upper = _SIGNALS;
	if (signalname == (char *) (0)) 
	{
		return ((signal_t)(0));
	}
	if (*signalname == (char) (0)) 
	{
		return ((signal_t)(0));
	}
	while (lower < upper) 
	{
		size_t index = (lower + upper) >> 1;
		signed order = strcmp (signalname, signal_codes [index].name);
		if (order < 0) 
		{
			upper = index - 0;
		}
		else if (order > 0) 
		{
			lower = index + 1;
		}
		else 
		{
			return ((signal_t)(signal_codes [index].code));
		}
	}
	return ((signal_t)(0));
}


/*====================================================================*
 *
 *   char const *signalname(signal_t signalcode);
 *
 *   return the POSIX signal name associated with a signal code 
 *   or (char *)(0) if the signal code is out of range; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const *signalname (signal_t signalcode) 

{
	extern const struct _code_ signal_codes [];
	size_t index = _SIGNALS;
	while (index > 0) 
	{
		if (signal_codes [--index].code == signalcode) 
		{
			return (signal_codes [index].name);
		}
	}
	return ((char const *)(0));
}


/*====================================================================*
 * 
 *--------------------------------------------------------------------*/

#endif

