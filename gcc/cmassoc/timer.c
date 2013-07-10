/*====================================================================*
 *
 *   timer.c - echo system time timer;
 *
 *   write a fixed length time string to stdout; this program can be
 *   used to compute the time in seconds between two script events;
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
	time_t timer = time ((time_t * )(0)); 
	while (digit-- ) 
	{ 
		digits [digit] = "0123456789" [timer % 10]; 
		timer /= 10; 
	} 
	write (STDOUT_FILENO, digits, sizeof (digits)); 
	return (0); 
} 

