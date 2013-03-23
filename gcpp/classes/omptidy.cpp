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
 *--------------------------------------------------------------------*/

char const * omptidy::program () const 

{
	return (this->mprogram);
}

omptidy & omptidy::program (char const * program) 

{
	this->mprogram = omptidy::replace (this->mprogram, program);
	return (*this);
}

/*====================================================================*
 *   
 *   char const * project () const;
 *   
 *   get and set the project comment string;
 *   
 *--------------------------------------------------------------------*/

char const * omptidy::project () const 

{
	return (this->mproject);
}

omptidy & omptidy::project (char const * project) 

{
	this->mproject = omptidy::replace (this->mproject, project);
	return (*this);
}

/*====================================================================*
 *   
 *   char const * package () const;
 *   
 *   get and set the package comment string;
 *   
 *--------------------------------------------------------------------*/

char const * omptidy::package () const 

{
	return (this->mpackage);
}

omptidy & omptidy::package (char const * package) 

{
	this->mpackage = omptidy::replace (this->mpackage, package);
	return (*this);
}

/*====================================================================*
 *   
 *   char const * release () const;
 *   
 *   get and set the release comment string;
 *   
 *--------------------------------------------------------------------*/

char const * omptidy::release () const 

{
	return (this->mrelease);
}

omptidy & omptidy::release (char const * release) 

{
	this->mrelease = omptidy::replace (this->mrelease, release);
	return (*this);
}

/*====================================================================*
 *
 *   signed omptidy::page (signed c);
 *
 *   search for PHP source; ignore asp source; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed omptidy::page (signed c) 

{
	while (c != EOF) 
	{
		while ((c == '\r') || (c == '\n')) 
		{
			c = std::cin.get ();
		}
		if (c == '.') 
		{
			char symbol [SYMBOLSIZE];
			char * sp = symbol;
			do 
			{
				*sp++ = c;
				c = std::cin.get ();
			}
			while (oascii::isalpha (c));
			*sp = (char) (0);
			if (!std::strcmp (symbol, ".TH")) 
			{
				while (oascii::nobreak (c)) 
				{
					c = std::cin.get ();
				}
				sp += std::snprintf (sp, sizeof (symbol) + sp - symbol, " %s", program);
				sp += std::snprintf (sp, sizeof (symbol) + sp - symbol, " \"%s\"", release);
				sp += std::snprintf (sp, sizeof (symbol) + sp - symbol, " \"%s\"", package);
				sp += snprintf (sp, sizeof (symbol) + sp - symbol, " \"%s\"", project);
			}
			else if (!std::strcmp (symbol, ".SH")) 
			{
				std::cout.put ('\n');
			}
			else if (!std::strcmp (symbol, ".TP")) 
			{
				std::cout.put ('\n');
			}
			else if (!std::strcmp (symbol, ".PP")) 
			{
				std::cout.put ('\n');
			}
			std::sout.put (symbol);
		}
		while (oascii::nobreak (c)) 
		{
			if (oascii::isquote (c)) 
			{
				c = ocollect::literal (c, c);
				continue;
			}
			if (c == '[') 
			{
				c = ocollect::literal (c, ']');
				continue;
			}
			if (c == '.') 
			{
				c = ocollect::keep (c);
				if (oascii::isblank (c)) 
				{
					do 
					{
						c = std::cin.get ();
					}
					while (oascii::isblank (c));
					std::cout.put ('\n');
				}
				continue;
			}
			c = ocollect::keep (c);
		}
		c = ocollect::keep (c);
	}
	return;
}


/*====================================================================*
 *
 *   signed find (signed c);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed omptidy::find (signed c) 

{
	while (oascii::isspace (c)) 
	{
		c = std::cin.get ();
	}
	return (c);
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
	delete [] this->mbuffer;
	return;
}


/*====================================================================*
 *   end definition
 *--------------------------------------------------------------------*/

#endif

