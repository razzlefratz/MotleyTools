/*====================================================================*
 *
 *   _iob[]
 *
 *   _stdio.h
 *
 *   allocate and initialize the i/o buffers for STDIN, STDOUT and STDERR.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "_stdio.h"

char _sibuf [_BUFSIZE] = 

{
	NUL
};

char _sobuf [_BUFSIZE] = 

{
	NUL
};

char _sebuf [_BUFSIZE] = 

{
	NUL
};

char _unbuf [_NFILE] = 

{
	NUL,
	NUL,
	NUL
};

FILE _iob [_NFILE] = 

{
	{
		STDIN,
		_IOREAD |_IOTEXT,
		_sibuf,
		_sibuf,
		0
	},
	{
		STDOUT,
		_IOWRITE|_IOTEXT,
		_sobuf,
		_sobuf,
		_BUFSIZE
	},
	{
		STDERR,
		_IOWRITE|_IOTEXT,
		_sebuf,
		_sebuf,
		_BUFSIZE
	}
};

