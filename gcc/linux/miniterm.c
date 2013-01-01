/*
 *  AUTHOR: Sven Goldt (goldt@math.tu-berlin.de)
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 */

/*
 *   This is like all programs in the Linux Programmer's Guide meant
 *   as a simple practical demonstration. It can be used as a base for 
 *   a real terminal program.
 */

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/signal.h>

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define BAUDRATE B38400
#define MODEMDEVICE "/dev/ttyS0"
#define ENDMINITERM 2 /* ctrl-b to quit miniterm */
#define _POSIX_SOURCE 1 /* POSIX compliant source */

#define FALSE 0
#define TRUE 1

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

volatile int STOP=FALSE;

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

void child_handler (int s) 

{
	STOP=TRUE;
}


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	struct termios oldtio;
	struct termios newtio;
	struct termios oldstdtio;
	struct termios newstdtio;
	struct sigaction sa;
	signed fd;
	signed c;
	if ((fd = open (MODEMDEVICE, O_RDWR | O_NOCTTY)) < 0) 
	{
		perror (MODEMDEVICE);
		exit (-1);
	}
	tcgetattr (fd, &oldtio);
	newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;
	newtio.c_iflag = IGNPAR;
	newtio.c_oflag = 0;
	newtio.c_lflag = 0;
	newtio.c_cc [VMIN]=1;
	newtio.c_cc [VTIME]=0;
	tcflush (fd, TCIFLUSH);
	tcsetattr (fd, TCSANOW, &newtio);

/*
 *   Strange, but if you uncomment this command miniterm will not work
 *   even if you stop canonical mode for stdout. This is a linux bug.
 */

	tcsetattr (1, TCSANOW, &newtio);
	tcgetattr (0, &oldstdtio);
	tcgetattr (0, &newstdtio);
	newstdtio.c_lflag &= ~(ICANON | ECHO);
	tcsetattr (0, TCSANOW, &newstdtio);
	switch (fork ()) 
	{
	case 0:
		close (1);
		for (c = getchar (); c != ENDMINITERM; c = getchar ()) 
		{
			write (fd, &c, 1);
		}
		tcsetattr (fd, TCSANOW, &oldtio);
		tcsetattr (0, TCSANOW, &oldstdtio);
		close (fd);
		exit (0);
		break;
	case -1:
		perror ("fork");
		tcsetattr (fd, TCSANOW, &oldtio);
		close (fd);
		exit (-1);
	default:
		close (0);
		sa.sa_handler = child_handler;
		sa.sa_flags = 0;
		sigaction (SIGCHLD, &sa, NULL);
		while (STOP==FALSE) 
		{
			read (fd, &c, 1);
			write (1, &c, 1);
		}
		wait (NULL);
		break;
	}
}

