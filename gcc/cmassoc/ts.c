/*====================================================================*
 *
 *   ts.c - print system time stamp;
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
#include <string.h>
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

int main(int argc, char const * argv[])

{
	char string[14];
	time_t timer = time((time_t *) (0));
	write (STDOUT_FILENO, string, strftime(string, sizeof(string), "%y%m%d-%H%M%S", localtime(& timer)));
	return (0);
}

