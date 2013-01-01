/*====================================================================*
 *
 *   flag_t cheader (char const *title, char const *class, flag_t flags);
 *
 *   clang.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CHEADER_SOURCE
#define CHEADER_SOURCE

#include <stdio.h>

#include "../clang/clang.h"
#include "../tools/types.h"
#include "../tools/flags.h"

flag_t cheader (char const *title, char const *class, flag_t flags) 

{

#ifdef CMASSOC_SAFEMODE

	if (!title) 
	{
		return (flags);
	}
	if (!class) 
	{
		return (flags);
	}

#endif

	if (_anyset (flags, CFLAG_HEADER)) 
	{
		_clrbits (flags, CFLAG_HEADER);
		_setbits (flags, CFLAG_FOOTER);
		printf ("#ifndef %s_%s\n", title, class);
		printf ("#define %s_%s\n", title, class);
		printf ("\n");
	}
	return (flags);
}


#endif

