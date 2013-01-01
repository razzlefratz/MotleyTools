/*====================================================================*
 *
 *   unget.c - token replacement primatives;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "_stdio.h"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#ifndef _MAXUNGET
#define _MAXUNGET 0x0400
#endif

static unsigned char buffer [_MAXUNGET] = 

{
	NUL
};

static size_t bufcnt = 0;

/*====================================================================*
 *
 *   int _getc(FILE *stream);
 *
 *   _stdio.h
 *
 *   return one character from an input stream unless other characters
 *   have been buffered by ungetchr(); in that case, return the last
 *   buffered character, instead.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

int _getc (FILE *stream) 

{
	signed c;
	if ((stream == NULL) || ((stream->_flag & (_IOREAD|_IOERR|_IOEOF)) != _IOREAD)) 
	{
		c = EOF;
	}
	else if (bufcnt > 0) 
	{
		c = buffer [--bufcnt];
	}
	else 
	{
		c = _getc (stream);
	}
	return (c);
}


/*====================================================================*
 *
 *   int _ungetc(FILE *stream);
 *
 *   _stdio.h
 *
 *   push one character back into an input stream;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

int _ungetc (int c, FILE *stream) 

{
	if ((c == EOF) || ((stream == NULL) && ((stream->_flag & (_IOREAD|_IOERR|_IOEOF)) != _IOREAD))) 
	{
		c = EOF;
	}
	else if (bufcnt < _MAXUNGET) 
	{
		buffer [bufcnt++] = (unsigned int)(c);
	}
	else 
	{
		c = EOF;
	}
	return (c);
}


/*====================================================================*
 *
 *   int _ungets(char *string, FILE *stream);
 *
 *   _stdio.h
 *
 *   push a string back into to an input stream;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char *_ungets (char *string, FILE *stream) 

{
	char *cp = string;
	if (string) 
	{
		while (*cp) cp++;
		while (cp-- > string) _ungetc (*cp, stream);
	}
	return (string);
}

