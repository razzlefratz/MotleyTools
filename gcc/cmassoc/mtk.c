/*====================================================================*
 *
 *   mti.c - Motley Toolkit Installed;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

#include <stdio.h>

#include "../tools/version.h"

int main (int argc, char const * argv [])

{
	printf ("%s %s is installed!\n", PROJECT, VERSION);
	return (0);
}

