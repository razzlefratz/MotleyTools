/*====================================================================*
 *
 *   putoptv.h - putoptv related definitions and declarations;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 2005 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef PUTOPTV_HEADER
#define PUTOPTV_HEADER

/*====================================================================*
 *   constant definitions;
 *--------------------------------------------------------------------*/

#define PUTOPTV_S_FILTER "file [file] [...] or [< stdin][> stdout]"
#define PUTOPTV_S_FUNNEL "file [file] [...] [> stdout]"
#define PUTOPTV_S_SEARCH "findspec [findspec] [...] [> stdout]"
#define PUTOPTV_S_DIVINE "[> stdout]"

/*====================================================================*
 *   function declarations;
 *--------------------------------------------------------------------*/

void putoptv (char const * optv []);
void chkoptv (char const * optv []);

/*====================================================================*
 *   end definitions;
 *--------------------------------------------------------------------*/

#endif



