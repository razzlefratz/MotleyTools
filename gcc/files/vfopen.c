/*====================================================================*
 *
 *   bool vfopen(char const *pathname);
 *
 *   open the named file as stdout; rename it by appending a numeric
 *   file extension that serves as a file version number; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef VFOPEN_SOURCE
#define VFOPEN_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../files/files.h"
#include "../tools/types.h"
#include "../tools/error.h"

bool vfopen (char const *filename) 

{
	struct stat loadstat;
	struct stat savestat;
	char loadname [FILENAME_MAX];
	char savename [FILENAME_MAX];
	unsigned bailout = 0;
	unsigned version = 0;
	unsigned maximum = 0;
	char *extender;
	makepath (loadname, getenv ("PWD"), filename);
	makepath (savename, getenv ("PWD"), filename);
	if (lstat (loadname, &loadstat)) 
	{
		error (bailout, errno, "Can't open %s", loadname);
		return (false);
	}
	if (S_ISDIR (loadstat.st_mode)) 
	{
		error (bailout, 0, "Won't open %s: file is a folder", loadname);
		return (false);
	}
	if (S_ISLNK (loadstat.st_mode)) 
	{
		error (bailout, 0, "Won't open %s: file is a symlink", loadname);
		return (false);
	}
	if (S_ISBLK (loadstat.st_mode)) 
	{
		error (bailout, 0, "Won't open %s: file is a device", loadname);
		return (false);
	}
	if (S_ISCHR (loadstat.st_mode)) 
	{
		error (bailout, 0, "Won't open %s: file is a device", loadname);
		return (false);
	}
	if (S_ISFIFO (loadstat.st_mode)) 
	{
		error (bailout, 0, "Won't open %s: file is a fifo", loadname);
		return (false);
	}
	if (S_ISSOCK (loadstat.st_mode)) 
	{
		error (bailout, 0, "Won't open %s: file is a socket", loadname);
		return (false);
	}
	for (version = FILE_VER_MAX; version > 0; version /= 10) 
	{
		maximum++;
	}
	for (extender = savename; *extender; extender++);
	*extender++ = FILE_C_EXTENDER;
	for (version = 1; version < FILE_VER_MAX; version++) 
	{
		unsigned value = version;
		unsigned digit = maximum;
		for (extender [digit] = (char) (0); digit-- > 0; value /= 10) 
		{
			extender [digit] = (value % 10) + '0';
		}
		if (lstat (savename, &savestat)) 
		{
			if (!freopen (loadname, "rb", stdin)) 
			{
				error (bailout, errno, "Can't open %s for input", loadname);
				return (false);
			}
			if (rename (loadname, savename)) 
			{
				error (bailout, errno, "Can't rename %s as %s", loadname, savename);
				return (false);
			}
			if (!freopen (loadname, "wb", stdout)) 
			{
				error (bailout, errno, "Can't open %s for output", loadname);
				return (false);
			}
			if (chmod (loadname, loadstat.st_mode)) 
			{
				error (bailout, errno, "Can't preserve %s permissions", loadname);
				return (false);
			}
			if (chown (loadname, loadstat.st_uid, loadstat.st_gid)) 
			{
				error (bailout, errno, "Can't preserve %s ownership", loadname);
				return (false);
			}
			return (true);
		}
	}
	error (bailout, 0, "Won't open %s: Too many file versions", loadname);
	return (false);
}


#endif

