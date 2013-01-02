/*====================================================================*
 *
 *   opathspec.cpp - implementation of the opathspec class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oPATH_SOURCE
#define oPATH_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstdlib>
#include <cstring>

#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "files.h"
#include "find.h"

#include "../classes/oerror.hpp"
#include "../classes/opathspec.hpp"

/*====================================================================*
 *   private objects; 
 *--------------------------------------------------------------------*/

struct stat mstatinfo;

/*====================================================================*
 *
 *   bool isdotdir (cchar const *filename);
 *
 *   return true if filename is a dotted directory; treat NULL,  
 *   NIL,  "." and ".." as dotted directory names;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool opathspec::isdotdir (char const *filename) 

{
	if (filename == (char *) (0)) 
	{
		return (true);
	}
	if (*filename == FILE_C_EXTENDER) 
	{
		filename++;
	}
	if (*filename == FILE_C_EXTENDER) 
	{
		filename++;
	}
	return (*filename == (char) (0));
}


/*====================================================================*
 *
 *   bool exists (char const *filename);
 *
 *   return true of the filename exists; the basename portion can 
 *   have wildcard characters but the pathname portion many not; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool opathspec::exists (char const *filename) 

{
	return (!stat (filename, &this->mstatinfo));
}


/*====================================================================*
 *
 *   bool infolder (char pathname[], char const *wildcard, bool recurse);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool opathspec::infolder (char pathname [], char const *wildcard, bool recurse) 

{
	DIR *dir;
	if ((dir = opendir (pathname)) != (DIR *) (0)) 
	{
		struct dirent *dirent;
		char * filename;
		for (filename = pathname; *filename != (char) (0); filename++);
		*filename = PATH_C_EXTENDER;
		while ((dirent = readdir (dir)) != (struct dirent *) (0)) 
		{
			std::strcpy (filename + 1, dirent->d_name);
			if (lstat (pathname, &this->mstatinfo)) 
			{
				oerror::error (0, errno, pathname);
				continue;
			}
			if (S_ISDIR (this->mstatinfo.st_mode)) 
			{
				if (opathspec::isdotdir (dirent->d_name)) 
				{
					continue;
				}
				if (recurse) 
				{
					if (opathspec::infolder (pathname, wildcard, recurse)) 
					{
						closedir (dir);
						return (true);
					}
				}
				continue;
			}
			if (S_ISREG (this->mstatinfo.st_mode)) 
			{
				if (opathspec::match (filename + 1, wildcard)) 
				{
					closedir (dir);
					return (true);
				}
				continue;
			}
		}
		*filename = (char) (0);
		closedir (dir);
	}
	return (false);
}


/*====================================================================*
 *
 *   bool invector (char fullname[], char const *pathname[], char const *filename);
 *
 *   return true if filename is present in any folder listed in
 *   NULL terminated vector pathname; otherwise, return false; use 
 *   fullname as a scratch buffer;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool opathspec::invector (char fullname [], char const *pathname [], char const *filename) 

{

#ifdef CMASSOC_SAFEMODE

	if (!fullname) 
	{
		return (false);
	}
	if (!pathname) 
	{
		return (false);
	}
	if (!filename) 
	{
		return (false);
	}

#endif

	while (*pathname) 
	{
		opathspec::makepath (fullname, *pathname++, filename);
		if (!stat (fullname, &this->mstatinfo)) 
		{
			return (true);
		}
	}
	return (false);
}


/*====================================================================*
 *
 *   bool invector (char fullname[], char const *pathname[], char const *filename);
 *
 *   return true if filename is present in any folder listed in
 *   NULL teminated vector pathname; otherwise, return false; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool opathspec::invector (char fullname [], char const *pathname [], char const *filename, bool recurse) 

{

#ifdef CMASSOC_SAFEMODE

	if (!fullname) 
	{
		return (false);
	}
	if (!pathname) 
	{
		return (false);
	}
	if (!filename) 
	{
		return (false);
	}

#endif

	while (*pathname) 
	{
		char tempname [FILENAME_MAX];
		opathspec::makepath (fullname, *pathname++, filename);
		opathspec::partpath (fullname, fullname, tempname);
		if (opathspec::infolder (fullname, tempname, recurse)) 
		{
			return (true);
		}
	}
	return (false);
}


/*====================================================================*
 *
 *   bool instring (char *fullname[], char const *pathname, char const *filename);
 *
 *   return true if the named file is present in one of the folders listed 
 *   in the NUL terminated path string; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool opathspec::instring (char fullname [], char const *pathname, char const *filename) 

{

#ifdef CMASSOC_SAFEMODE

	if (!fullname) 
	{
		return (false);
	}
	if (!pathname) 
	{
		return (false);
	}
	if (!filename) 
	{
		return (false);
	}

#endif

	while (*pathname) 
	{
		char *string;
		for (string = fullname; *pathname != (char) (0); *string++ = *pathname++) 
		{
			if (*pathname == PATH_C_EXTENDER) 
			{
				pathname++;
				break;
			}
		}
		*string = (char) (0);
		opathspec::makepath (fullname, fullname, filename);
		if (!stat (fullname, &this->mstatinfo)) 
		{
			return (true);
		}
	}
	return (false);
}


/*====================================================================*
 *
 *   bool instring (char *fullname[], char const *pathname, char const *filename);
 *
 *   return true if the named file is present in one of the folders listed 
 *   in the NUL terminated path string; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool opathspec::instring (char fullname [], char const *pathname, char const *filename, bool recurse) 

{

#ifdef CMASSOC_SAFEMODE

	if (!fullname) 
	{
		return (false);
	}
	if (!pathname) 
	{
		return (false);
	}
	if (!filename) 
	{
		return (false);
	}

#endif

	while (*pathname) 
	{
		char tempname [FILENAME_MAX];
		char *string;
		for (string = fullname; *pathname != (char) (0); *string++ = *pathname++) 
		{
			if (*pathname == PATH_C_EXTENDER) 
			{
				pathname++;
				break;
			}
		}
		*string = (char) (0);
		opathspec::makepath (fullname, fullname, filename);
		opathspec::partpath (fullname, fullname, tempname);
		if (opathspec::infolder (fullname, tempname, recurse)) 
		{
			return (true);
		}
	}
	return (false);
}


/*====================================================================*
 *
 *   char const *dirname (char const *filespec);
 *
 *   return directory portion of filespec; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const *opathspec::dirname (char const *filespec) 

{
	static char buffer [FILENAME_MAX];
	char *pathname = std::strcpy (buffer, filespec);
	for (filespec = (char const *) (buffer); *filespec; filespec++) 
	{
		if (*filespec == PATH_C_EXTENDER) 
		{
			pathname = (char *) (filespec);
		}
	}
	if (*pathname != PATH_C_EXTENDER) 
	{
		*pathname++ = FILE_C_EXTENDER;
	}
	*pathname = (char) (0);
	return (buffer);
}


/*====================================================================*
 *
 *   char const *basename (char const *filespec);
 *
 *   return filename portion of filespec; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const *opathspec::basename (char const *filespec) 

{
	char const *filename = filespec;
	while (*filespec) 
	{
		if (*filespec++ == PATH_C_EXTENDER) 
		{
			filename = filespec;
		}
	}
	return (filename);
}


/*====================================================================*
 *
 *   void findpath (char const *filespec, char *pathname, char *filename);
 *
 *   scan filespec and copy the path component into the pathname
 *   buffer and file component into the filename buffer; missing
 *   components are not expanded; expand missing components with
 *   aother function; see ofindfile::makefind() for one example;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void opathspec::findpath (char const *filespec, char *pathname, char *filename) 

{
	this->partpath (filespec, pathname, filename);
	if ((pathname) && (!*pathname)) 
	{
		*pathname++ = FILE_C_EXTENDER;
		*pathname = (char) (0);
	}
	if ((filename) && (!*filename)) 
	{
		*filename++ = FILE_C_EXTENDER;
		*filename = (char) (0);
	}
	return;
}


/*====================================================================*
 *
 *   void partpath (char const *filespec, char *pathname, char *filename);
 *
 *   scan filespec and copy the path component into the pathname
 *   buffer and file component into the filename buffer; missing
 *   components are not expanded; expand missing components with
 *   aother function; see ofindfile::makefind() for one example;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void opathspec::partpath (char const *filespec, char *pathname, char *filename) 

{
	char const *string;

#ifdef CMASSOC_SAFEMODE

	if (!filespec) 
	{
		return (false);
	}
	if (!pathname) 
	{
		return (false);
	}
	if (!filename) 
	{
		return (false);
	}

#endif

	for (string = filespec; *string; string++) 
	{
		if (*string == PATH_C_EXTENDER) 
		{
			while (filespec < string) 
			{
				*pathname++ = *filespec++;
			}
		}
	}
	if (*filespec == PATH_C_EXTENDER) 
	{
		filespec++;
	}
	while (filespec < string) 
	{
		*filename++ = *filespec++;
	}
	*pathname++ = (char) (0);
	*filename++ = (char) (0);
	return;
}


/*====================================================================*
 *
 *   void partfile (char const *filespec, char filename[], char extender[]);
 *
 *   scan filespec and copy the name component into the filename
 *   buffer and type component into the extender buffer; missing
 *   components are not expanded; expand missing components with
 *   aother function; see ofindfile::makefind() for one example;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void opathspec::partfile (char const *filespec, char filename [], char extender []) 

{
	char const *string;

#ifdef CMASSOC_SAFEMODE

	if (!filespec) 
	{
		return (false);
	}
	if (!pathname) 
	{
		return (false);
	}
	if (!filename) 
	{
		return (false);
	}

#endif

	for (string = filespec; *string; string++) 
	{
		if ((*string == PATH_C_EXTENDER) || (*string == FILE_C_EXTENDER)) 
		{
			while (filespec < string) 
			{
				*filename++ = *filespec++;
			}
		}
	}
	if (*filespec == FILE_C_EXTENDER) 
	{
		filespec++;
		while (filespec < string) 
		{
			*extender++ = *filespec++;
		}
	}
	else 
	{
		while (filespec < string) 
		{
			*filename++ = *filespec++;
		}
	}
	*filename++ = (char) (0);
	*extender++ = (char) (0);
	return;
}


/*====================================================================*
 *
 *   void fullpath (char fullname[], char const *filespec);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void opathspec::fullpath (char fullname [], char const *filespec) 

{
	this->makepath (fullname, getenv ("PWD"), filespec);
	return;
}


/*====================================================================*
 *
 *   void makepath (char fullname[], char const *pathname, char const *filename);
 *
 *   split the pathname string and filename string into constituent;
 *   weed through the stack and write a clean pathname string in the 
 *   fullname buffer;
 *
 *   pathname is split into constituents then filename is split into
 *   constituents and appended to those from pathname; when filename
 *   filename starts with slash; then its constituents replace those 
 *   those from pathname; the result is a vector of strings "", ".", 
 *   ".." and real filenames;
 *
 *   we preserve leading "" strings then collect remaining strings except
 *   for "", "." and ".." strings; each "" and "." is discarded and ".." 
 *   discarded after decrementing the accumulation counter; the resulting
 *   string vector is copied to the baseline string argument with slashes
 *   to separate each strings;
 *  
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void opathspec::makepath (char fullname [], char const *pathname, char const *filename) 

{
	char mpathname [FILENAME_MAX];
	char mfilename [FILENAME_MAX];

#ifdef CMASSOC_SAFEMODE

	if (fullname == (char *) (0)) 
	{
		return;
	}
	if (pathname == (char *) (0)) 
	{
		return;
	}

#endif

	this->mcount = 0;
	this->mstack [this->mcount] = (char *) (0);
	opathspec::splitpath (std::strcpy (mpathname, pathname));
	opathspec::splitpath (std::strcpy (mfilename, filename));
	opathspec::mergepath ();
	std::strcpy (fullname, this->mstack [0]);
	for (this->mindex = 1; this->mindex < this->mlevel; this->mindex++) 
	{
		std::strcat (fullname, PATH_S_EXTENDER);
		std::strcat (fullname, this->mstack [this->mindex]);
	}
	return;
}


/*====================================================================*
 *
 *   void splitpath (char *pathname)
 *
 *   split the pathname string into constituent filenames and push themn
 *   on the filename stack; clear the stack before start if the pathname
 *   starts with slash. 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void opathspec::splitpath (char filespec []) 

{

#ifdef CMASSOC_SAFEMODE

	if (filespec == (char *) (0)) 
	{
		return;
	}

#endif

	if (*filespec == PATH_C_EXTENDER) 
	{
		this->mcount = 0;
	}
	for (this->mstack [this->mcount++] = filespec; *filespec != (char) (0); filespec++) 
	{
		if (*filespec == PATH_C_EXTENDER) 
		{
			if (this->mcount < this->mlimit) 
			{
				this->mstack [this->mcount++] = filespec + 1;
			}
			*filespec = (char) (0);
		}
	}
	return;
}


/*====================================================================*
 *
 *   void mergepath ()
 *
 *   split the pathname string into constituent filenames and push themn
 *   on the filename stack; clear the stack before start if the pathname
 *   starts with slash. 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void opathspec::mergepath () 

{
	for (this->mindex = this->mstart = this->mlevel = 1; this->mindex < this->mcount; this->mindex++) 
	{
		int dots = 0;
		while (this->mstack [this->mindex] [dots] == FILE_C_EXTENDER) 
		{
			dots++;
		}
		if (this->mstack [this->mindex] [dots] != (char) (0)) 
		{
			this->mstack [this->mlevel++] = this->mstack [this->mindex];
		}
		else if (dots > 2) 
		{
			this->mstack [this->mlevel++] = this->mstack [this->mindex];
		}
		else if (dots > 1) 
		{
			if (this->mlimit == this->mstart) 
			{
				this->mstack [this->mlevel++] = this->mstack [this->mindex];
				this->mstart++;
			}
			else 
			{
				this->mlevel--;
			}
		}
	}
	return;
}


/*====================================================================*
 *
 *   opathspec ();
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

opathspec::opathspec () 

{
	this->mstack = new char * [DIRLEVEL_MAX];
	this->mlimit = DIRLEVEL_MAX;
	this->mcount = 0;
	this->mlevel = 0;
	this->mindex = 0;
	return;
}


/*====================================================================*
 *
 *   ~opathspec ()
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

opathspec::~opathspec () 

{
	delete [] this->mstack;
	return;
}


/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif

