/*====================================================================*
 *
 *   stamp.c - echo system time stamp;
 *
 *   write a fixed length time stamp to stdout; this program can be
 *   used to generate distinct, chronological labels for filenames;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

/*====================================================================*"
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

/*====================================================================*
 *
 *   int main (int argc, char const * argv []);
 *
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv [])

{
	char digits [8];
	unsigned digit = sizeof (digits);
	time_t timer = time ((time_t *) (0));
	while (digit--)
	{
		digits [digit] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" [timer % 36];
		timer /= 36;
	}
	write (STDOUT_FILENO, digits, sizeof (digits));
	return (0);
}

