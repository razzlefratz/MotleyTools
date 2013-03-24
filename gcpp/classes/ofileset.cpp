/*====================================================================*
 *
 *   ofileset.cpp - implementation of the ofileset class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oFILESET_SOURCE
#define oFILESET_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstring>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "files.h"
#include "../classes/ofileset.hpp"

/*====================================================================*
 *
 *   unsigned int index() const;
 *
 *   return the fileset index as an unsigned integer; the fileset index
 *   is the file serial number;
 *
 *--------------------------------------------------------------------*/

unsigned int ofileset::index () const 

{
	return (this->mindex);
}


/*====================================================================*
 *
 *   ofileset & index(unsigned index);
 *
 *   assign a new value to the fileset index;
 *
 *--------------------------------------------------------------------*/

ofileset & ofileset::index (unsigned index) 

{
	this->mindex = index;
	return (*this);
}


/*====================================================================*
 *
 *   unsigned int field() const;
 *
 *   return the fileset field property as an unsigned integer; the fileset
 *   field specifies the number of digits comprising a sequence number;
 *
 *--------------------------------------------------------------------*/

unsigned int ofileset::field () const 

{
	return (this->mfield);
}


/*====================================================================*
 *
 *   ofileset & field(unsigned field);
 *
 *   assign a new value to the filesset field property;
 *
 *--------------------------------------------------------------------*/

ofileset & ofileset::field (unsigned field) 

{
	this->mfield = field;
	return (*this);
}


/*====================================================================*
 *
 *   char const *makepath ();
 *
 *   construct the fullname for pathname, filename, index and extender
 *   constituents; 
 *
 *--------------------------------------------------------------------*/

ofileset & ofileset::makepath () 

{
	std::strcpy (this->mfullname, this->mpathname);
	std::strcat (this->mfullname, PATH_S_EXTENDER);
	std::strcat (this->mfullname, this->mbasename);
	char *string = this->mfullname;
	while (*string) 
	{
		string++;
	}
	unsigned int index = this->mindex;
	unsigned int field = this->mfield;
	string [field] = (char) (0);
	while (field > 0) 
	{
		string [--field] = '0' + index % 10;
		index /= 10;
	}
	std::strcat (this->mfullname, FILE_S_EXTENDER);
	std::strcat (this->mfullname, this->mextender);
	return (*this);
}


/*====================================================================*
 *
 *   char const *fullpath (bool increment);
 *
 *   return the fileset pathname after incrementing the fileset index;
 *
 *--------------------------------------------------------------------*/

char const *ofileset::fullpath (bool increment) 

{
	if (increment) 
	{
		this->mindex++;
	}
	return (this->makepath ().fullname ());
}


/*====================================================================*
 *
 *   ofileset & filespec (char const *filespec);
 *
 *   assign a new filespec to this object instance; 
 *
 *--------------------------------------------------------------------*/

ofileset & ofileset::filespec (char const *filespec) 

{
	std::strcpy (this->mfullname, filespec);
	this->mcontext->split (this->mfullname, PATH_C_EXTENDER, false, false);
	this->mpathname = otext::replace (this->mpathname, this->mcontext->prefix ());
	this->mfilename = otext::replace (this->mfilename, this->mcontext->suffix ());
	this->mcontext->split (this->mbasename, FILE_C_EXTENDER, false, true);
	this->mbasename = otext::replace (this->mbasename, mcontext->prefix ());
	this->mextender = otext::replace (this->mextender, mcontext->suffix ());
	return (*this);
}


/*====================================================================*
 *
 *   char const *pathname () const;
 *
 *   return the pathname constituent as a constant string; 
 *
 *--------------------------------------------------------------------*/

char const *ofileset::pathname () const 

{
	return (this->mpathname);
}


/*====================================================================*
 *
 *   ofileset & pathname (char const *filespec);
 *
 *   assign a new pathname to this object instance; take the pathname from
 *   and example filespec;
 *
 *--------------------------------------------------------------------*/

ofileset & ofileset::pathname (char const *filespec) 

{
	ofileset example (filespec);
	this->mpathname = otext::replace (this->mpathname, example.pathname ());
	return (*this);
}


/*====================================================================*
 *
 *   char const *filename () const;
 *
 *   return the filename constituent as a constant string;
 *
 *--------------------------------------------------------------------*/

char const *ofileset::filename () const 

{
	return (this->mfilename);
}


/*====================================================================*
 *
 *   ofileset & filename (char const *filespec);
 *
 *   assign a new filename to this object instance; take the filename from
 *   an example filespec;
 *
 *--------------------------------------------------------------------*/

ofileset & ofileset::filename (char const *filespec) 

{
	ofileset example (filespec);
	this->mfilename = otext::replace (this->mfilename, example.filename ());
	return (*this);
}


/*====================================================================*
 *
 *   char const *basename () const;
 *
 *   return the filename constituent as a constant string; 
 *
 *--------------------------------------------------------------------*/

char const *ofileset::basename () const 

{
	return (this->mbasename);
}


/*====================================================================*
 *
 *   ofileset & basename (char const *filespec);
 *
 *   assign a new basename to this object instance; take the filename from
 *   an example filespec;
 *
 *--------------------------------------------------------------------*/

ofileset & ofileset::basename (char const *filespec) 

{
	ofileset example (filespec);
	this->mbasename = otext::replace (this->mbasename, example.basename ());
	return (*this);
}


/*====================================================================*
 *
 *   char const * extender () const;
 *
 *   return the extender constituent as a constant string;
 *
 *--------------------------------------------------------------------*/

char const *ofileset::extender () const 

{
	return (this->mextender);
}


/*====================================================================*
 *
 *   ofileset & extender (char const *filespec);
 *
 *   assign a new extender to this object instance; take the extender from
 *   an example filespec;
 *
 *--------------------------------------------------------------------*/

ofileset & ofileset::extender (char const *filespec) 

{
	ofileset example (filespec);
	this->mextender = otext::replace (this->mextender, example.extender ());
	return (*this);
}


/*====================================================================*
 *
 *   ofileset(char const *filespec);
 *
 *
 *
 *--------------------------------------------------------------------*/

ofileset::ofileset (char const *filespec) 

{
	this->mfullname = new char [FILENAME_MAX+1];
	std::strcpy (this->mfullname, filespec);
	this->mcontext->split (this->mfullname, PATH_C_EXTENDER, false, false);
	this->mpathname = otext::replace (this->mpathname, this->mcontext->prefix ());
	this->mfilename = otext::replace (this->mfilename, this->mcontext->suffix ());
	this->mcontext->split (this->mfilename, FILE_C_EXTENDER, false, true);
	this->mbasename = otext::replace (this->mbasename, mcontext->prefix ());
	this->mextender = otext::replace (this->mextender, mcontext->suffix ());
	this->mindex = 0;
	this->mfield = 3;
	return;
}


/*====================================================================*
 *
 *   ofileset (char const *filespec);
 *
 *
 *
 *--------------------------------------------------------------------*/

ofileset::ofileset () 

{
	this->mcontext = new ocontext;
	this->mfullname = new char [FILENAME_MAX+1];
	std::strcpy (this->mfullname, "temp.txt");
	this->mcontext->split (this->mfullname, PATH_C_EXTENDER, false, true);
	this->mpathname = otext::replace (this->mpathname, this->mcontext->prefix ());
	this->mfilename = otext::replace (this->mfilename, this->mcontext->suffix ());
	this->mcontext->split (this->mfilename, FILE_C_EXTENDER, false, false);
	this->mbasename = otext::replace (this->mbasename, mcontext->prefix ());
	this->mextender = otext::replace (this->mbasename, mcontext->suffix ());
	this->mindex = 0;
	this->mfield = 3;
	return;
}


/*====================================================================*
 *
 *   ~ofileset (char const *filespec);
 *
 *
 *
 *--------------------------------------------------------------------*/

ofileset::~ofileset () 

{
	delete this->mcontext;
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

