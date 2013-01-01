/*====================================================================*
 *
 *   FILE *_fpinit(int fd, char const *mode, FILE *fp);
 *
 *   _stdio.h
 *
 *   assign a file descriptor to a free file control block; return the
 *   file control block address on success or NULL on failure;
 *
 *   this function is used by freopen() and fdopen() to initialize all
 *   standard file control blocks; it must not be called if the stream
 *   assigned to the file pointer is still open;
 *
 *   this implementation preserves any buffer currently associated with
 *   the file pointer; it assigns a buffer is none is assigned; the new
 *   buffer size is determined by the _IOUNBUF flag bit;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "_stdio.h"

FILE *_fpinit (int fd, char const *mode, FILE * fp) 

{
	extern char _unbuf [_NFILE];
	if ((fd >= 0) && (mode != NULL) && (fp != NULL)) 
	{
		fp->_file = (char)(fd);
		fp->_flag &= (_IOUNBUF | _IOALLOC);
		fp->_flag |= ((*mode++ == 'r')? _IOREAD: _IOWRITE);
		fp->_flag |= ((*mode++ == '+')? _IOREAD | _IOWRITE: 0);
		fp->_flag |= ((*mode++ == 'b')? 0: _IOTEXT);
		while (fp->_base == NULL) 
		{
			if ((fp->_flag & (_IOUNBUF)) != 0) 
			{
				fp->_ptr = fp->_base = &_unbuf [fp->_file];
				fp->_cnt = ((fp->_flag & (_IOREAD)) != 0)? (0): (1);
				fp->_flag &= ~(_IOALLOC);
			}
			else 
			{
				fp->_ptr = fp->_base = (char *)(malloc (_BUFSIZE));
				fp->_cnt = ((fp->_flag & (_IOREAD)) != 0)? 0: _BUFSIZE;
				fp->_flag |= ((fp->_base)? _IOALLOC: _IOUNBUF);
			}
		}
		return (fp);
	}
	else 
	{
		return (NULL);
	}
}

