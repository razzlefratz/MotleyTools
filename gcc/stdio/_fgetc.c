/*====================================================================*
 *
 *   int _fgetc(FILE *fp);
 *
 *   _stdio.h
 *
 *   return the next character from the specified input stream; return
 *   EOF on end-of-file or error;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

#include "_stdio.h"

int _fgetc (FILE * fp) 

{
	if ((fp != NULL) && ((fp->_flag & (_IOREAD | _IOERR | _IOEOF)) == _IOREAD)) 
	{
		if ((fp->_cnt > 0) || (_fillbuf (fp) == 0)) 
		{
			fp->_cnt--;
			return ((unsigned)(*fp->_ptr++));
		}
	}
	else 
	{
		return (EOF);
	}
}

