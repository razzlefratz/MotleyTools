/*====================================================================*
 *
 *   fp = _freopen(char const *pathname, char const *mode, FILE *fp);
 *
 *   _stdio.h
 *
 *   This function opens the specified file and associates it with the
 *   specified file pointer. Any file currently assigned to the pointer
 *   is closed; this function is typically used to to associate one of
 *   the predefined standard I/O streams (ie; stdin, stdout, or stderr)
 *   with a specific file.
 *
 *   The new stream retains the buffering characteristics of the original
 *   file, unless specified otherwise via setbuf().
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "_stdio.h"

FILE *_freopen (char const *pathname, char const *mode, register FILE * fp) 

{
	int fd;
	if ((fp != NULL) && ((fd = _dopen (pathname, mode)) != ERR)) 
	{
		if ((fp->_flag & (_IOREAD | _IOWRITE)) != 0) 
		{
			if ((fp->_flag & (_IOWRITE)) == (_IOWRITE)) 
			{
				_fflush (fp);
			}
			_close (fp->_file);
		}
		return (_fpinit (fd, mode, fp));
	}
	else 
	{
		return (NULL);
	}
}

