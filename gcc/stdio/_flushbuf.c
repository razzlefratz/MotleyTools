/*====================================================================*
 *
 *   int _flushbuf(int c, FILE *fp);
 *
 *   _stdio.h
 *
 *   flush the buffer assigned to a stream then insert one character into
 *   the buffer; return the character value on success or EOF on failure;
 *
 *   failure can occur if the pointer is invalid, the file is not opened
 *   for write, a file error exists or the buffer cannot be completely
 *   flushed for whatever reason;
 *
 *   this implementation assigns a buffer if one is not assigned; the new
 *   buffer size is determined by the _IONUNBUF flag bit;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "_stdio.h"

int _flushbuf (int c, FILE * fp) 

{
	int count;
	if ((fp != NULL) && ((fp->_flag & (_IOWRITE | _IOERR | _IOEOF)) == _IOWRITE)) 
	{
		if (fp->_base == NULL) 
		{
			_setbuf (fp, ((fp->_flag & (_IOUNBUF)) != 0)? NULL: (char *)(malloc (_BUFSIZE)));
		}
		count = fp->_ptr - fp->_base;
		if ((fp->_cnt = write (fp->_file, fp->_base, count)) == count) 
		{
			fp->_ptr = fp->_base;
			fp->_cnt = ((fp->_flag & (_IOUNBUF)) != 0)? 1: _BUFSIZE;
			*fp->_ptr++ = (unsigned char)(c);
			fp->_cnt--;
			return (c);
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

