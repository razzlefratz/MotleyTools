/*====================================================================*
 *
 *   void  passwords (unsigned seed, unsigned start, unsigned count, unsigned limit, unsigned block, char space);
 *
 *   crypt.h
 *
 *   print a range of device passwords on stdout; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef PASSWORDS_SOURCE
#define PASSWORDS_SOURCE

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <netinet/in.h>

#include "../calc/calc.h"
#include "../crypt/crypt.h"

static void password (unsigned seed, char const charset [], unsigned characters, unsigned limit, unsigned block, char space) 

{ 
	unsigned count = 0; 
	_srand (seed); 
	while (count < limit) 
	{ 
		unsigned character = _rand (); 
		if ((count) && (block) && ! (count % block)) 
		{ 
			putc (space, stdout); 
		} 
		putc (charset [character % characters], stdout); 
		count++; 
	} 
	return; 
} 

void passwords (unsigned seed, unsigned start, unsigned count, unsigned limit, unsigned block, char space) 

{ 
	char charset [UCHAR_MAX + 1]; 
	unsigned offset = 0;
	_srand (seed); 
	while (offset < sizeof (charset)) 
	{ 
		unsigned c = _rand () & SCHAR_MAX;
		if (isupper (c)) 
		{ 
			charset [offset++] = c; 
		} 
	} 
	while (count--) 
	{ 
		password (start, charset, sizeof (charset), limit, block, space); 
		putc ('\n', stdout); 
		start++; 
	} 
	return; 
} 

#endif



