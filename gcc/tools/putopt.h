/*====================================================================*
 *
 *   putopt.h - putopt related definitions and declarations;
 *
 *.  Motley Tools by Charles Maier
 *:  compiled for debian gnu/linux environment using gcc 2.95 compiler;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef PUTOPT_HEADER
#define PUTOPT_HEADER

/*====================================================================*
 *   constant definitions;
 *--------------------------------------------------------------------*/

#define PUTOPT_I_OPTIONS 0
#define PUTOPT_I_COMMAND 1
#define PUTOPT_I_PURPOSE 2
#define PUTOPT_I_DETAILS 3

#define PUTOPT_S_FILTER "file [file] [...] or [< stdin][> stdout]"
#define PUTOPT_S_FUNNEL "file [file] [...] [> stdout]"
#define PUTOPT_S_SEARCH "findspec [findspec] [...] [> stdout]"
#define PUTOPT_S_DIVINE "[> stdout]"

/*====================================================================*
 *   function declarations;
 *--------------------------------------------------------------------*/

void putopt (char const *help []);

/*====================================================================*
 *   end definitions;
 *--------------------------------------------------------------------*/

#endif

