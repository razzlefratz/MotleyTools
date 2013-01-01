/*====================================================================*
 *
 *   bool openauth (char const * filename, char const * registry) 
 *
 *   open the named file and return a valid file descriptor or -1
 *   on error; aside from normal open errors, an error can be the
 *   failure to open the named registry file or failure to locate
 *   the file digest in the registry;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef OPENAUTH_SOURCE
#define OPENAUTH_SOURCE

#include <unistd.h>
#include <errno.h>

#include "../crypt/SHA256.h"
#include "../files/files.h"

int openauth (char const * filename, char const * registry) 

{
	byte digest [SHA256_DIGEST_LENGTH];
	byte buffer [1024];
	signed reg;
	signed fd;
	if ((reg = open (registry, O_BINARY|O_RDONLY)) != -1) 
	{
		if ((fd = open (filename, O_BINARY|O_RDONLY)) != -1) 
		{
			SHA256Ident (fd, buffer, sizeof (buffer), digest);
			if (SHA256Match (reg, digest)) 
			{
				close (reg);
				return (fd);
			}
			close (fd);
		}
		close (reg);
	}
	errno = EACCES;
	return (-1);
}


/*====================================================================*
 *   demo/test program;
 *--------------------------------------------------------------------*/

#if 0

#include <stdio.h>

#include "../crypt/SHA256Reset.c"
#include "../crypt/SHA256Write.c"
#include "../crypt/SHA256Block.c"
#include "../crypt/SHA256Fetch.c"
#include "../crypt/SHA256Ident.c"
#include "../crypt/SHA256Match.c"
#include "../tools/error.c"

char const * program_name = "openauth";
int main (int argc, char const * argv []) 

{
	char const * registry;
	int fd;
	if (*++argv) 
	{
		registry = *argv;
	}
	while (*++argv) 
	{
		if ((fd = openauth (*argv, registry)) == -1) 
		{
			error (0, errno, "%s", *argv);
			continue;
		}
		error (0, 0, "Opened %s", *argv);
		close (fd);
	}
	return (0);
}


#endif

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

