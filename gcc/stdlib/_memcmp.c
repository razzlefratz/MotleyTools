/*====================================================================*
 *
 *   signed _memcmp (const void * target, const void * source, unsigned long count);
 *
 *   _string.h
 *   _memory.h
 *
 *   This function compares the first (cnt) character positions of
 *   two buffers and returns 0 if they are identical; otherwise, a
 *   -1 is returned if the first buffer precedes the second and a
 *   +1 is returned if the first buffer follows the second. Buffer
 *   length is specified in bytes.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../stdlib/_memory.h"

signed _memcmp (register const void * target, register const void * source, register unsigned long count)

{
	if (source) if (target)
	{
		while ((count) && (* (char *) (target) == * (char *) (source))) 
		{
			target++;
			source++;
			count--;
		}
	}
	return ((count)? (signed) (* (char *) (target) - * (char *) (source)): (0));
}
