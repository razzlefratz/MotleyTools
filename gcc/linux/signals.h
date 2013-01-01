/*====================================================================*
 *
 *   signals.h - 
 *
 *.  Motley Tools by Charles Maier
 *:  Licensed under GNU General Public License Version 2 Only;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SIGNALS_HEADER
#define SIGNALS_HEADER

/*====================================================================*
 *   custom header files; 
 *--------------------------------------------------------------------*/

#include "../tools/types.h"

/*====================================================================*
 *   constant definitions; 
 *--------------------------------------------------------------------*/

#ifdef __linux__
#define _SIGNALS 31
#else
#define _SIGNALS 34
#endif

/*====================================================================*
 *   variable declarations;
 *--------------------------------------------------------------------*/

typedef signed signal_t;

/*====================================================================*
 *   signal encode/decode functions;
 *--------------------------------------------------------------------*/

signal_t signalspec (char const *string);
signal_t signalcode (char const *signalname);
char const *signalname (signal_t signalcode);

/*====================================================================*
 *   end definitions and declarations;
 *--------------------------------------------------------------------*/

#endif

