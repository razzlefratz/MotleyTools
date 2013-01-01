/*====================================================================*
 *
 *   int _fflush(FILE *fp);
 *
 *   _stdio.h
 *
 *   flush the buffer assigned to a stream; return 0 on success or EOF on
 *   error; return EOF if no buffer is assigned to the stream;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "_stdio.h"

int _fflush (FILE *fp) 

{
	if ((fp != NULL) && ((fp->_flag & (_IOWRITE|_IOERR|_IOEOF)) == _IOWRITE) && (fp->_base != NULL)) 
	{
		int count = fp->_ptr - fp->_base;
		if ((fp->_cnt = _write (fp->_file, fp->_base, count)) == count) 
		{
			fp->_cnt = ((fp->_flag & (_IOUNBUF)) != (0))? (1):(_BUFSIZE);
			fp->_ptr = fp->_base;
			return (0);
		}
		else if (fp->_cnt < 0) fp->_flag |= (_IOERR);
		else fp->_flag |= (_IOEOF);
	}
	return (EOF);
}

