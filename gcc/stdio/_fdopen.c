/*====================================================================*
 *
 *   FILE *_fdopen(int fd, char const *mode);
 *
 *   _stdio.h
 *
 *   assign the specified file descriptor to a free file control block;
 *   return the file control block address as a FILE pointer;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "_stdio.h"

FILE *_fdopen (register int fd, char const *mode) 

{
	extern FILE _iob [];
	register FILE *fp;
	register int file;
	for (file = 0; file < _NFILE; file++) 
	{
		fp = &_iob [file];
		if ((fp->_flag & (_IOREAD|_IOWRITE)) == 0) 
		{
			return (_fpinit (fd, mode, fp));
		}
	}
	return (NULL);
}

