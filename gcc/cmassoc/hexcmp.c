/*====================================================================*
 *
 *   hexcmp.c - compare two binary files byte by byte;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

#define _GETOPT_H

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define HEXCMP_EXTRA "++"
#define HEXCMP_SHORT "--"
#define HEXCMP_DELTA "XX"
#define HEXCMP_GROUP (1 << 4)
#define HEXCMP_BLOCK (1 << 8)

#define HEXCMP_SILENCE (1 << 0)
#define HEXCMP_VERBOSE (1 << 1)

/*====================================================================*
 *
 *   int main (int argc, char const * argv []);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv [])

{
	static char const * optv [] =
	{
		"qv",
		"file file",
		"compare two binary files byte by byte",
		"q\tquiet mode",
		"v\tverbose mode",
		(char const *) (0)
	};
	unsigned offset;
	unsigned column;
	signed length1;
	signed length2;
	signed fd1;
	signed fd2;
	uint8_t byte1;
	uint8_t byte2;
	flag_t flags = (flag_t) (0);
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'q':
			_setbits (flags, HEXCMP_SILENCE);
			break;
		case 'v':
			_setbits (flags, HEXCMP_VERBOSE);
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (argc < 2)
	{
		error (1, ENOTSUP, "Need two files to compare");
	}
	if (argc > 2)
	{
		error (1, ENOTSUP, "Too many files to compare");
	}
	if ((fd1 = open (* argv, O_BINARY | O_RDONLY)) == -1)
	{
		error (1, errno, FILE_CANTOPEN, * argv);
	}
	argc--;
	argv++;
	if ((fd2 = open (* argv, O_BINARY | O_RDONLY)) == -1)
	{
		error (1, errno, FILE_CANTOPEN, * argv);
	}
	argc--;
	argv++;
	length1 = read (fd1, & byte1, sizeof (byte1));
	length2 = read (fd2, & byte2, sizeof (byte2));
	for (offset = 0; (length1 > 0) || (length2 > 0); offset++)
	{
		if ((offset % HEXCMP_GROUP) == 0)
		{
			if (offset)
			{
				printf ("\n");
			}
			if (_anyset (flags, HEXCMP_VERBOSE))
			{
				if ((offset % HEXCMP_BLOCK) == 0)
				{
					if (offset)
					{
						printf ("\n");
					}
					printf ("-------- ");
					for (column = 0; column < HEXCMP_GROUP; column++)
					{
						printf (" %02X", column);
					}
					printf ("\n");
					printf ("\n");
				}
			}
			printf ("%08X ", offset);
		}
		if (! length1)
		{
			printf (" %s", HEXCMP_EXTRA);
			length2 = read (fd2, & byte2, sizeof (byte2));
			continue;
		}
		if (! length2)
		{
			printf (" %s", HEXCMP_SHORT);
			length1 = read (fd1, & byte1, sizeof (byte1));
			continue;
		}
		if (byte1 == byte2)
		{
			printf (" %02X", byte1);
		}
		else 
		{
			printf (" %s", HEXCMP_DELTA);
		}
		length1 = read (fd1, & byte1, sizeof (byte1));
		length2 = read (fd2, & byte2, sizeof (byte2));
	}
	printf ("\n");
	exit (0);
}

