/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#include <sys/types.h>
#include <string.h>

#include "../tools/types.h"
#include "../tools/memory.h"

size_t gather (void * memory, size_t extent, const struct field * field, unsigned fields) 

{
	byte * offset = (byte *)(memory);
	while ((fields--) && (field->size < extent)) 
	{
		if (!field->type)
		{
			memcopy (offset, field->base, field->size);
		}
		else
		{
			memfold (offset, field->base, field->size);
		}
		offset += field->size;
		extent -= field->size;
		field++;
	}
	return (offset - (byte *)(memory));
}


#if 1
#include <stdio.h>
#include <string.h>
#include "../tools/hexdump.c"
#include "../tools/memcopy.c"
#include "../tools/memfold.c"

int main (int argc, char const * argv []) 

{
	byte buffer [256];
	char string [] = { "Hello World" };
	unsigned number = 0x12345678;
	struct field fields [] = 
	{
		{
			0,
			string,
			sizeof (string)
		},
		{
			0,
			&number,
			sizeof (number)
		},
		{
			1,
			&number,
			sizeof (number)
		}
	};
	memset (buffer, 0, sizeof (buffer));
	gather (buffer, sizeof (buffer), fields, SIZEOF (fields));
	hexdump (buffer, 0, sizeof (buffer), stdout);
	return (0);
}


#endif

