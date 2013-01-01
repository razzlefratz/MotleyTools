/*====================================================================*
 *
 *   ts.c - print system time stamp;
 *
 *   write a fixed length time stamp to stdout; this program can be
 *   used to generate distinct, chronological labels for filenames;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
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
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	char string [14];
	time_t timer = time ((time_t *)(0));
	write (STDOUT_FILENO, string, strftime (string, sizeof (string), "%y%m%d-%H%M%S", localtime (&timer)));
	return (0);
}

