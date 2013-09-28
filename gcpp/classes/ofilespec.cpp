/*====================================================================*
 *
 *   othis->filespec.cpp - implementation of the ofilespec class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oFILESPEC_SOURCE
#define oFILESPEC_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstdlib>
#include <cstring>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ofilespec.hpp"
#include "../../gcc/files/files.h"

/*====================================================================*
 *   class variables;
 *--------------------------------------------------------------------*/

ofilespec ofilespec::scratch;

/*====================================================================*
 *
 *   char const *fullpath ();
 *
 *   compile the fullname from the pathname and filename constituents and
 *   return it as a constant string;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * ofilespec::fullpath ()

{
	return (this->makepath ().fullname ());
}

/*====================================================================*
 *
 *   char const *makepath ();
 *
 *   compile the fullname from the pathname and filename constituents and
 *   return the object address;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ofilespec & ofilespec::makepath ()

{
	this->filename ();
	std::strcpy (this->mfullname, this->mpathname);
	if ((* this->mpathname != (char) (0)) && (* this->mfilename != (char) (0)))
	{
		std::strcat (this->mfullname, PATH_S_EXTENDER);
	}
	std::strcat (this->mfullname, this->mfilename);
	return (* this);
}

/*====================================================================*
 *
 *   ofilespec & operator= (char const *filespec);
 *
 *   separate filespec into pathname and filename constituents then separate
 *   filename into basename and extender constituents;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ofilespec & ofilespec::operator = (char const * filespec)

{
	this->filespec (filespec);
	return (* this);
}

/*====================================================================*
 *
 *   ofilespec & filespec (char const *filespec);
 *
 *   separate filespec into pathname and filename constituents then separate
 *   filename into basename and extender constituents;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ofilespec & ofilespec::filespec (char const * filespec)

{
	this->split (filespec, PATH_C_EXTENDER, false, false);
	this->prefix (this->mpathname, FILENAME_MAX);
	this->suffix (this->mfilename, FILENAME_MAX);
	this->split ((char const *) (this->mfilename), FILE_C_EXTENDER, false, true);
	this->prefix (this->mbasename, FILENAME_MAX);
	this->suffix (this->mextender, FILENAME_MAX);
	this->makepath ();
	return (* this);
}

/*====================================================================*
 *
 *   char const *fullname() const;
 *
 *   return the fullname composite as a constant string;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * ofilespec::fullname () const

{
	return (this->mfullname);
}

/*====================================================================*
 *
 *   char const *pathname() const;
 *
 *   return the pathname constituent as a constant string;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * ofilespec::pathname () const

{
	return (this->mpathname);
}

/*====================================================================*
 *
 *   ofilespec & pathname (char const *filespec);
 *
 *   replace the pathname constituent with one from another filespec;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ofilespec & ofilespec::pathname (char const * filespec)

{
	std::strcpy (this->mpathname, ofilespec::scratch.filespec (filespec).pathname ());
	return (this->makepath ());
}

/*====================================================================*
 *
 *   char const *filename() const;
 *
 *   compile the filename from the basename and extender constituents and
 *   return it as a constant string;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * ofilespec::filename () const

{
	std::strcpy (this->mfilename, this->mbasename);
	if ((* this->mbasename != (char) (0)) && (* this->mextender != (char) (0)))
	{
		std::strcat (this->mfilename, FILE_S_EXTENDER);
	}
	std::strcat (this->mfilename, this->mextender);
	return (this->mfilename);
}

/*====================================================================*
 *
 *   ofilespec & filename(char const *filespec);
 *
 *   replace the filename constituent with one from another filespec;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ofilespec & ofilespec::filename (char const * filespec)

{
	std::strcpy (this->mfilename, ofilespec::scratch.filespec (filespec).filename ());
	this->split ((char const *) (this->mfilename), FILE_C_EXTENDER, false, true);
	this->prefix (this->mbasename, FILENAME_MAX);
	this->suffix (this->mextender, FILENAME_MAX);
	return (this->makepath ());
}

/*====================================================================*
 *
 *   char const *basename() const;
 *
 *   return the basename constituent as a constant string;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * ofilespec::basename () const

{
	return (this->mbasename);
}

/*====================================================================*
 *
 *   ofilespec & basename(char const *filespec);
 *
 *   replace the basename constituent with one from another filespec;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ofilespec & ofilespec::basename (char const * filespec)

{
	std::strcpy (this->mbasename, ofilespec::scratch.filespec (filespec).basename ());
	return (this->makepath ());
}

/*====================================================================*
 *
 *   char const *extender() const;
 *
 *   return the extender constituent as a constant string;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * ofilespec::extender () const

{
	return (this->mextender);
}

/*====================================================================*
 *
 *   ofilespec & extender(char const *filespec);
 *
 *   replace the extender constituent with one from another filespec;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ofilespec & ofilespec::extender (char const * filespec)

{
	std::strcpy (this->mextender, ofilespec::scratch.filespec (filespec).extender ());
	return (this->makepath ());
}

/*====================================================================*
 *
 *   char const *longname() const;
 *
 *   return the longname as a constant string; the longname is the fullname
 *   less the file extender; for example:
 *
 *   fullname =  "/home/share/src/gcc/files/fopen.c"
 *   longname =  "/home/share/src/gcc/files/fopen"
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * ofilespec::longname () const

{
	std::strcpy (this->mfullname, this->mpathname);
	if ((* this->mpathname != (char) (0)) && (* this->mbasename != (char) (0)))
	{
		std::strcat (this->mfullname, PATH_S_EXTENDER);
	}
	std::strcat (this->mfullname, this->mbasename);
	return (this->mfullname);
}

/*====================================================================*
 *
 *   char const *tempname (char const *filename);
 *
 *   return the fullname with an alternate basename but do not change the
 *   basename property; if the basename argument is void then return the
 *   pathname; otherwise, append a path extender and the basename argument
 *   to the pathname;
 *
 *   pathname = "/home/share/src"
 *   tempfilename(NULL) --> "/home/share/src"
 *   tempfilename("") --> "/home/share/src/"
 *   tempfilename(".") --> "/home/share/src/."
 *   tempfilename("abc.def") --> "/home/share/src/abc.def"
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * ofilespec::tempname (char const * filespec)

{
	std::strcpy (this->mfullname, this->mpathname);
	if ((* this->mpathname != (char) (0)) && (filespec != (char *) (0)))
	{
		std::strcat (this->mfullname, PATH_S_EXTENDER);
	}
	std::strcat (this->mfullname, ofilespec::scratch.filespec (filespec).filename ());
	return (this->mfullname);
}

/*====================================================================*
 *
 *   char const *likename(char const *extender);
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

char const * ofilespec::likename (char const * filespec)

{
	this->longname ();
	if (filespec != (char *) (0))
	{
		std::strcat (this->mfullname, FILE_S_EXTENDER);
		std::strcat (this->mfullname, ofilespec::scratch.filespec (filespec).extender ());
	}
	return (this->mfullname);
}

/*====================================================================*
 *
 *   char const *savename (char const *filespec);
 *
 *   return an extended name as a constant string; an extended name is the
 *   fullname plus an additional file extender;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * ofilespec::savename (char const * filespec)

{
	this->makepath ();
	if (filespec != (char *) (0))
	{
		std::strcat (this->mfullname, FILE_S_EXTENDER);
		std::strcat (this->mfullname, ofilespec::scratch.filespec (filespec).extender ());
	}
	return (this->mfullname);
}

/*====================================================================*
 *
 *   char const *savename (unsigned number, unsigned length);
 *
 *   return a sequence name as a constant string; a sequence name is the
 *   fullname plus an additional numeric file extender;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * ofilespec::savename (unsigned number, unsigned length)

{
	char digits [length +  1];
	for (digits [length] = (char) (0); length > 0; number /= 10)
	{
		digits [-- length] = (char) ('0' +  (number % 10));
	}
	this->makepath ();
	std::strcat (this->mfullname, FILE_S_EXTENDER);
	std::strcat (this->mfullname, digits);
	return (this->mfullname);
}

/*====================================================================*
 *
 *   void &peek ();
 *
 *   print the state of internal strings on stdout;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ofilespec & ofilespec::peek ()

{
	std::cout << "fullpath=[" << this->fullpath () << "]" << std::endl;
	std::cout << "pathname=[" << this->pathname () << "]" << std::endl;
	std::cout << "filename=[" << this->filename () << "]" << std::endl;
	std::cout << "basename=[" << this->basename () << "]" << std::endl;
	std::cout << "extender=[" << this->extender () << "]" << std::endl;
	std::cout << "longname=[" << this->longname () << "]" << std::endl;
	std::cout << "tempname=[" << this->tempname ("/home/abc.new") << "]" << std::endl;
	std::cout << "likename=[" << this->likename ("/home/abc.new") << "]" << std::endl;
	std::cout << "savename=[" << this->savename ("/home/abc.new") << "]" << std::endl;
	std::cout << "savename=[" << this->savename (5, 3) << "]" << std::endl;
	std::cout << std::endl;
	return (* this);
}

/*====================================================================*
 *
 *   ofilespec();
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ofilespec::ofilespec ()

{
	this->mfullname = new char [FILENAME_MAX +  1];
	this->mpathname = new char [FILENAME_MAX +  1];
	this->mfilename = new char [FILENAME_MAX +  1];
	this->mbasename = new char [FILENAME_MAX +  1];
	this->mextender = new char [FILENAME_MAX +  1];
	return;
}

/*====================================================================*
 *
 *   ofilespec(char const *filespec);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ofilespec::ofilespec (char const * filespec)

{
	this->mfullname = new char [FILENAME_MAX +  1];
	this->mpathname = new char [FILENAME_MAX +  1];
	this->mfilename = new char [FILENAME_MAX +  1];
	this->mbasename = new char [FILENAME_MAX +  1];
	this->mextender = new char [FILENAME_MAX +  1];
	this->filespec (filespec);
	return;
}

/*====================================================================*
 *
 *   ~ofilespec();
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ofilespec::~ ofilespec ()

{
	delete [] this->mfullname;
	delete [] this->mpathname;
	delete [] this->mfilename;
	delete [] this->mbasename;
	delete [] this->mextender;
	return;
}

/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif



