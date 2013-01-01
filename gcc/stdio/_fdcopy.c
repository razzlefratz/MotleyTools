/*====================================================================*
 *
 *   signed _fdcopy(int ifd, int ofd, size_t blocksize);
 *
 *   file.h
 *
 *   copy one file to another using file descriptors; return 0 on success
 *   or -1 on error;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "_stdio.h"
#include "_stdlib.h"

signed _fdcopy (int ifd, int ofd, size_t blocksize) 

{
	char *buffer = (char *)(emalloc (blocksize));
	int count;
	while ((count = read (ifd, buffer, blocksize)) > 0) 
	{
		if (write (ofd, buffer, count) < count) return (-1);
	}
	return (0);
}

