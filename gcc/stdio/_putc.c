/*====================================================================*
 *
 *   int _putc(int c, FILE *fp);
 *
 *   _stdio.h
 *
 *   output one character to the buffer assigned to a stream; return the
 *   character value on success or EOF on failure;
 *
 *   if the buffer is full then flush it it using fflush() which returns
 *   EOF if the buffer cannot be flushed;
 *
 *   if the character a newline and the file control block _IOTEXT flag
 *   bit is set then flush the buffer before return;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "_stdio.h"

int _putc (int c, FILE * fp) 

{
	if ((fp != NULL) && ((fp->_flag & (_IOWRITE | _IOERR | _IOEOF)) == _IOWRITE)) 
	{
		if ((fp->_cnt > 0) || (_fflush (fp) == 0)) 
		{
			*fp->_ptr++ = (char)(c);
			fp->_cnt--;
			if (((fp->_flag & (_IOTEXT)) != 0) && (c == '\n')) 
			{
				return ((_fflush (fp) == EOF)? (EOF): (c));
			}
			else 
			{
				return (c);
			}
		}
		else 
		{
			return (EOF);
		}
	}
	else 
	{
		return (EOF);
	}
}

