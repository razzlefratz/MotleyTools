/*====================================================================*
 *
 *   void _setbuf(FILE *fp, char *buffer);
 *
 *   _stdio.h
 *
 *   assign a special buffer to the file control block addressed by the
 *   FILE pointer argument; if the buffer argument is NULL then assign a
 *   one-byte buffer;
 *
 *   a custom buffer may be assigned after the file is opened but before
 *   i/o is performed; if no buffer is assigned then subsequent i/o will
 *   be buffered as dictated by the default i/o library implementation;
 *
 *   For example, a stream May be set to 'buffered' I/O with:
 *
 *      _setbuf(fp,malloc(_BUFSIZE));
 *
 *   or set to 'unbuffered' I/O with:
 *
 *      _setbuf(fp, NULL);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "_stdio.h"

void _setbuf (register FILE *fp, char *buffer) 

{
	extern char _unbuf [];
	if ((fp != NULL) && ((fp->_flag & (_IOREAD|_IOWRITE)) != 0) && ((fp->_flag & (_IOERR|_IOEOF)) == 0)) 
	{
		if ((fp->_flag & (_IOALLOC)) != 0) free (fp->_base);
		fp->_flag &= ~(_IOUNBUF|_IOALLOC);
		if (buffer != NULL) 
		{
			fp->_ptr = fp->_base = buffer;
			fp->_cnt = ((fp->_flag & (_IOREAD)) != 0)? (0):(_BUFSIZE);
			fp->_flag |= (_IOALLOC);
		}
		else 
		{
			fp->_ptr = fp->_base = &_unbuf [fp->_file];
			fp->_cnt = ((fp->_flag & (_IOREAD)) != 0)? (0):(1);
			fp->_flag |= (_IOUNBUF);
		}
	}
	return;
}

