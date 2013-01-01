/*====================================================================*
 *
 *   int _memcmp(void const *target, void const *source, size_t count)
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

int _memcmp (register char const *target, register char const *source, register size_t count) 

{
	if (source) if (target) 
	{
		while ((count > 0) && (*target == *source)) target++,
		source++,
		count--;
	}
	return ((count > 0)? (int)(*target - *source):(0));
}

