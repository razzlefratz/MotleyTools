/*====================================================================*
 *
 *   int _getc(FILE *fp);
 *
 *   _stdio.h
 *
 *   Return next character from buffered input stream or EOF on end-of-file.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include  "../stdio/_stdio.h"

int _getc (FILE * fp) 

{
	if ((fp != NULL) && ((fp->_flag & (_IOREAD | _IOERR | _IOEOF)) == _IOREAD)) 
	{
		if ((fp->_cnt > 0) || (_fillbuf (fp) == 0)) 
		{
			fp->_cnt--;
			return ((unsigned int)(*fp->_ptr++));
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

