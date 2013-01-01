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
#include "../tools/basic.h"

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
	extern const struct _code_ signalcodes [];
	return (namecode (signalcodes, _SIGNALS, signalname, 0));
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
	extern const struct _code_ signalcodes [];
	size_t index = _SIGNALS;
	while (index > 0) 
	{
		if (signalcodes [--index].code == signalcode) 
		{
			return (signalcodes [index].name);
		}
	}
	return ((char const *)(0));
}


/*====================================================================*
 * 
 *--------------------------------------------------------------------*/

#endif

