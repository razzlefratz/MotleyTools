/*====================================================================*
 *
 *   mode_t modespec (char const *string);
 *
 *   tools.h
 *   
 *   convert string argument to numeric file permission;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef ARGTOMODE_SOURCE
#define ARGTOMODE_SOURCE

#include <sys/types.h>

#include "../tools/tools.h"
#include "../tools/chars.h"
#include "../tools/error.h"

mode_t modespec (char const *string) 

{
	char const *sp = string;
	mode_t mode = 0;
	if (!string) 
	{
		error (1, EINVAL, __func__);
	}
	while (isoctal (*sp)) 
	{
		mode *= 8;
		mode += *sp++ - '0';
	}
	if (*sp) 
	{
		error (1, EINVAL, "[%s]", string);
	}
	if ((mode < 0x0001) || (mode > 0x0FFF)) 
	{
		error (1, EINVAL, "Mode %s exceeds range %04o to %04o", string, 0x0001, 0x0FFFF);
	}
	return (mode);
}


#endif

