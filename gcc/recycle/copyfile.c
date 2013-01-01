/*====================================================================*
 *
 *   int copyfile (char *oldfilename, char *ofn, struct stat *logstat, flag_t flags);
 *
 *   copy one file to another; abandon the operation on failure but 
 *   do not remove the new file; this preserves partial data should 
 *   the disk fill up;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include "../recycle/recycle.h"
#include "../tools/types.h"
#include "../tools/error.h"

int copyfile (char const *ifn, char const *ofn, struct stat *statinfo, flag_t flags) 

{
	file_t ifd = -1;
	file_t ofd = -1;
	char buffer [BUFSIZ];
	ssize_t count;
	if ((ifd = open (ifn, O_RDWR)) < 0) 
	{
		error (0, errno, "can't open %s for reading", ifn);
		return (1);
	}
	if ((ofd = open (ofn, O_WRONLY | O_CREAT | O_TRUNC, statinfo->st_mode)) < 0) 
	{
		error (0, errno, "can't open %s for writing", ofn);
		close (ifd);
		return (1);
	}
	if (fchmod (ofd, statinfo->st_mode)) 
	{
		error (0, errno, "can't set %s permissions", ofn);
		close (ifd);
		close (ofd);
		return (1);
	}
	if (fchown (ofd, statinfo->st_uid, statinfo->st_gid)) 
	{
		error (0, errno, "can't set %s ownership", ofn);
		close (ifd);
		close (ofd);
		return (1);
	}
	while ((count = read (ifd, buffer, sizeof (buffer))) > 0) 
	{
		if (write (ofd, buffer, count) != count) 
		{
			error (0, errno, "error writing to %s", ofn);
			close (ifd);
			close (ofd);
			return (1);
		}
	}
	if (count < 0) 
	{
		error (0, errno, "error reading %s", ifn);
		close (ifd);
		close (ofd);
		return (1);
	}
	if (ftruncate (ifd, 0)) 
	{
		error (0, errno, "error truncating %s", ifn);
		close (ifd);
		close (ofd);
		return (1);
	}
	else 
	{
		close (ifd);
		close (ofd);
	}
	return (0);
}

