/*====================================================================*
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef _STRERROR_SOURCE
#define _STRERROR_SOURCE

#include "../stdio/_stdio.h"
#include "../tools/types.h"

char const * strerror (error_t errnum) 

{
	if ((errnum < 0) || (errnum > 100)) 
	{
		return ("unknown error");
	}
	return (sys_errlist [errnum]);
}


#endif

