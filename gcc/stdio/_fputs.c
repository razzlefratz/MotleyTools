/*====================================================================*
 *
 *   int _fputs(char *string, FILE *fp);
 *
 *   _stdio.h
 *
 *   copy a string to the buffer assigned to a file pointer; exclude the
 *   NUL terminator; return 0 on success and EOF on failure;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "_stdio.h"

int _fputs (char const *string, FILE *fp) 

{
	if (string != NULL) 
	{
		while (*string != (char)(0)) 
		{
			if (_fputc (*string++, fp) == EOF) 
			{
				return (EOF);
			}
		}
	}
	return (0);
}

