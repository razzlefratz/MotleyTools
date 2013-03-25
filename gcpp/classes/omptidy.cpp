/*====================================================================*
 *
 *   omptidy.cpp - definition of omptidy class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oMPTIDY_SOURCE
#define oMPTIDY_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cerrno>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oascii.hpp"
#include "../classes/omptidy.hpp"

/*====================================================================*
 *   
 *   char const * program () const;
 *   
 *   get and set the program comment string;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * omptidy::program () const 

{
	return (this->mprogram);
}

omptidy & omptidy::program (char const * program) 

{
	this->mprogram = otext::replace (this->mprogram, program);
	return (*this);
}


/*====================================================================*
 *   
 *   char const * project () const;
 *   
 *   get and set the project comment string;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * omptidy::project () const 

{
	return (this->mproject);
}

omptidy & omptidy::project (char const * project) 

{
	this->mproject = otext::replace (this->mproject, project);
	return (*this);
}


/*====================================================================*
 *   
 *   char const * package () const;
 *   
 *   get and set the package comment string;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * omptidy::package () const 

{
	return (this->mpackage);
}

omptidy & omptidy::package (char const * package) 

{
	this->mpackage = otext::replace (this->mpackage, package);
	return (*this);
}


/*====================================================================*
 *   
 *   char const * release () const;
 *   
 *   get and set the release comment string;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * omptidy::release () const 

{
	return (this->mrelease);
}

omptidy & omptidy::release (char const * release) 

{
	this->mrelease = otext::replace (this->mrelease, release);
	return (*this);
}


/*====================================================================*
 *
 *   omptidy & filename (char const * filename);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

omptidy & omptidy::filename (char const * filename) 

{
	char const * basename;
	for (basename = filename; * filename; filename++) 
	{
		if ((* filename == '\\') || (* filename == '/')) 
		{
			basename = filename + 1;
		}
	}
	this->mprogram = otext::replace (this->mprogram, basename);
	for (filename = basename; * filename; filename++) 
	{
		if (* filename == '.') 
		{
			this->mprogram [filename - basename] = ' ';
		}
	}
	return (*this);
}


/*====================================================================*
 *
 *   omptidy & omptidy::tidy ();
 *
 *   tidy man page source file;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

omptidy & omptidy::tidy () 

{
	signed c = std::cin.get ();
	while (c != EOF) 
	{
		while ((c == '\r') || (c == '\n')) 
		{
			c = std::cin.get ();
		}
		if (c == '.') 
		{
			char * sp = this->mstring;
			do 
			{
				*sp++ = c;
				c = std::cin.get ();
			}
			while (oascii::isalpha (c));
			*sp = (char) (0);
			if (!std::strcmp (this->mstring, ".TH")) 
			{
				while (oascii::nobreak (c)) 
				{
					c = std::cin.get ();
				}
				std::cout << this->mstring;
				std::cout << " " << this->mprogram;
				std::cout << " \"" << this->mrelease << "\"";
				std::cout << " \"" << this->mpackage << "\"";
				std::cout << " \"" << this->mproject << "\"";
			}
			else 
			{
				if (!std::strcmp (this->mstring, ".SH")) 
				{
					std::cout << std::endl;
				}
				else if (!std::strcmp (this->mstring, ".TP")) 
				{
					std::cout << std::endl;
				}
				else if (!std::strcmp (this->mstring, ".PP")) 
				{
					std::cout << std::endl;
				}
				std::cout << this->mstring;
			}
		}
		while (oascii::nobreak (c)) 
		{
			if (c == '.') 
			{
				c = ocollect::keep (c);
				if (c == '.')
				{
					do { c = ocollect::keep (c); } while (c == '.');
					continue;
				}
				if (oascii::isblank (c)) 
				{
					do { c = std::cin.get (); } while (oascii::isblank (c));
					std::cout.put ('\n');
					continue;
				}
				continue;
			}
			if (oascii::isquote (c)) 
			{
				c = ocollect::literal (c, c);
				continue;
			}
			c = ocollect::keep (c);
		}
		c = ocollect::keep (c);
	}
	return (*this);
}


/*====================================================================*
 *
 *   omptidy()
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

omptidy::omptidy () 

{
	this->mproject = new char [1];
	this->mproject [0] = (char)(0);
	this->mprogram = new char [1];
	this->mprogram [0] = (char)(0);
	this->mpackage = new char [1];
	this->mpackage [0] = (char)(0);
	this->mrelease = new char [1];
	this->mrelease [0] = (char)(0);
	this->mstring = new char [oMPTIDY_SYMBOLSIZE];
	this->mstring [0] = (char)(0);
	return;
}


/*====================================================================*
 *
 *   ~omptidy()
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

omptidy::~omptidy () 

{
	delete [] this->mproject;
	delete [] this->mprogram;
	delete [] this->mpackage;
	delete [] this->mrelease;
	delete [] this->mstring;
	return;
}


/*====================================================================*
 *   end definition
 *--------------------------------------------------------------------*/

#endif

