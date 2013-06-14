/*====================================================================*
 *
 *   othis->filespec.cpp - implementation of the opackage class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oPACKAGE_SOURCE
#define oPACKAGE_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstdlib>
#include <cstring>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/opackage.hpp"

/*====================================================================*
 *   class variables;
 *--------------------------------------------------------------------*/

char const * opackage::extenders [oPACKAGE_EXTENDERS_MAX+1] = 

{
	".tar",
	".tgz",
	".tar.gz",
	".tar.bz2",
	".md5sum",
	".hlp",
	".log",
	(char const *) (0)
};


/*====================================================================*
 *
 *   char const *archive () const;
 *
 *   return archive basename; the basename is the filename less the pathname,
 *   release and extention;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * opackage::archive () const 

{
	return ((char const *) (this->marchive));
}


/*====================================================================*
 *
 *   char const *package () const;
 *
 *   return release substring; the release is the filename less the
 *   trailer; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * opackage::package () const 

{
	return ((char const *) (this->mproduct));
}


/*====================================================================*
 *
 *   char const *product () const;
 *
 *   return package basename; the basename is the filename less the pathname,
 *   release and extention;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * opackage::product () const 

{
	return ((char const *) (this->mproduct));
}


/*====================================================================*
 *
 *   char const *release () const;
 *
 *   return package basename; the basename is the filename less the pathname,
 *   release and extention;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * opackage::release () const 

{
	return ((char const *) (this->mrelease));
}


/*====================================================================*
 *
 *   char const *trailer () const;
 *
 *   return package basename; the basename is the filename less the pathname,
 *   release and extention;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * opackage::trailer () const 

{
	return ((char const *) (this->mtrailer));
}


/*====================================================================*
 *
 *   opackage & operator= (char const *filespec);
 *
 *   separate filespec into pathname and filename constituents then separate 
 *   filename into basename and extender constituents; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

opackage & opackage::operator= (char const * filespec) 

{
	this->filespec (filespec);
	return (* this);
}


/*====================================================================*
 *
 *   opackage & filespec (char const *filespec);
 *
 *   separate filespec into pathname and filename constituents then separate 
 *   filename into basename and extender constituents; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

opackage & opackage::filespec (char const * string) 

{
	char const * package;
	char const * release;
	char const * trailer;
	for (package = release = trailer = string; * string != (char) (0); string++) 
	{
		if (* string == '/') 
		{
			package = string+1;
			release = string+1;
			trailer = string+1;
			continue;
		}
		if (* string == '-') 
		{
			release = string;
			trailer = string;
			continue;
		}
		if (* string == '.') 
		{
			trailer = string;
			for (char const ** extender = extenders; * extender != (char const *) (0); extender++) 
			{
				if (!std::strcmp (string, * extender)) 
				{
					while (*++string != (char) (0));
					break;
				}
			}
			if (* string == (char) (0)) 
			{
				break;
			}
		}
	}
	if ((package < release) && (release < trailer)) 
	{
		this->marchive = opackage::extract (marchive, package, string);
		this->mpackage = opackage::extract (mpackage, package, trailer);
		this->mproduct = opackage::extract (mproduct, package, release++);
		this->mrelease = opackage::extract (mrelease, release, trailer++);
		this->mtrailer = opackage::extract (mtrailer, trailer, string);
	}
	return (* this);
}


/*====================================================================*
 *
 *   opackage & extender (char const *string);
 *
 *   add another extender to the extenders list if space allows;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

opackage & opackage::extender (char const * string) 

{
	char const ** extender = opackage::extenders;
	while (* extender != (char const *) (0)) 
	{
		extender++;
	}
	if ((extender - opackage::extenders) < oPACKAGE_EXTENDERS_MAX) 
	{
		* extender++ = string;
		* extender = (char const *) (0);
	}
	return (* this);
}


/*====================================================================*
 *
 *   char * extract(char *string, char const *first, char const *limit)
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char * opackage::extract (char string [], char const * start, char const * limit) 

{
	delete [] string;
	string = new char [limit - start + 1];
	std::memcpy (string, start, limit - start);
	string [limit - start] = (char) (0);
	return (string);
}


/*====================================================================*
 *
 *   void &peek ();
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

opackage & opackage::peek () 

{
	std::cout << "archive=[" << this->marchive << "]" << std::endl;
	std::cout << "package=[" << this->mpackage << "]" << std::endl;
	std::cout << "product=[" << this->mproduct << "]" << std::endl;
	std::cout << "release=[" << this->mrelease << "]" << std::endl;
	std::cout << "trailer=[" << this->mtrailer << "]" << std::endl;
	std::cout << std::endl;
	return (* this);
}


/*====================================================================*
 *
 *   opackage();
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

opackage::opackage () 

{
	this->marchive = new char [1];
	this->mpackage = new char [1];
	this->mproduct = new char [1];
	this->mrelease = new char [1];
	this->mtrailer = new char [1];
	this->marchive [0] = (char) (0);
	this->mpackage [0] = (char) (0);
	this->mproduct [0] = (char) (0);
	this->mrelease [0] = (char) (0);
	this->mtrailer [0] = (char) (0);
	return;
}


/*====================================================================*
 *
 *   opackage(char const *filespec);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

opackage::opackage (char const * filespec) 

{
	this->marchive = new char [1];
	this->mpackage = new char [1];
	this->mproduct = new char [1];
	this->mrelease = new char [1];
	this->mtrailer = new char [1];
	this->marchive [0] = (char) (0);
	this->mpackage [0] = (char) (0);
	this->mproduct [0] = (char) (0);
	this->mrelease [0] = (char) (0);
	this->mtrailer [0] = (char) (0);
	this->filespec (filespec);
	return;
}


/*====================================================================*
 *
 *   ~ opackage();
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

opackage::~opackage () 

{
	delete [] this->marchive;
	delete [] this->mpackage;
	delete [] this->mproduct;
	delete [] this->mrelease;
	delete [] this->mtrailer;
	return;
}


/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif

