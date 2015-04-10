/*====================================================================*
 *
 *   ocomment.cpp - definition of ocomment class
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
 *   get and set comment bar width, excluding endpoints;
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
 *   unsigned align (void) const;
 *
 *   get and set the comment space;
 *
 *--------------------------------------------------------------------*/

unsigned ocomment::align (void) const

{
	return (this->mstart);
}

ocomment & ocomment::align (unsigned space)

{
	this->mstart = space;
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
 *   char const * publish (void) const;
 *
 *   get and set the publish comment string;
 *
 *--------------------------------------------------------------------*/

char const * ocomment::publish (void) const

{
	return (this->mpublish);
}

ocomment & ocomment::publish (char const * publish)

{
	this->mpublish = otext::replace (this->mpublish, publish);
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
 *   ocomment & ocomment::preamble (void);
 *
 *   output an empty preamble comment block;
 *
 *--------------------------------------------------------------------*/

ocomment & ocomment::preamble (void)

{
	std::cout << "/*" << '=' << "*" << std::endl;
	std::cout << " *" << std::endl;
	std::cout << " *" << std::endl;
	std::cout << " *" << std::endl;
	std::cout << " *" << oCOMMENT_C_LICENSE << "   " << std::endl;
	std::cout << " *" << std::endl;
	std::cout << " *" << oCOMMENT_C_PACKAGE << "   " << std::endl;
	std::cout << " *" << oCOMMENT_C_RELEASE << "   " << std::endl;
	std::cout << " *" << oCOMMENT_C_PUBLISH << "   " << std::endl;
	std::cout << " *" << std::endl;
	std::cout << " *" << '-' << "*/" << std::endl;
	return (* this);
}

/*====================================================================*
 *
 *   signed comment (signed c) const;
 *
 *   read and write comment blocks; remove blank lines between C++ 
 *   comments but insert a blank line between C comment;
 *
 *--------------------------------------------------------------------*/

signed ocomment::comment (signed c)

{
	while (c == '/')
	{
		if (std::cin.peek () == '/')
		{
			c = ocomment::cplus (c);
			do 
			{
				c = std::cin.get ();
			}
			while (oascii::isspace (c));
			continue;
		}
		if (std::cin.peek () == '*')
		{
			c = ocomment::clang (c);
			do 
			{
				c = std::cin.get ();
			}
			while (oascii::isspace (c));

/*
 *	insert blank line between adjacent C Language comment blocks but remove
 *	blank lines between adjacent C++ comment blocks, as above;
 */

			if (c == '/')
			{
				if (std::cin.peek () == '*')
				{
					std::cout.put ('\n');
				}
			}
			continue;
		}
		std::cout.put (c);
		c = std::cin.get ();
		break;
	}
	return (c);
}

/*====================================================================*
 *
 *   signed cplus (signed c);
 *
 *   format C++ comment and return the character immediately after 
 *   comment; the comment includes starting slashes and terminating 
 *   newline;
 *
 *   read and discard strings of leading slashes;
 *
 *   if oCOMMENT_B_DOUBLE then convert C++ comment to C comment;
 *
 *   if oCOMMENT_B_TRIPLE then convert C++ comment to multi-line
 *   C comment;
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
	return (c);
}

/*====================================================================*
 *
 *   signed clang (signed c);
 *
 *   format ANSI C style comments and return the character after the
 *   comment; the comment includes the opening and closing inverted 
 *   pair slash-asterisk and the intervening text;                  
 *
 *   this implementation appends one newline immediately after the 
 *   comment; 
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
	std::cout.put (c);
	c = std::cin.get ();
	while ((c != '/') && (c != EOF))
	{
		while ((c != '*') && (c != EOF))
		{
			c = ocomment::content (c);
		}
		if (c != EOF)
		{
			c = ocomment::special (c);
		}
	}
	std::cout.put ('/');
	std::cout.put ('\n');
	return (c);
}

/*====================================================================*
 *
 *   signed content (signed c) const;
 *
 *   print comment line; preserve intervening word spacing; remove 
 *   tailing white space;
 *
 *--------------------------------------------------------------------*/

signed ocomment::content (signed c) const

{
	std::cout.put (c);
	if (c == '\n')
	{
		std::cout.put (' ');
		do 
		{
			c = std::cin.get ();
		}
		while (oascii::isblank (c));
		if (c != '*')
		{
			unsigned column = this->mstart;
			unsigned offset = 0;
			std::cout.put ('*');
			if ((c == '=') || (c == '-') || (c == '*'))
			{
				c = ocomment::breaker (c);
			}
			while (oascii::nobreak (c))
			{
				if ((c == '*') && (std::cin.peek () == '/'))
				{
					break;
				}
				else if (c == ' ')
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
	}
	else 
	{
		c = std::cin.get ();
	}
	return (c);
}

/*====================================================================*
 *
 *   signed special (signed c) const;
 *
 *   detect, and optionally replace, special comment lines;
 *
 *--------------------------------------------------------------------*/

signed ocomment::special (signed c) const

{
	std::cout.put ('*');
	c = std::cin.get ();
	if ((c == '=') || (c == '-') || (c == '*'))
	{
		c = ocomment::breaker (c);
	}
	else if ((c == oCOMMENT_C_PACKAGE) && ocomment::anyset (oCOMMENT_B_PACKAGE))
	{
		c = ocomment::message (c, this->mpackage);
	}
	else if ((c == oCOMMENT_C_RELEASE) && ocomment::anyset (oCOMMENT_B_RELEASE))
	{
		c = ocomment::message (c, this->mrelease);
	}
	else if ((c == oCOMMENT_C_PUBLISH) && ocomment::anyset (oCOMMENT_B_PUBLISH))
	{
		c = ocomment::message (c, this->mpublish);
	}
	else if ((c == oCOMMENT_C_LICENSE) && ocomment::anyset (oCOMMENT_B_LICENSE))
	{
		c = ocomment::message (c, this->mlicense);
	}
	else if ((c == '('))
	{
		c = ocomment::section (')');
	}
	else if ((c == '['))
	{
		c = ocomment::section (']');
	}
	else if (oascii::isquote (c))
	{
		c = ocomment::section (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed breaker (signed c) const;
 *
 *   force comment bars to fixed width, when present, by consuming, 
 *   discarding and rewriting the existing comment bar;
 *
 *--------------------------------------------------------------------*/

signed ocomment::breaker (signed c) const

{
	signed count = 0;
	signed start = c;
	while (c == start)
	{
		c = std::cin.get ();
		count++;
	}
	if ((start == '*') || (c == '*') || oascii::isbreak (c))
	{
		count = this->mwidth;
	}
	while (count-- > 0)
	{
		std::cout.put (start);
	}
	if ((start == '*') || oascii::isbreak (c))
	{
		std::cout.put ('*');
	}
	return (c);
}

/*====================================================================*
 *
 *   signed section (signed c);
 *
 *
 *
 *--------------------------------------------------------------------*/

signed ocomment::section (signed c) const

{
	for (unsigned count = this->mwidth; count--;  std::cout.put ('='));
	std::cout.put ('*');
	std::cout.put ('\n');
	std::cout.put (' ');
	std::cout.put ('*');
	std::cout.put (' ');
	std::cout.put (' ');
	std::cout.put (' ');
	for (signed o = std::cin.get (); (o != c) && (o != EOF); o = std::cin.get ())
	{
		std::cout.put (o);
		if (o == '\n')
		{
			std::cout.put (' ');
			std::cout.put ('*');
		}
	}
	std::cout.put ('\n');
	std::cout.put (' ');
	std::cout.put ('*');
	for (unsigned count = this->mwidth; count--;  std::cout.put ('-'));
	c = std::cin.get ();
	if (c == EOF)
	{
		std::cout.put ('*');
	}
	return (c);
}

/*====================================================================*
 *
 *   signed message (unsigned char c, char const * string) const;
 *
 *   replace special comments with a new one;
 *
 *   read and discard comment line; replace it with another starting 
 *   with appropriate start character; omit the start character when
 *   permanence is requested;
 *
 *--------------------------------------------------------------------*/

signed ocomment::message (signed c, char const * string) const

{
	signed start = c;
	do 
	{
		c = std::cin.get ();
	}
	while (oascii::nobreak (c));
	if (ocomment::allclear (oCOMMENT_B_DISCARD))
	{
		unsigned align = this->mstart;
		if ((align) && ocomment::allclear (oCOMMENT_B_FOREVER))
		{
			std::cout.put (start);
			align--;
		}
		while (align--)
		{
			std::cout.put (' ');
		}
		std::cout << string;
	}
	return (c);
}

/*====================================================================*
 *
 *   ocomment (void)
 *
 *--------------------------------------------------------------------*/

ocomment::ocomment (void)

{
	this->mpackage = new char [1];
	this->mpackage [0] = (char) (0);
	this->mrelease = new char [1];
	this->mrelease [0] = (char) (0);
	this->mpublish = new char [1];
	this->mpublish [0] = (char) (0);
	this->mlicense = new char [1];
	this->mlicense [0] = (char) (0);
	this->mstart = oCOMMENT_START;
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
	delete [] this->mpackage;
	delete [] this->mrelease;
	delete [] this->mpublish;
	delete [] this->mlicense;
}

/*====================================================================*
 *   end definition
 *--------------------------------------------------------------------*/

#endif



