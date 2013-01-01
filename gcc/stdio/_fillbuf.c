/*====================================================================*
 *
 *   int _fillbuf(FILE *fp);
 *
 *   _stdio.h
 *
 *   fill the buffer assigned to a stream; return the first character on
 *   success or EOF on failure; reserve the vacant character position for
 *   one ungetc() call;
 *
 *   unlike filbuf(), this function assigns a buffer to the stream if one
 *   is not assigned; new buffer size is determined by the _IOUNBUF flag
 *   bit;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "_stdio.h"
#include "_stddef.h"

int _fillbuf (register FILE * fp) 

{
	int count;
	if ((fp != NULL) && ((fp->_flag & (_IOREAD | _IOERR | _IOEOF)) == _IOREAD)) 
	{
		if (fp->_base == NULL) 
		{
			_setbuf (fp, ((fp->_flag & (_IOUNBUF)) != 0)? NULL: (char *)(malloc (_BUFSIZE)));
		}
		count = ((fp->_flag & (_IOUNBUF)) != 0)? (1): (_BUFSIZE);
		if ((fp->_cnt = _read (fp->_file, fp->_base, count)) > 0) 
		{
			fp->_ptr = fp->_base;
			fp->_cnt--;
			return ((unsigned)(*fp->_ptr++));
		}
		else if (fp->_cnt < 0) 
		{
			fp->_flag |= (_IOERR);
		}
		else 
		{
			fp->_flag |= (_IOEOF);
		}
	}
	else 
	{
		return (EOF);
	}
}

