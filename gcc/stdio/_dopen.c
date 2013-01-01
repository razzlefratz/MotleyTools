/*====================================================================*
 *
 *   int _dopen(char const *pathname, char const *mode);
 *
 *   _stdio.h
 *
 *   This function opens or creates a file in the specified access mode
 *   and returns a file descriptor. ERR is returned if the file cannot
 *   be opened as requested.
 *
 *   This function if referenced but fopen() and freopen() to provide a
 *   standard interpretation of the access mode string. It also permits
 *   direct access to files which do not require a file control block.
 *
 *   See fdopen() to associate the file descriptor with a file pointer.
 *
 *   The preprocessor constant ERR, normally (-1), should be defined in
 *   file <stdio.h>;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "_stdio.h"
#include "_fcntl.h"

int _dopen (char const *path, char const *mode) 

{
	register int fd;
	if ((path != NULL) && (mode != NULL) && (*mode != NUL)) 
	{

#ifdef _WIN32

		unsigned oflag = _O_RDONLY;
		unsigned pflag = 0;
		unsigned tflag = _O_BINARY;
		while (*mode) switch (*mode++) 
		{
		case 'r':
			oflag = _O_RDONLY;
			break;
		case 'w':
			oflag = _O_CREAT|_O_WRONLY;
			pflag = _O_TRUNC;
			break;
		case 'a':
			oflag = _O_CREAT|_O_WRONLY;
			pflag = _O_APPEND;
			break;
		case '+':
			oflag = _O_RDWR;
			break;
		case 'b':
			tflag = _O_BINARY;
			break;
		case 't':
			tflag = _O_TEXT;
			break;
		default:
			return (ERR);
		}
		fd = _open (path, oflag|pflag|tflag, _S_IREAD|_S_IWRITE, 0);

#else

		if (*mode == 'r') fd = open (path, _O_RDONLY, 0);
		else if (*mode == 'w') fd = creat (path, _O_WRONLY);
		else if (*mode == 'a') 
		{
			if ((fd = open (path, (_O_RDONLY), 0)) > 0) _lseek (fd, 0L, 2);
			else fd = creat (path, (_O_WRONLY));
		}
		else fd = ERR;

#endif

	}
	else fd = ERR;
	return (fd);
}

