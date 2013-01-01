/*====================================================================*
 *
 *   void bytespec (char const *string, void * memory, size_t extent);
 *
 *   memory.h
 *
 *   encode a memory region with a fixed-length hexadecimal string;
 *   return the number of bytes encoded or terminate the program on 
 *   error; 
 *
 *   the number of octets in string must equal the memory extent or
 *   an error will occur; octets may be seperated by semi-colons; 
 *   empty octets are illegal;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef BYTESPEC_SOURCE
#define BYTESPEC_SOURCE

#include <ctype.h>
#include <errno.h>

#include "../tools/memory.h"
#include "../tools/number.h"
#include "../tools/error.h"

size_t bytespec (char const * string, void * memory, size_t extent) 

{
	char const * number = string;
	byte * offset = (byte *)(memory);
	if (!number) 
	{
		error (1, EINVAL, __func__);
	}
	while ((*number) && (extent--)) 
	{
		unsigned digit;
		if (((void *)(offset) > memory) && (*number == HEX_EXTENDER)) 
		{
			number++;
		}
		if ((digit = todigit (*number++)) >= 0x10) 
		{
			error (1, EINVAL, "Have %s but need valid hex digit", string);
		}
		*offset = digit << 4;
		if ((digit = todigit (*number++)) >= 0x10) 
		{
			error (1, EINVAL, "Have %s but need valid hex digit", string);
		}
		*offset |= digit;
		offset++;
	}
	if ((*number) || (extent)) 
	{
		error (1, EINVAL, "%s is not %zd bytes", string, (void *)(offset) - memory + extent);
	}
	return ((void *)(offset) - memory);
}


#endif

