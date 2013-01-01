/*====================================================================*
 *
 *   int _ffill(FILE *fp);
 *
 *   _stdio.h
 *
 *   fill the buffer assigned to a stream; return NULL on success or EOF
 *   on error; on success, previous buffer contents are lost;
 *
 *   this implementation also returns EOF if no buffer is assigned to the
 *   stream; a buffer may be assigned using setbuf().
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "_stdio.h"

int _ffill (register FILE *fp) 

{
	if ((fp != NULL) && ((fp->_flag & (_IOREAD|_IOERR|_IOEOF)) == _IOREAD) && (fp->_base != NULL)) 
	{
		int count = ((fp->_flag & (_IOUNBUF)) != (0))? (1):(_BUFSIZE);
		if ((fp->_cnt = _read (fp->_file, fp->_base, count)) > 0) 
		{
			fp->_ptr = fp->_base;
			return (0);
		}
		else if (fp->_cnt < 0) fp->_flag |= (_IOERR);
		else fp->_flag |= (_IOEOF);
	}
	return (EOF);
}

