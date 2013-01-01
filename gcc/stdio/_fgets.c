/*====================================================================*
 *
 *   char *_fgets(char *buffer, size_t length, FILE *fp);
 *
 *   _stdio.h
 *
 *   This function returns a pointer to a string of limited length
 *   from the input stream associated with a file pointer. NULL is
 *   returned on end-of-file or error.
 *
 *   The read terminates with the first newline character, which is
 *   included in the string; otherwise, the read terminates when the
 *   string fills. In either case, the string is terminated with a
 *   null byte.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "_stdio.h"

char *_fgets (char *buffer, size_t length, FILE *fp) 

{
	register char *bp = buffer;
	register signed c;
	if (bp != NULL) 
	{
		while ((length-- > 0) && ((c = _fgetc (fp)) != EOF) && ((*bp++ = (unsigned char)(c)) != '\n'));
		*bp = (char)(0);
	}
	return (((bp > buffer) || (c != EOF))? buffer: (char *)(0));
}

