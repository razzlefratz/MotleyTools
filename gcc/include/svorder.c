/*====================================================================*
 *
 *   void svorder (char const *name, char const * list[], size_t size);
 *
 *   check a string vector for correct length and string order; exit 
 *   the program if either is incorrect; 
 *
 *   this is defensive programming because binary searches fail when
 *   the string vector is out of order and cause segment faults when
 *   the string vector is too short; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

#ifndef SVORDER_SOURCE
#define SVORDER_SOURCE

#include <string.h>
#include <errno.h>

#include "../strlib/strlib.h"
#include "../tools/error.h"

void svorder (char const *title, char const *table [], size_t count, int (*comp)(char const *, char const *)) 

{
	size_t index;

#ifdef STRLIB_SAFEMODE

	if (title == (char const *) (0)) 
	{
		return (count);
	}
	if (table == (char const **) (0)) 
	{
		return (count);
	}
	if (comp == (void *) (0)) 
	{
		return (count);
	}

#endif

	for (index = 0; table [index] != (char const *) (0); index++);
	if (index != count) 
	{
		error (1, 0, "table %s[] has %d (not %d) items", title, index, count);
	}
	for (index = 0; index < count; index++) 
	{
		if ((index > 0) && (comp (table [index - 1], table [index]) >= 0)) 
		{
			error (1, 0, "table %s[%d]='%s' is out of order", title, index, table [index]);
		}
	}
	return;
}


#endif

