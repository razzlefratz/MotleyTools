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
 *   char const * program (void) const;
 *   
 *   get and set the program comment string;
 *   
 *--------------------------------------------------------------------*/

char const * omptidy::program (void) const

{
	return (this->mprogram);
}

omptidy & omptidy::program (char const * program)

{
	this->mprogram = otext::replace (this->mprogram, program);
	return (* this);
}

/*====================================================================*
 *   
 *   char const * project (void) const;
 *   
 *   get and set the project comment string;
 *   
 *--------------------------------------------------------------------*/

char const * omptidy::project (void) const

{
	return (this->mproject);
}

omptidy & omptidy::project (char const * project)

{
	this->mproject = otext::replace (this->mproject, project);
	return (* this);
}

/*====================================================================*
 *   
 *   char const * package (void) const;
 *   
 *   get and set the package comment string;
 *   
 *--------------------------------------------------------------------*/

char const * omptidy::package (void) const

{
	return (this->mpackage);
}

omptidy & omptidy::package (char const * package)

{
	this->mpackage = otext::replace (this->mpackage, package);
	return (* this);
}

/*====================================================================*
 *   
 *   char const * release (void) const;
 *   
 *   get and set the release comment string;
 *   
 *--------------------------------------------------------------------*/

char const * omptidy::release (void) const

{
	return (this->mrelease);
}

omptidy & omptidy::release (char const * release)

{
	this->mrelease = otext::replace (this->mrelease, release);
	return (* this);
}

/*====================================================================*
 *
 *   omptidy & filename (char const * filename);
 *
 *--------------------------------------------------------------------*/

omptidy & omptidy::filename (char const * filename)

{
	char const * basename;
	for (basename = filename; * filename; filename++)
	{
		if ((* filename == '\\') || (* filename == '/'))
		{
			basename = filename +  1;
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
	return (* this);
}

/*====================================================================*
 *
 *   signed omptidy::tidy (signed c);
 *
 *   tidy man page source file;
 *
 *--------------------------------------------------------------------*/

signed omptidy::tidy (signed c)

{
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
				* sp++ = c;
				c = std::cin.get ();
			}
			while (oascii::isalpha (c));
			* sp = (char) (0);
			if (! std::strcmp (this->mstring, ".TH"))
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
			else if (! std::strcmp (this->mstring, ".SH"))
			{
				std::cout << std::endl << this->mstring;
			}
			else if (! std::strcmp (this->mstring, ".SS"))
			{
				std::cout << std::endl << this->mstring;
			}
			else if (! std::strcmp (this->mstring, ".TP"))
			{
				std::cout << std::endl << this->mstring;
			}
			else if (! std::strcmp (this->mstring, ".HP"))
			{
				std::cout << std::endl << this->mstring;
			}
			else if (! std::strcmp (this->mstring, ".IP"))
			{
				std::cout << std::endl << this->mstring;
			}
			else if (! std::strcmp (this->mstring, ".PP"))
			{
				std::cout << std::endl << this->mstring;
			}
			else if (! std::strcmp (this->mstring, ".P"))
			{
				std::cout << std::endl << this->mstring;
			}
			else 
			{
				std::cout << this->mstring;
			}
		}
		while (oascii::nobreak (c))
		{
			if (oascii::isquote (c))
			{
				c = omptidy::literal (c, c);
				continue;
			}
			if (c == '.')
			{
				c = omptidy::keep (c);
				if (c == '.')
				{
					do 
					{
						c = omptidy::keep (c);
					}
					while (c == '.');
					continue;
				}
				if (oascii::isblank (c))
				{
					do 
					{
						c = std::cin.get ();
					}
					while (oascii::isblank (c));
					std::cout.put ('\n');
					continue;
				}
				continue;
			}

#if 1

			if (c == '\\')
			{
				c = omptidy::keep (c);
				if (c == 'v')
				{
					c = 'f';
				}
				c = omptidy::keep (c);
				continue;
			}

#endif

			c = omptidy::keep (c);
		}
		c = omptidy::keep (c);
	}
	std::cout.put ('\n');
	return (c);
}

/*====================================================================*
 *
 *   omptidy & example (void);
 *
 *   print a skeleton manpage template on stdout;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

omptidy & omptidy::example (void)

{
	char const * subjects [] = 
	{
		"NAME",
		"SYNTAX",
		"SYNOPSIS",
		"AVAILABILITY",
		"DESCRIPTION",
		"OPTIONS",
		"EXAMPLES",
		"NOTES",
		"MESSAGES",
		"HISTORY",
		"RESOURCES",
		"FILES",
		"BUGS",
		"CAVEATS",
		"AUTHORS",
		"CREDITS",
		"SEE ALSO",
		(char const *) (0)
	};
	char const ** subject = subjects;
	std::cout << ".TH program 1 package" << std::endl;
	while (* subject)
	{
		std::cout << std::endl << ".SH " << * subject++ << std::endl;
	}
	std::cout << std::endl;
	return (* this);
}

/*====================================================================*
 *
 *   omptidy (void)
 *
 *--------------------------------------------------------------------*/

omptidy::omptidy (void)

{
	this->mproject = new char [1];
	this->mproject [0] = (char) (0);
	this->mprogram = new char [1];
	this->mprogram [0] = (char) (0);
	this->mpackage = new char [1];
	this->mpackage [0] = (char) (0);
	this->mrelease = new char [1];
	this->mrelease [0] = (char) (0);
	this->mstring = new char [oMPTIDY_SYMBOLSIZE];
	this->mstring [0] = (char) (0);
	return;
}

/*====================================================================*
 *
 *   ~omptidy(void)
 *
 *--------------------------------------------------------------------*/

omptidy::~ omptidy (void)

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



