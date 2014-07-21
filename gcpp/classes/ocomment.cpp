/*====================================================================*
 *
 *   ocomment.cpp - definition of ocomment class.
 *
 *.  Motley Tools by Charles Maier <cmaier@cmassoc.net>;
 *:  Copyright 2001-2006 by Charles Maier Associates;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCOMMENT_SOURCE
#define oCOMMENT_SOURCE

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

#include "../classes/ocomment.hpp"
#include "../classes/oascii.hpp"

/*====================================================================*
 *
 *   unsigned width (void) const;
 *
 *   get and set the comment bar width;
 *
 *--------------------------------------------------------------------*/

unsigned ocomment::width (void) const

{
	return (this->mwidth);
}

ocomment & ocomment::width (unsigned width)

{
	this->mwidth = width;
	return (* this);
}

/*====================================================================*
 *
 *   unsigned char cupper (void) const;
 *
 *   get and set the upper bar character;
 *
 *--------------------------------------------------------------------*/

unsigned char ocomment::cupper (void) const

{
	return (this->mupper);
}

ocomment & ocomment::cupper (unsigned char upper)

{
	this->mupper = upper;
	return (* this);
}

/*====================================================================*
 *
 *   unsigned char clower (void) const;
 *
 *   get and set the lower bar character;
 *
 *--------------------------------------------------------------------*/

unsigned char ocomment::clower (void) const

{
	return (this->mlower);
}

ocomment & ocomment::clower (unsigned char lower)

{
	this->mlower = lower;
	return (* this);
}

/*====================================================================*
 *
 *   char const * preface (void) const;
 *
 *   get and set the preface comment string;
 *
 *--------------------------------------------------------------------*/

char const * ocomment::preface (void) const

{
	return (this->mpreface);
}

ocomment & ocomment::preface (char const * preface)

{
	this->mpreface = otext::replace (this->mpreface, preface);
	return (* this);
}

/*====================================================================*
 *
 *   char const * package (void) const;
 *
 *   get and set the package comment string;
 *
 *--------------------------------------------------------------------*/

char const * ocomment::package (void) const

{
	return (this->mpackage);
}

ocomment & ocomment::package (char const * package)

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

char const * ocomment::release (void) const

{
	return (this->mrelease);
}

ocomment & ocomment::release (char const * release)

{
	this->mrelease = otext::replace (this->mrelease, release);
	return (* this);
}

/*====================================================================*
 *
 *   char const * license (void) const;
 *
 *   get and set the license comment string;
 *
 *--------------------------------------------------------------------*/

char const * ocomment::license (void) const

{
	return (this->mlicense);
}

ocomment & ocomment::license (char const * license)

{
	this->mlicense = otext::replace (this->mlicense, license);
	return (* this);
}

/*====================================================================*
 *
 *   char const * special (void) const;
 *
 *   get and set the special comment string;
 *
 *--------------------------------------------------------------------*/

char const * ocomment::special (void) const

{
	return (this->mspecial);
}

ocomment & ocomment::special (char const * special)

{
	this->mspecial = otext::replace (this->mspecial, special);
	return (* this);
}

/*====================================================================*
 *
 *   ocomment & ocomment::preamble (void);
 *
 *   insert an empty preamble comment block;
 *
 *--------------------------------------------------------------------*/

ocomment & ocomment::preamble (void)

{
	std::cout << "/*===*" << std::endl;
	std::cout << " *" << std::endl;
	std::cout << " *" << std::endl;
	std::cout << " *" << std::endl;

#if 0

	std::cout << " *.   " << std::endl;
	std::cout << " *:   " << std::endl;
	std::cout << " *;   " << std::endl;

#endif

	std::cout << " *" << std::endl;
	std::cout << " *---*/" << std::endl;
	return (* this);
}

/*====================================================================*
 *
 *   signed ocomment::preamble (signed c)
 *
 *   insert an empty preamble comment block;
 *
 *--------------------------------------------------------------------*/

signed ocomment::preamble (signed c)

{
	if (ocomment::anyset (oCOMMENT_B_COMMENT))
	{
		while (c != EOF)
		{
			if (c == '/')
			{
				c = ocomment::comment (c);
				continue;
			}
			if (c == ';')
			{
				std::cout.put (c);
				c = std::cin.get ();
				continue;
			}
			if (oascii::isspace (c))
			{
				c = std::cin.get ();
				continue;
			}
			ocomment::preamble ();
			break;
		}
	}
	return (c);
}

/*====================================================================*
 *
 *   signed comment (signed c) const;
 *
 *   read and write comment blocks;
 *
 *--------------------------------------------------------------------*/

signed ocomment::comment (signed c)

{
	c = std::cin.get ();
	if (c == '/')
	{
		c = ocomment::cplus (c);
		return (c);
	}
	if (c == '*')
	{
		c = ocomment::clang (c);
		return (c);
	}
	std::cout.put ('/');
	return (c);
}

/*====================================================================*
 *
 *   signed cplus (signed c);
 *
 *   format C++ style comments and return the character after;
 *
 *   read and discard excess leading slashes and empty comment lines;
 *
 *   under normal conditions, output two slashes then read and write
 *   characters until newline or EOF; discard the newline;
 *
 *   if oCOMMENT_B_TRIPLE is set then convert C++ comment to a multi-line
 *   C-style comment;
 *
 *--------------------------------------------------------------------*/

signed ocomment::cplus (signed c)

{
	while (c == '/')
	{
		c = std::cin.get ();
	}
	if (ocomment::anyset (oCOMMENT_B_DOUBLE))
	{
		std::cout.put ('/');
		std::cout.put ('*');
		if (ocomment::anyset (oCOMMENT_B_TRIPLE))
		{
			std::cout.put ('\n');
			std::cout.put (' ');
			std::cout.put ('*');
		}
		while (oascii::nobreak (c))
		{
			std::cout.put (c);
			c = std::cin.get ();
		}
		if (ocomment::anyset (oCOMMENT_B_TRIPLE))
		{
			std::cout.put ('\n');
		}
		std::cout.put (' ');
		std::cout.put ('*');
		std::cout.put ('/');
	}
	else 
	{
		bool space = false;
		std::cout.put ('/');
		std::cout.put ('/');
		while (oascii::nobreak (c))
		{
			if (oascii::isblank (c))
			{
				c = std::cin.get ();
				space = true;
				continue;
			}
			if (space)
			{
				std::cout.put (' ');
				space = false;
				continue;
			}
			std::cout.put (c);
			c = std::cin.get ();
		}
		if (c != EOF)
		{
			std::cout.put (c);
		}
	}
	c = std::cin.get ();
	return (c);
}

/*====================================================================*
 *
 *   signed clang (signed c);
 *
 *   format ANSI C style comments and return the character after;
 *
 *   this method has two standard forms as follows interlaced with
 *   specific formatting function blocks; the second form is more
 *   reliable and veratile;
 *
 *      putc ('/', stdout);
 *      while ((c != '/') && (c != EOF))
 *      {
 *           while ((c != '*') && (c != EOF))
 *          {
 *              putc (c, stdout);
 *              c = getc (stdin);
 *          }
 *          putc (c, stdout);
 *          c = getc (stdin);
 *      }
 *      putc ('/', stdout);
 *
 *   and
 *
 *      putc ('/', stdout);
 *      do {
 *          ungetc (c, stdin);
 *          do {
 *              c = getc(stdin);
 *              putc (c,stdout);
 *          } while ((c != '*') && (c != EOF));
 *          c = getc (stdin);
 *      } while ((c != '/') && (c != EOF));
 *      putc ('/', stdout);
 *
 *--------------------------------------------------------------------*/

signed ocomment::clang (signed c)

{
	std::cout.put ('/');
	while ((c != '/') && (c != EOF))
	{
		while ((c != '*') && (c != EOF))
		{
			if (c == '\n')
			{
				c = ocomment::content (c, 3);
				continue;
			}
			std::cout.put (c);
			c = std::cin.get ();
		}
		std::cout.put ('*');
		if (ocomment::anyset (oCOMMENT_B_NOSTARS))
		{
			while (c == '*')
			{
				c = std::cin.get ();
			}
		}
		else
		{
			c = std::cin.get ();
		}
		if ((c == this->mupper) || (c == this->mlower) || (c == '*'))
		{
			c = ocomment::breaker (c, '*');
		}
		else if (ocomment::anyset (oCOMMENT_B_PREFACE) && (c == oCOMMENT_C_PREFACE))
		{
			c = ocomment::message (c, this->mpreface);
		}
		else if (ocomment::anyset (oCOMMENT_B_SPECIAL) && (c == oCOMMENT_C_SPECIAL))
		{
			c = ocomment::message (c, this->mspecial);
		}
		else if (ocomment::anyset (oCOMMENT_B_PACKAGE) && (c == oCOMMENT_C_PACKAGE))
		{
			c = ocomment::message (c, this->mpackage);
		}
		else if (ocomment::anyset (oCOMMENT_B_RELEASE) && (c == oCOMMENT_C_RELEASE))
		{
			c = ocomment::message (c, this->mrelease);
		}
		else if (ocomment::anyset (oCOMMENT_B_LICENSE) && (c == oCOMMENT_C_LICENSE))
		{
			c = ocomment::message (c, this->mlicense);
		}
	}
	std::cout.put ('/');
	std::cout.put ('\n');
	c = std::cin.get ();
	return (c);
}

/*====================================================================*
 *
 *   signed content (signed c, unsigned column) const;
 *
 *   print comment line; preserve intervening word spacing; remove 
 *   tailing white space;
 *
 *--------------------------------------------------------------------*/

signed ocomment::content (signed c, unsigned column) const

{
	std::cout.put (c);
	std::cout.put (' ');
	do 
	{
		c = std::cin.get ();
	}
	while (oascii::isblank (c));
	if (c != '*')
	{
		unsigned offset = 0;
		std::cout.put ('*');
		while (oascii::nobreak (c))
		{
			if (c == '*')
			{
				if (std::cin.peek () == '/')
				{
					return (c);
				}
			}
			if (c == ' ')
			{
				column++;
			}
			else if (c == '\t')
			{
				column -= column % 8;
				column += 8;
			}
			else 
			{
				while (offset < column)
				{
					std::cout.put (' ');
					offset++;
				}
				std::cout.put (c);
				column++;
				offset++;
			}
			c = std::cin.get ();
		}
	}
	return (c);
}

/*====================================================================*
 *
 *   signed breaker (signed c, signed e) const;
 *
 *   for comment bars to fixed length if present;
 *
 *--------------------------------------------------------------------*/

signed ocomment::breaker (signed c, signed e) const

{
	signed width = 0;
	signed start = c;
	while (c == start)
	{
		c = std::cin.get ();
		width++;
	}
	if ((c == e) || (e == start))
	{
		width = this->mwidth;
	}
	while (width-- > 0)
	{
		std::cout.put (start);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed message (unsigned char c, char const * string) const;
 *
 *   replace comment line with new one;
 *
 *   read and discard comment line; replace it with another starting 
 *   with appropriate start character; omit the start character when
 *   permanence is requested;
 *
 *--------------------------------------------------------------------*/

signed ocomment::message (signed c, char const * string) const

{
	signed o = c;
	do 
	{
		c = std::cin.get ();
	}
	while (oascii::nobreak (c));
	if (ocomment::allclear (oCOMMENT_B_DISCARD))
	{
		std::cout.put (ocomment::anyset (oCOMMENT_B_PERMANENT)? ' ': o);
		std::cout.put (' ');
		std::cout.put (' ');
		std::cout << string;
	}
	return (c);
}

/*====================================================================*
 *
 *   ocomment (unsigned length)
 *
 *--------------------------------------------------------------------*/

ocomment::ocomment (unsigned length)

{
	this->mpreface = new char [1];
	this->mpreface [0] = (char) (0);
	this->mpackage = new char [1];
	this->mpackage [0] = (char) (0);
	this->mrelease = new char [1];
	this->mrelease [0] = (char) (0);
	this->mlicense = new char [1];
	this->mlicense [0] = (char) (0);
	this->mspecial = new char [1];
	this->mspecial [0] = (char) (0);
	this->mupper = oCOMMENT_C_UPPER;
	this->mlower = oCOMMENT_C_LOWER;
	this->mwidth = oCOMMENT_WIDTH;
	return;
}

/*====================================================================*
 *
 *   ocomment (void)
 *
 *--------------------------------------------------------------------*/

ocomment::ocomment (void)

{
	this->mpreface = new char [1];
	this->mpreface [0] = (char) (0);
	this->mpackage = new char [1];
	this->mpackage [0] = (char) (0);
	this->mrelease = new char [1];
	this->mrelease [0] = (char) (0);
	this->mlicense = new char [1];
	this->mlicense [0] = (char) (0);
	this->mspecial = new char [1];
	this->mspecial [0] = (char) (0);
	this->mupper = oCOMMENT_C_UPPER;
	this->mlower = oCOMMENT_C_LOWER;
	this->mwidth = oCOMMENT_WIDTH;
	return;
}

/*====================================================================*
 *
 *   ~ ocomment (void)
 *
 *--------------------------------------------------------------------*/

ocomment::~ ocomment (void)

{
	delete [] this->mpreface;
	delete [] this->mpackage;
	delete [] this->mrelease;
	delete [] this->mlicense;
	delete [] this->mspecial;
	return;
}

/*====================================================================*
 *   end definition
 *--------------------------------------------------------------------*/

#endif



