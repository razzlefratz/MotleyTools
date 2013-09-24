/*====================================================================*
 *
 *
 *
 *
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdint.h>
#include <memory.h>
#include <errno.h>
#include <net/ethernet.h>

#include "../tools/types.h"
#include "../tools/sizes.h"
#include "../tools/error.h"

/*====================================================================*
 *
 *   void getmemory (byte const * memory, size_t extent, char const * object, size_t length);
 *
 *
 *--------------------------------------------------------------------*/

static void getmemory(byte const * memory, size_t extent, char const * object, size_t length)

{
	if (length > extent)
	{
		error (1, ECANCELED, "%s exceeds " SIZE_T_SPEC " bytes", object, length);
	}
	hexout (memory, length, ':', 0, stdout);
	return;
}

/*====================================================================*
 *
 *   void getstring (byte const * memory, size_t extent, char const * object, size_t length);
 *
 *
 *--------------------------------------------------------------------*/

static void getstring(byte const * memory, size_t extent, char const * object, size_t length)

{
	char const * string = (char const *) (memory);
	if (length > extent)
	{
		error (1, ECANCELED, "%s exceeds " SIZE_T_SPEC " bytes", object, length);
	}
	while (isprint(* string) && (length--))
	{
		putc (* string++, stdout);
	}
	return;
}

/*====================================================================*
 *
 *   size_t memdecode (const void * memory, size_t extent, char const * object, char const * string) ;
 *
 *
 *--------------------------------------------------------------------*/

size_t memdecode(const void * memory, size_t extent, char const * object, char const * string)

{
	size_t length;
	if (! strcmp(object, "byte"))
	{
		uint8_t number;
		if (sizeof(number) > extent)
		{
			error (1, ECANCELED, "%s exceeds " SIZE_T_SPEC " bytes", object, length);
		}
		memcpy (& number, memory, sizeof(byte));
		printf ("%u", number);
		return (sizeof(number));
	}
	else if(! strcmp(object, "word"))
	{
		uint16_t number;
		if (sizeof(number) > extent)
		{
			error (1, ECANCELED, "%s exceeds " SIZE_T_SPEC " bytes", object, length);
		}
		memcpy (& number, memory, sizeof(number));
		printf ("%u", LE16TOH(number));
		return (sizeof(number));
	}
	else if(! strcmp(object, "long"))
	{
		uint32_t number;
		if (sizeof(number) > extent)
		{
			error (1, ECANCELED, "%s exceeds " SIZE_T_SPEC " bytes", object, length);
		}
		memcpy (& number, memory, sizeof(number));
		printf ("%u", LE32TOH(number));
		return (sizeof(number));
	}
	else if(! strcmp(object, "xbyte"))
	{
		uint8_t number;
		if (sizeof(number) > extent)
		{
			error (1, ECANCELED, "%s exceeds " SIZE_T_SPEC " bytes", object, length);
		}
		memcpy (& number, memory, sizeof(number));
		printf ("0x%02X", number);
		return (sizeof(number));
	}
	else if(! strcmp(object, "xword"))
	{
		uint16_t number;
		if (sizeof(number) > extent)
		{
			error (1, ECANCELED, "%s exceeds " SIZE_T_SPEC " bytes", object, length);
		}
		memcpy (& number, memory, sizeof(number));
		printf ("0x%04X", LE16TOH(number));
		return (sizeof(number));
	}
	else if(! strcmp(object, "xlong"))
	{
		uint32_t number;
		if (sizeof(number) > extent)
		{
			error (1, ECANCELED, "%s exceeds " SIZE_T_SPEC " bytes", object, length);
		}
		memcpy (& number, memory, sizeof(number));
		printf ("0x%08X", LE32TOH(number));
		return (sizeof(number));
	}
	else if(! strcmp(object, "data"))
	{
		char const * size = string;
		if (! size)
		{
			error (1, EINVAL, "%s needs a length", object);
		}
		length = (unsigned) (uintspec(size, 1, extent));
		if (length > extent)
		{
			error (1, ECANCELED, "%s exceeds " SIZE_T_SPEC " bytes", object, length);
		}
		hexout (memory, length, 0, 0, stdout);
		return (length);
	}
	else if(! strcmp(object, "text"))
	{
		char const * size = string;
		if (! size)
		{
			error (1, EINVAL, "%s needs a length", object);
		}
		length = (unsigned) (uintspec(size, 1, extent));
		getstring (memory, extent, object, length);
		return (length);
	}
	else if(! strcmp(object, "skip"))
	{
		char const * size = string;
		if (! size)
		{
			error (1, EINVAL, "%s needs a length", object);
		}
		length = (unsigned) (uintspec(size, 1, extent));
		return (length);
	}
	else if(! strcmp(object, "mac"))
	{
		length = ETHER_ADDR_LEN;
		getmemory (memory, extent, object, length);
		return (length);
	}
	else if(! strcmp(object, "url"))
	{
		length = STRINGSIZE;
		getstring (memory, extent, object, length);
		return (length);
	}
	else 
	{
		error (1, ENOTSUP, "%s", object);
	}
	return (0);
}

