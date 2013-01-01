/*====================================================================*
 *
 *   void _fcopy(FILE *ifp, FILE *ofp, size_t bufsize);
 *
 *   _stdio.h
 *
 *   This function performs a buffered copy of one file to another. If
 *   the copy was successful 0 is returned; otherwise, ERR is returned.
 *   The two files are referenced by file pointer.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef _FCOPY_SOURCE
#define _FCOPY_SOURCE

#include "_stdio.h"
#include "_stddef.h"

int _fcopy (FILE * ifp, FILE * ofp, size_t blocksize) 

{
	char *buffer = (char *) (emalloc (blocksize));
	int count;
	while ((count = read (_fileno (ifp), buffer, blocksize)) > 0) 
	{
		if (write (_fileno (ofp), buffer, count) < count) return (ERR);
	}
	free (buffer);
	return (0);
}


#endif

