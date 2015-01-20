/*====================================================================*
 *
 *   ofindspec.cpp - implementation of the ofindspec class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oFINDSPEC_SOURCE
#define oFINDSPEC_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstring>
#include <cstdlib>
#include <iostream>

#include <errno.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ofindspec.hpp"

#include "../../gcc/files/files.h"
#include "../../gcc/files/find.h"

/*====================================================================*
 *
 *   char const *ofindspec::fullname();
 *
 *   return the fullname as a constant string;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * ofindspec::fullname ()

{
	std::strncpy (this->mtempname, this->mpathname, FILENAME_MAX);
	if ((* this->mpathname != (char) (0)) && (* this->mfilename != (char) (0)))
	{
		std::strncat (this->mtempname, PATH_S_EXTENDER, FILENAME_MAX);
	}
	std::strncat (this->mtempname, this->mfilename, FILENAME_MAX);
	return (this->mtempname);
}

/*====================================================================*
 *
 *   ofindspec & ofindspec::fullname(char const *filespec);
 *
 *   assign a new filespec to this object instance; separate the pathname,
 *   basename, title and class components;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ofindspec & ofindspec::fullname (char const * filespec)

{

#ifdef CMASSOC_SAFEMODE

	if (filespec == (char const *) (0))
	{
		return (* this);
	}

#endif

	ofindspec::pathspec.makepath (this->mtempname, std::getenv ("PWD"), filespec);
	ofindspec::pathspec.partpath (this->mtempname, this->mpathname, this->mfilename);
	ofindspec::pathspec.partfile (this->mfilename, this->mbasename, this->mextender);
	if (* this->mpathname == (char) (0))
	{
		this->mpathname [0] = FILE_C_EXTENDER;
		this->mpathname [1] = (char) (0);
	}
	if (* this->mfilename == (char) (0))
	{
		this->mfilename [0] = FILE_C_EXTENDER;
		this->mfilename [1] = (char) (0);
	}
	strcpy (this->mtempname, this->mpathname);
	strcat (this->mtempname, PATH_S_EXTENDER);
	strcat (this->mtempname, this->mfilename);
	switch (this->mfindmode)
	{
	case FIND_M_NORMAL:
		strcpy (this->mwildcard, this->mfilename);
		break;
	case FIND_M_SEARCH:
		strcpy (this->mtempname, this->mpathname);
		strcpy (this->mwildcard, this->mfilename);
		break;
	default: 
		oerror::error (1, EINVAL, "makefind (..., code_t mode)");
	}
	if (* this->mwildcard == FILE_C_EXTENDER)
	{
		this->mwildcard [0] = FILE_C_WILDCARD;
		this->mwildcard [1] = (char) (0);
	}
	return (* this);
}

/*====================================================================*
 *
 *   char const *ofindspec::pathname() const;
 *
 *   return the pathname as a constant string; the pathname is the folder path
 *   less trailing path extender; for example:
 *
 *   basename = "/home/share/src/gcc/files/fopen.c"
 *   pathname = "/home/share/src/gcc/file"
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * ofindspec::pathname () const

{
	return (this->mpathname);
}

/*====================================================================*
 *
 *   ofindspec & ofindspec::pathname(char const *string);
 *
 *   assign a new pathname to this object instance after extracting it from
 *   the filespec argument; this allows cut-and-paste from another filename;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ofindspec & ofindspec::pathname (char const * string)

{
	std::strncpy (this->mpathname, string, FILENAME_MAX);
	return (* this);
}

/*====================================================================*
 *
 *   char const *ofindspec::filename() const;
 *
 *   return the basename as a constant string; the basename is the file title
 *   and class less the pathname;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * ofindspec::filename () const

{
	return (this->mfilename);
}

/*====================================================================*
 *
 *   ofindspec & ofindspec::filename(char const *string);
 *
 *   assign a new basename to this object instance after extracting it from
 *   the filespec argument; this allows cut-and-paste from another filename;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ofindspec & ofindspec::filename (char const * string)

{
	std::strncpy (this->mfilename, string, FILENAME_MAX);
	return (* this);
}

/*====================================================================*
 *
 *   char const *ofindspec::basename() const;
 *
 *   return the file class as a constant string; the file class is the
 *   file name without the file extender;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * ofindspec::basename () const

{
	return (this->mbasename);
}

/*====================================================================*
 *
 *   ofindspec & ofindspec::basename(char const *string);
 *
 *   assign a new file title to this object instance; the file title is
 *   extracted from the string argument;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ofindspec & ofindspec::basename (char const * string)

{
	std::strncpy (this->mbasename, string, FILENAME_MAX);
	return (* this);
}

/*====================================================================*
 *
 *   char const *ofindspec::extender() const;
 *
 *   return the file class as a constant string; the file class is the
 *   file extender without the leading file extender;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * ofindspec::extender () const

{
	return (this->mextender);
}

/*====================================================================*
 *
 *   ofindspec & ofindspec::extender(char const *string);
 *
 *   assign a new file class to this object instance; the file class is
 *   extracted from the string argument;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ofindspec & ofindspec::extender (char const * string)

{
	std::strncpy (this->mextender, string, FILENAME_MAX);
	return (* this);
}

/*====================================================================*
 *
 *   char const *ofindspec::longname() const;
 *
 *   return the longname as a constant string; the longname is the fullname
 *   less the file extender; for example:
 *
 *   basename =  "/home/share/src/gcc/files/fopen.c"
 *   longname =  "/home/share/src/gcc/files/fopen"
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * ofindspec::longname () const

{
	std::strncpy (this->mtempname, this->mpathname, FILENAME_MAX);
	if ((* this->mpathname != (char) (0)) && (* this->mbasename != (char) (0)))
	{
		std::strncat (this->mtempname, PATH_S_EXTENDER, FILENAME_MAX);
	}
	std::strncat (this->mtempname, this->mbasename, FILENAME_MAX);
	return (this->mtempname);
}

/*====================================================================*
 *
 *   char const *ofindspec::altbasename(char const *basename);
 *
 *   return the fullname with an alternate basename but do not change the
 *   basename property; if the basename argument is void then return the
 *   pathname; otherwise, append a path extender and the basename argument
 *   to the pathname;
 *
 *   pathname = "/home/share/src"
 *   altbasename(NULL) --> "/home/share/src"
 *   altbasename(NIL) --> "/home/share/src/"
 *   altbasename(".") --> "/home/share/src/."
 *   altbasename("abc.def") --> "/home/share/src/abc.def"
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * ofindspec::altfilename (char const * filename)

{
	std::strncpy (this->mtempname, this->mpathname, FILENAME_MAX);
	if (filename != (char *) (0))
	{
		std::strncat (this->mtempname, PATH_S_EXTENDER, FILENAME_MAX);
		std::strncat (this->mtempname, filename, FILENAME_MAX);
	}
	return (this->mtempname);
}

/*====================================================================*
 *
 *   char const *ofindspec::altextender(char const *extender);
 *
 *   return the fullname with an alternate file extentsion but do not change
 *   the extender property; if the extender argument is void then return the
 *   longname; otherwise, append a file extender and the extender argument to
 *   the longname;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * ofindspec::altextender (char const * extender)

{
	this->longname ();
	if (extender != (char *) (0))
	{
		std::strncat (this->mtempname, FILE_S_EXTENDER, FILENAME_MAX);
		std::strncat (this->mtempname, extender, FILENAME_MAX);
	}
	return (this->mtempname);
}

/*====================================================================*
 *
 *   char const *ofindspec:addextender (char const *extender);
 *
 *   return an extended name as a constant string; an extended name is the
 *   fullname plus an additional file extender;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * ofindspec::addextender (char const * extender)

{
	this->fullname ();
	if (extender != (char *) (0))
	{
		std::strncat (this->mtempname, FILE_S_EXTENDER, FILENAME_MAX);
		std::strncat (this->mtempname, extender, FILENAME_MAX);
	}
	return (this->mtempname);
}

/*====================================================================*
 *
 *   char const *ofindspec::serial (unsigned number, unsigned length);
 *
 *   return a sequence name as a constant string; a sequence name is the
 *   original fullname having an additional 3 digit file extender;
 *
 *--------------------------------------------------------------------*/

char const * ofindspec::serial (unsigned number, unsigned length)

{
	char digits [length + 1];
	for (digits [length] = (char) (0); length > 0; number /=  10)
	{
		digits [-- length] = (char) ('0' + (number % 10));
	}
	this->fullname ();
	std::strncat (this->mtempname, FILE_S_EXTENDER, FILENAME_MAX);
	std::strncat (this->mtempname, digits, FILENAME_MAX);
	return (this->mtempname);
}

/*====================================================================*
 *
 *   void &ofindspec::peek ();
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ofindspec & ofindspec::peek ()

{
	std::cout << "fullname=[" << this->fullname () << "]" << std::endl;
	std::cout << "pathname=[" << this->pathname () << "]" << std::endl;
	std::cout << "filename=[" << this->filename () << "]" << std::endl;
	std::cout << "basename=[" << this->basename () << "]" << std::endl;
	std::cout << "extender=[" << this->extender () << "]" << std::endl;
	std::cout << "longname=[" << this->longname () << "]" << std::endl;
	std::cout << "altextender=[" << this->altextender ("tmp") << "]" << std::endl;
	std::cout << "addextender=[" << this->addextender ("tmp") << "]" << std::endl;
	std::cout << "serial=[" << this->serial (0, 3) << "]" << std::endl;
	std::cout << std::endl;
	return (* this);
}

/*====================================================================*
 *
 *   ofindspec::ofindspec();
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ofindspec::ofindspec (char const * filespec)

{
	this->mfindmode = 0;
	this->mtempname = new char [FILENAME_MAX + 1];
	this->mtempname [0] = (char) (0);
	this->mpathname = new char [FILENAME_MAX + 1];
	this->mpathname [0] = (char) (0);
	this->mfilename = new char [FILENAME_MAX + 1];
	this->mfilename [0] = (char) (0);
	this->mwildcard = new char [FILENAME_MAX + 1];
	this->mwildcard [0] = (char) (0);
	this->mbasename = new char [FILENAME_MAX + 1];
	this->mbasename [0] = (char) (0);
	this->mextender = new char [FILENAME_MAX + 1];
	this->mextender [0] = (char) (0);
	this->fullname (filespec);
	return;
}

/*====================================================================*
 *
 *   ofindspec::ofindspec ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ofindspec::ofindspec ()

{
	this->mfindmode = 0;
	this->mtempname = new char [FILENAME_MAX + 1];
	this->mtempname [0] = (char) (0);
	this->mpathname = new char [FILENAME_MAX + 1];
	this->mpathname [0] = (char) (0);
	this->mfilename = new char [FILENAME_MAX + 1];
	this->mfilename [0] = (char) (0);
	this->mwildcard = new char [FILENAME_MAX + 1];
	this->mwildcard [0] = (char) (0);
	this->mbasename = new char [FILENAME_MAX + 1];
	this->mbasename [0] = (char) (0);
	this->mextender = new char [FILENAME_MAX + 1];
	this->mextender [0] = (char) (0);
	return;
}

/*====================================================================*
 *
 *   ofindspec::~ofindspec ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ofindspec::~ ofindspec ()

{
	delete [] this->mtempname;
	delete [] this->mpathname;
	delete [] this->mfilename;
	delete [] this->mwildcard;
	delete [] this->mbasename;
	delete [] this->mextender;
	return;
}

/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif



