/*====================================================================*
 *
 *   int _ungetc(int c, FILE *fp);
 *
 *   _stdio.h
 *
 *   This function returns a character to the specified input stream
 *   and returns the character value on success or EOF on error.
 *
 *   A minimum of one character may be returned to any input stream
 *   after each call to _fgetc(), _fgets(s), _getc() or _gets() for the
 *   stream. The maximum number of returned characters will vary on
 *   circumstances.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "_stdio.h"

int _ungetc (int c, FILE * fp) 

{
	if ((fp != NULL) && ((fp->_flag & (_IOREAD | _IOERR | _IOEOF)) == _IOREAD) && (c != EOF)) 
	{
		if (fp->_ptr > fp->_base) 
		{
			++fp->_cnt;
			return (*--fp->_ptr = (char)(c));
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

