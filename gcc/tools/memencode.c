/*====================================================================*
 * 
 *   size_t memencode (void * memory, size_t extent, char const * type, char const * data);
 *
 *   memory.h
 *
 *   encode a memory region based on type data strings;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef MEMENCODE_SOURCE
#define MEMENCODE_SOURCE

#include <stdint.h>
#include <memory.h>
#include <errno.h>

#include "../tools/memory.h"
#include "../tools/number.h"
#include "../tools/error.h"

size_t memencode(void * memory, size_t extent, char const * type, char const * data)

{
	if (! strcmp(type, "byte"))
	{
		uint8_t * number = (typeof(number)) (memory);
		if (extent < sizeof(* number))
		{
			error (1, ECANCELED, "Overflow at %s %s", type, data);
		}
		* number = (typeof(* number)) (basespec(data, 0, sizeof(* number)));
		return (sizeof(* number));
	}
	if (! strcmp(type, "word"))
	{
		uint16_t * number = (typeof(number)) (memory);
		if (extent < sizeof(* number))
		{
			error (1, ECANCELED, "Overflow at %s %s", type, data);
		}
		* number = (typeof(* number)) (basespec(data, 0, sizeof(* number)));
		return (sizeof(* number));
	}
	if (! strcmp(type, "long"))
	{
		uint32_t * number = (typeof(number)) (memory);
		if (extent < sizeof(* number))
		{
			error (1, ECANCELED, "Overflow at %s %s", type, data);
		}
		* number = (typeof(* number)) (basespec(data, 0, sizeof(* number)));
		return (sizeof(* number));
	}
	if (! strcmp(type, "huge"))
	{
		uint64_t * number = (typeof(number)) (memory);
		if (extent < sizeof(* number))
		{
			error (1, ECANCELED, "Overflow at %s %s", type, data);
		}
		* number = (typeof(* number)) (basespec(data, 0, sizeof(* number)));
		return (sizeof(* number));
	}
	if (! strcmp(type, "text"))
	{
		extent = strlen(data);
		memcpy (memory, data, extent);
		return (extent);
	}
	if (! strcmp(type, "data"))
	{
		extent = (unsigned) (dataspec(data, memory, extent));
		return (extent);
	}
	if (! strcmp(type, "zero"))
	{
		extent = (typeof(extent)) (uintspec(data, 0, extent));
		memset (memory, 0x00, extent);
		return (extent);
	}
	if (! strcmp(type, "fill"))
	{
		extent = (typeof(extent)) (uintspec(data, 0, extent));
		memset (memory, 0xff, extent);
		return (extent);
	}
	if (! strcmp(type, "skip"))
	{
		extent = (typeof(extent)) (uintspec(data, 0, extent));
		return (extent);
	}
	error (1, ENOTSUP, "%s", type);
	return (0);
}

#endif



