/*====================================================================*
 *
 *   size_t gather (void * memory, size_t extent, struct field const * field, unsigned fields);
 *
 *   memory.h
 *
 *   fill a memory region with data from diverse memory regions; this
 *   function is similar to POSIX function writev() but with it's own
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

#ifndef GATHER_SOURCE
#define GATHER_SOURCE

#include <sys/types.h>
#include <string.h>

#include "../tools/memory.h"

size_t gather(void * memory, size_t extent, struct field const * field, unsigned fields)

{
	byte * target = (byte *) (memory);
	while ((fields--) && (field->size < extent))
	{
		if (! field->type)
		{
			memcopy (target, field->base, field->size);
		}
		else 
		{
			memfold (target, field->base, field->size);
		}
		target += field->size;
		extent -= field->size;
		field++;
	}
	return (target - (byte *) (memory));
}

/*====================================================================*
 *   test/demo program;
 *--------------------------------------------------------------------*/

#if 0

#include <stdio.h>
#include <string.h>

#include "../tools/hexdump.c"
#include "../tools/memcopy.c"
#include "../tools/memfold.c"

int main(int argc, char const * argv[])

{
	byte buffer[256];
	char string[] = 
	{
		"Hello World"
	};
	unsigned number = 0x12345678;
	struct field fields[] = 
	{
		{
			0,
			string,
			sizeof (string)
		},
		{
			0,
			& number,
			sizeof (number)
		},
		{
			1,
			& number,
			sizeof (number)
		}
	};
	memset (buffer, 0, sizeof(buffer));
	gather (buffer, sizeof(buffer), fields, SIZEOF(fields));
	hexdump (buffer, 0, sizeof(buffer), stdout);
	return (0);
}

#endif

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#endif



