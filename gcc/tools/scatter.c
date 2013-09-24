/*====================================================================*
 *
 *   size_t gather (void * memory, size_t extent, struct field const * field, unsigned fields);
 *
 *   memory.h
 *
 *   copy data from a memory region to diverse memory regions; this
 *   function is similar to POSIX function readv() but with it's own
 *   data structure similar to POSIX struct iovec;
 *
 *   struct field has a type member that causes the associated data
 *   to be copied in revers byte order when it has a non-zero value;
 *   this is used fro endian conversion of integers;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

#ifndef SCATTER_SOURCE
#define SCATTER_SOURCE

#include <sys/types.h>
#include <string.h>

#include "../tools/memory.h"

size_t scatter(void const * memory, size_t extent, struct field const * field, unsigned fields)

{
	byte const * source = (byte const *) (memory);
	while ((fields--) && (field->size < extent))
	{
		if (! field->type)
		{
			memcopy (field->base, source, field->size);
		}
		else 
		{
			memfold (field->base, source, field->size);
		}
		source += field->size;
		extent -= field->size;
		field++;
	}
	return (source - (byte *) (memory));
}

#endif



