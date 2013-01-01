/*====================================================================*
 *
 *   FILE *_fopen(char const *pathname, char const *mode);
 *
 *   _stdio.h
 *
 *   open a file and return the address of the assigned filed control
 *   block, as a FILE pointer;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../stdio/_stdio.h"

FILE *_fopen (char const *pathname, char const *mode) 

{
	FILE *fp;
	int fd;
	if ((fd = _dopen (pathname, mode)) != -1) 
	{
		if ((fp = _fdopen (fd, mode)) == NULL) 
		{
			_close (fd);
		}
		return (fp);
	}
	return (NULL);
}

