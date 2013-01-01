/*====================================================================*
 *
 *   void getviewport(unsigned *rows, unsigned *cols);
 *
 *   linux.h
 * 
 *   update the row and column variable stored at the given address
 *   unless the address is void; determine row and column values as
 *   a function of console window size;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef GETVIEWPORT_SOURCE
#define GETVIEWPORT_SOURCE

#include <stdlib.h>
#include <unistd.h>

#ifdef __linux__
#include <sys/ioctl.h>
#include <termios.h>
#endif

#include "../linux/linux.h"

void getviewport (unsigned *rows, unsigned *columns) 

{

#ifdef TIOCGWINSZ

	struct winsize winsize;
	if (ioctl (STDOUT_FILENO, TIOCGWINSZ, &winsize) != -1) 
	{
		if ((rows) && (winsize.ws_row > 0)) 
		{
			*rows = winsize.ws_row;
		}
		if ((columns) && (winsize.ws_col > 0)) 
		{
			*columns = winsize.ws_col;
		}
	}

#endif

	return;
}


#endif

