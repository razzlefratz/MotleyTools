/*====================================================================*
 *
 *   size_t dataspec (char const * string, void * memory, size_t extent);
 *
 *   encode a memory region with a variable-length hexadecimal string;
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

#ifndef DATASPEC_SOURCE
#define DATASPEC_SOURCE

#include <ctype.h>
#include <errno.h>

#include "../tools/memory.h"
#include "../tools/number.h"
#include "../tools/error.h"

size_t dataspec (char const * string, void * memory, size_t extent) 

{
	char const * number = string;
	byte * offset = (byte *)(memory);
	if (!number) 
	{
		error (1, EINVAL, __func__);
	}
	while (isspace (*number)) 
	{
		number++;
	}
	while ((*number) && (extent--)) 
	{
		unsigned digit = 0;
		if ((offset != memory) && (*number == HEX_EXTENDER)) 
		{
			number++;
		}
		if ((digit = todigit (*number++)) >= 0x10) 
		{
			error (1, EINVAL, "Have '%s' but need valid hex digit", string);
		}
		*offset = digit << 4;
		if (!*number) 
		{
			error (1, EINVAL, "Have '%s' but need extra hex digit", string);
		}
		if ((digit = todigit (*number++)) >= 0x10) 
		{
			error (1, EINVAL, "Have '%s' but need valid hex data", string);
		}
		*offset |= digit;
		offset++;
	}
	while (isspace (*number)) 
	{
		number++;
	}
	if (*number) 
	{
		error (1, EINVAL, "'%s' exceeds %d bytes", string, (int)((void *)(offset) - memory - extent));
	}
	return ((void *)(offset) - memory);
}


#endif

