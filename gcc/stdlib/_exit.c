/*====================================================================*
 *
 *   void _exit(int status);
 *
 *   _stdio.h
 *
 *   terminate the current process after closing all open files; flush
 *   each output buffer before closing it; pass the specified status to
 *   the parent process; do not return to the calling program;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../stdio/_stdio.h"
#include "../stdlib/_stdlib.h"

void _exit (int status) 

{
	extern FILE _iob [_NFILE];
	int file;
	for (file = 0; file < _NFILE; file++) 
	{
		_fclose (&_iob [file]);
	}
	_exit (status);
}

