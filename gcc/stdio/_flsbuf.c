/*====================================================================*
 *
 *   int _flsbuf(int c, FILE *fp);
 *
 *   _stdio.h
 *
 *   flush the buffer assigned to a stream then insert one character into
 *   the buffer; return the character value on success or EOF on failure;
 *
 *   macro _flsbuf() defined in stdio.h is functionally equivalent.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "_stdio.h"

int _flsbuf (int c, FILE *fp) 

{
	if (_fflush (fp) == 0) 
	{
		*fp->_ptr++ = (unsigned char)(c);
		fp->_cnt--;
		return (c);
	}
	else 
	{
		return (EOF);
	}
}

