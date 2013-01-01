/*====================================================================*
 *
 *   FILE *_bufopen(char const *pathname, char const *mode);
 *   int _bufclose(FILE *fp);
 *
 *   _stdio.h
 *
 *   open a named file in the specified mode; return a valid file pointer
 *   on success or NULL on failure;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "_stdio.h"

#ifdef _POSIX

FILE *_bufopen (char *buffer, size_t size, char const *mode) 

{
	FILE *fp;
	fp = (FILE *)(emalloc (sizeof (FILE)));
	fp->_cnt = size;
	fp->_ptr = buffer;
	fp->_base = buffer;
	fp->_flag &= (_IOUNBUF|_IOALLOC);
	fp->_flag |= ((*mode++ == 'r')? _IOREAD:_IOWRITE);
	fp->_flag |= ((*mode++ == '+')? _IOREAD|_IOWRITE:0);
	fp->_flag |= ((*mode++ == 'b')? 0:_IOTEXT);
	fp->_file = 0xFF;
	return (fp);
}

int _bufclose (FILE *fp) 

{
	free (fp);
	return (-1);
}


#else

FILE *_bufopen (char *buffer, size_t size, char const *mode) 

{
	FILE *fp;
	fp = (FILE *)(emalloc (sizeof (FILE)));
	fp->_cnt = size;
	fp->_ptr = buffer;
	fp->_base = buffer;
	fp->_flag &= (_IOUNBUF|_IOALLOC);
	fp->_flag |= ((*mode++ == 'r')? _IOREAD:_IOWRITE);
	fp->_flag |= ((*mode++ == '+')? _IOREAD|_IOWRITE:0);
	fp->_flag |= ((*mode++ == 'b')? 0:_IOTEXT);
	fp->_file = 0xFF;
	return (fp);
}

int _bufclose (FILE *fp) 

{
	free (fp);
	return (-1);
}


#endif

