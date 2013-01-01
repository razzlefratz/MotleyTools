/*====================================================================*
 *
 *   int _setvbuf(register FILE *fp, char *buffer, int *mode, size_t bufsize);
 *
 *   _stdio.h
 *
 *   This function assigns a buffer to the I/O stream associated with
 *   a file pointer and returns a pointer to the buffer; the buffer is
 *   then used for subsequent I/O on that stream; this function May be
 *   used to control the buffering characteristics of any I/O stream;
 *
 *   It should be called after a file is opened, but must be called
 *   prior to performing any I/O; otherwise data May be lost; if not used,
 *   subsequent stream I/O will be buffered as dictated by the default
 *   I/O library implementation;
 *
 *   If the specified buffer address is NULL, setbuf() will allocate an
 *   internal single character buffer causing subsequent file I/O to be
 *   unbuffered; otherwise, the specified buffer must be large enough to
 *   hold an entire input record as defined by the constant _BUFSIZE in
 *   STDIO.H.
 *
 *   For example, a stream May be set to 'buffered' I/O with:
 *
 *      _setbuf(fp,malloc(_BUFSIZE));
 *
 *   or set to 'unbuffered' I/O with:
 *
 *      _setbuf(fp,NULL);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "_stdio.h"

int _setvbuf (register FILE *fp, char *buffer, int mode, size_t bufsize) 

{
	extern char _unbuf [];
	if ((fp != NULL) && ((fp->_flag & (_IOREAD|_IOWRITE)) != 0) && ((fp->_flag & (_IOERR|_IOEOF)) == 0)) 
	{
		if ((fp->_flag & (_IOALLOC)) != 0) free (fp->_base);
		fp->_flag &= ~(_IOUNBUF|_IOALLOC);
		if (buffer != NULL) 
		{
			fp->_ptr = fp->_base = buffer;
			fp->_cnt = ((fp->_flag & (_IOREAD)) != 0)? (0):(bufsize);
			fp->_flag |= (_IOALLOC);
		}
		else 
		{
			fp->_ptr = fp->_base = &_unbuf [fp->_file];
			fp->_cnt = ((fp->_flag & (_IOREAD)) != 0)? (0):(1);
			fp->_flag |= (_IOUNBUF);
		}
		return (0);
	}
	else 
	{
		return (ERR);
	}
}

