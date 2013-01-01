/*====================================================================*
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

#include "../tools/types.h"
#include "../tools/error.h"
#include "../files/files.h"
#include "../files/find.h"

void findfile (FIND * find, void function (FIND *, flag_t), flag_t flags);
void testfile (FIND * find, void function (FIND *, flag_t), flag_t flags);

/*====================================================================*
 *
 *   void findfile (FIND * find, void function(FIND *, flag_t), flag_t flags);
 *
 *   search a folder and check each file; optionaly recurse through
 *   subfolders or traverse symbolic links or exit on first error; 
 *
 *   FIND is defined files.h; it contains multiple buffers
 *   to store filename components, a flagword and a stat structure;
 *   it avoids littering the code with stray buffers and pointers;
 *
 *   this is a standard module structure used throughout the motley
 *   tools suite; it should be kept free of functionality and error
 *   handling;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void findfile (FIND * find, void function (FIND *, flag_t), flag_t flags) 

{
	DIR *dir;
	if ((dir = opendir (find->fullname))) 
	{
		struct dirent *dirent;
		char *filename;
		strcpy (find->pathname, find->fullname);
		for (filename = find->fullname; *filename != (char) (0); filename++);
		*filename = PATH_C_EXTENDER;
		while ((dirent = readdir (dir))) 
		{
			strcpy (find->filename, dirent->d_name);
			strcpy (filename + 1, dirent->d_name);
			if (lstat (find->fullname, &find->statinfo)) 
			{
				error (0, errno, "can't read %s file information", find->fullname);
			}
			else if (S_ISDIR (find->statinfo.st_mode)) 
			{
				if (isdotdir (dirent->d_name)) 
				{
					continue;
				}
				if (flags & (FIND_B_RECURSE)) 
				{
					findfile (find, function, flags);
				}
			}
			else if (S_ISLNK (find->statinfo.st_mode)) 
			{
				if (flags & (FIND_B_TRAVERSE)) 
				{
					function (find, flags);
				}
			}
			else if (S_ISREG (find->statinfo.st_mode)) 
			{
				function (find, flags);
			}
			else if (S_ISBLK (find->statinfo.st_mode)) 
			{
				function (find, flags);
			}
			else if (S_ISCHR (find->statinfo.st_mode)) 
			{
				function (find, flags);
			}
			else if (S_ISFIFO (find->statinfo.st_mode)) 
			{
				function (find, flags);
			}
			else if (S_ISSOCK (find->statinfo.st_mode)) 
			{
				function (find, flags);
			}
		}
		*filename = (char) (0);
		closedir (dir);
	}
	else 
	{
		error (0, 0, "%s is not a folder.", find->fullname);
	}
	return;
}


/*====================================================================*
 *
 *   void testfile (FIND * find, void function (FIND *, flag_t), flag_t flags);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void testfile (FIND * find, void function (FIND *, flag_t), flag_t flags) 

{
	if (lstat (find->fullname, &find->statinfo)) 
	{
		error (0, errno, "can't read %s file information.", find->fullname);
	}
	else if (S_ISDIR (find->statinfo.st_mode)) 
	{
		findfile (find, function, flags);
	}
	else if (S_ISREG (find->statinfo.st_mode)) 
	{
		function (find, flags);
	}
	else if (S_ISLNK (find->statinfo.st_mode)) 
	{
		function (find, flags);
	}
	else if (S_ISBLK (find->statinfo.st_mode)) 
	{
		function (find, flags);
	}
	else if (S_ISCHR (find->statinfo.st_mode)) 
	{
		function (find, flags);
	}
	else if (S_ISFIFO (find->statinfo.st_mode)) 
	{
		function (find, flags);
	}
	else if (S_ISSOCK (find->statinfo.st_mode)) 
	{
		function (find, flags);
	}
	return;
}

