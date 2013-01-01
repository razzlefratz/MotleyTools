/*====================================================================*
 *
 *   int _filbuf(FILE *fp);
 *
 *   _stdio.h
 *
 *   fill the buffer assigned to a stream; return the first character on
 *   success or EOF on failure; reserve the vacant character position for
 *   one ungetc() call;
 *
 *   macro _filbuf() in stdio.h is functionally equivalent.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "_stdio.h"

int _filbuf (register FILE *fp) 

{
	if (_ffill (fp) == 0) 
	{
		int c = (unsigned int)(*fp->_ptr++);
		fp->_cnt--;
		return (c);
	}
	else 
	{
		return (EOF);
	}
}

