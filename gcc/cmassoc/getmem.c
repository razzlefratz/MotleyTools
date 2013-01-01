/*====================================================================*
 *
 *   getmem.c - memory data extractor
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#define _GETOPT_H

/*====================================================================*"
 *   system header files;
 *--------------------------------------------------------------------*/

#include <unistd.h>
#include <stdlib.h>
#include <net/ethernet.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/getoptv.h"
#include "../tools/memory.h"
#include "../tools/number.h"
#include "../tools/error.h"
#include "../tools/types.h"
#include "../tools/flags.h"
#include "../files/files.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/uintspec.c"
#include "../tools/basespec.c"
#include "../tools/todigit.c"
#include "../tools/hexout.c"
#include "../tools/error.c"
#endif

/*====================================================================*
 *   constants;
 *--------------------------------------------------------------------*/

#define GETMEM_VERBOSE (1 << 0)
#define GETMEM_SILENCE (1 << 1)
#define GETMEM_NEWLINE (1 << 2)

/*====================================================================*
 *
 *   void getmemory (byte const * memory, size_t extent, char const * object, size_t length);
 *
 *
 *--------------------------------------------------------------------*/

static void getmemory (byte const * memory, size_t extent, char const * object, size_t length) 

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

static void getstring (byte const * memory, size_t extent, char const * object, size_t length) 

{
	char const * string = (char const *)(memory);
	if (length > extent) 
	{
		error (1, ECANCELED, "%s exceeds " SIZE_T_SPEC " bytes", object, length);
	}
	while (isprint (*string) && (length--)) 
	{
		putc (*string++, stdout);
	}
	return;
}


/*====================================================================*
 *
 *   int main (int argc, char const * argv []);
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	static char const * optv [] = 
	{
		"qvn",
		"file offset type [size]\n\n\t  standard-length types are 'byte'|'number'|'long'|'hfid'|'mac'|'key'\n\t  variable-length types are 'data'|'text'",
		"PIB Data Extractor",
		"n\tappend newline",
		"q\tquiet mode",
		"v\tverbose mode",
		(char const *) (0)
	};
	file file;
	size_t offset = 0;
	size_t length = 0;
	size_t extent = 0;
	byte * buffer;
	byte const * memory;
	flag_t flags = (flag_t)(0);
	signed c;
	opterr = 1;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'n':
			_setbits (flags, GETMEM_NEWLINE);
			break;
		case 'q':
			_setbits (flags, GETMEM_SILENCE);
			break;
		case 'v':
			_setbits (flags, GETMEM_VERBOSE);
			break;
		default:
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (!argc) 
	{
		error (1, 0, "No file to read");
	}
	file.name = * argv;
	if ((file.file = open (file.name, O_BINARY|O_RDONLY)) == -1) 
	{
		error (1, errno, "Can't open %s", file.name);
	}
	if ((extent = lseek (file.file, 0, SEEK_END)) == -1) 
	{
		error (1, errno, "Can't size %s", file.name);
	}
	if (!(buffer = malloc (extent))) 
	{
		error (1, errno, "Can't span %s", file.name);
	}
	if (lseek (file.file, 0, SEEK_SET)) 
	{
		error (1, errno, "Can't seek %s", file.name);
	}
	if (read (file.file, buffer, extent) != extent) 
	{
		error (1, errno, "Can't load %s", file.name);
	}
	close (file.file);
	argc--;
	argv++;
	if (!argc) 
	{
		error (1, ECANCELED, "Need an offset");
	}
	length = (uint32_t)(basespec (* argv, 16, sizeof (uint32_t)));
	if (length > extent) 
	{
		error (1, ECANCELED, "PIB offset %zX exceeds PIB extent %zX", offset, length);
	}
	memory = buffer + length;
	argc--;
	argv++;
	if (!argc) 
	{
		_setbits (flags, GETMEM_VERBOSE);
	}
	while (argc && * argv) 
	{
		char const * object = * argv;
		argc--;
		argv++;
		if (!strcmp (object, "byte")) 
		{
			uint8_t * number = (uint8_t *)(memory);
			if (sizeof (* number) > extent) 
			{
				error (1, ECANCELED, "%s exceeds " SIZE_T_SPEC " bytes", object, length);
			}
			printf ("%u", * number);
			memory += sizeof (* number);
			extent -= sizeof (* number);
		}
		else if (!strcmp (object, "word")) 
		{
			uint16_t * number = (uint16_t *)(memory);
			if (sizeof (* number) > extent) 
			{
				error (1, ECANCELED, "%s exceeds " SIZE_T_SPEC " bytes", object, length);
			}
			printf ("%u", LE16TOH (* number));
			memory += sizeof (* number);
			extent -= sizeof (* number);
		}
		else if (!strcmp (object, "long")) 
		{
			uint32_t * number = (uint32_t *)(memory);
			if (sizeof (* number) > extent) 
			{
				error (1, ECANCELED, "%s exceeds " SIZE_T_SPEC " bytes", object, length);
			}
			printf ("%u", LE32TOH (* number));
			memory += sizeof (* number);
			extent -= sizeof (* number);
		}
		else if (!strcmp (object, "xbyte")) 
		{
			uint8_t * number = (uint8_t *)(memory);
			if (sizeof (* number) > extent) 
			{
				error (1, ECANCELED, "%s exceeds " SIZE_T_SPEC " bytes", object, length);
			}
			printf ("0x%02X", * number);
			memory += sizeof (* number);
			extent -= sizeof (* number);
		}
		else if (!strcmp (object, "xword")) 
		{
			uint16_t * number = (uint16_t *)(memory);
			if (sizeof (* number) > extent) 
			{
				error (1, ECANCELED, "%s exceeds " SIZE_T_SPEC " bytes", object, length);
			}
			printf ("0x%04X", LE16TOH (* number));
			memory += sizeof (* number);
			extent -= sizeof (* number);
		}
		else if (!strcmp (object, "xlong")) 
		{
			uint32_t * number = (uint32_t *)(memory);
			if (sizeof (* number) > extent) 
			{
				error (1, ECANCELED, "%s exceeds " SIZE_T_SPEC " bytes", object, length);
			}
			printf ("0x%08X", LE32TOH (* number));
			memory += sizeof (* number);
			extent -= sizeof (* number);
		}
		else if (!strcmp (object, "mac")) 
		{
			length = ETHER_ADDR_LEN;
			if (length > extent) 
			{
				error (1, ECANCELED, "%s exceeds " SIZE_T_SPEC " bytes", object, length);
			}
			getmemory (memory, extent, object, length);
			memory += length;
			extent -= length;
		}
		else if (!strcmp (object, "data")) 
		{
			if (!* argv) 
			{
				error (1, EINVAL, "%s needs a length", object);
			}
			length = (unsigned)(uintspec (* argv, 1, extent));
			hexout (memory, length, 0, 0, stdout);
			memory += length;
			extent -= length;
			argc--;
			argv++;
		}
		else if (!strcmp (object, "text")) 
		{
			if (!* argv) 
			{
				error (1, EINVAL, "%s needs a length", object);
			}
			length = (unsigned)(uintspec (* argv, 1, extent));
			getstring (memory, extent, object, length);
			memory += length;
			extent -= length;
			argc--;
			argv++;
		}
		else if (!strcmp (object, "skip")) 
		{
			if (!* argv) 
			{
				error (1, EINVAL, "%s needs a length", object);
			}
			length = (unsigned)(uintspec (* argv, 1, extent));
			memory += length;
			extent -= length;
			argc--;
			argv++;
			continue;
		}
		else 
		{
			error (1, ENOTSUP, "%s", object);
		}
		if ((argc) && (* argv)) 
		{
			putc (' ', stdout);
		}
	}
	if (_anyset (flags, GETMEM_NEWLINE)) 
	{
		putc ('\n', stdout);
	}
	free (buffer);
	return (0);
}

