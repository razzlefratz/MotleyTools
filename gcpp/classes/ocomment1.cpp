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
 *   size_t width (void) const;
 *
 *   get and set the comment bar width;
 *
 *--------------------------------------------------------------------*/

#if oCOMMENT_EXTENDBAR

size_t ocomment::width (void) const

{
	return (this->mwidth);
}

ocomment & ocomment::width (size_t width)

{
	this->mwidth = width;
	return (* this);
}

#endif

/*====================================================================*
 *
 *   unsigned char cupper (void) const;
 *
 *   get and set the upper bar character;
 *
 *--------------------------------------------------------------------*/

#if oCOMMENT_EXTENDBAR

unsigned char ocomment::cupper (void) const

{
	return (this->mupper);
}

ocomment & ocomment::cupper (unsigned char upper)

{
	this->mupper = upper;
	return (* this);
}

#endif

/*====================================================================*
 *
 *   unsigned char clower (void) const;
 *
 *   get and set the lower bar character;
 *
 *--------------------------------------------------------------------*/

#if oCOMMENT_EXTENDBAR

unsigned char ocomment::clower (void) const

{
	return (this->mlower);
}

ocomment & ocomment::clower (unsigned char lower)

{
	this->mlower = lower;
	return (* this);
}

#endif

/*====================================================================*
 *
 *   char const * preface (void) const;
 *
 *   get and set the preface comment string;
 *
 *--------------------------------------------------------------------*/

#if oCOMMENT_EXTENDBAR
#if oCOMMENT_CUSTOMIZE

char const * ocomment::preface (void) const

{
	return (this->mpreface);
}

ocomment & ocomment::preface (char const * preface)

{
	this->mpreface = otext::replace (this->mpreface, preface);
	return (* this);
}

#endif
#endif

/*====================================================================*
 *
 *   char const * package (void) const;
 *
 *   get and set the package comment string;
 *
 *--------------------------------------------------------------------*/

#if oCOMMENT_EXTENDBAR
#if oCOMMENT_CUSTOMIZE

char const * ocomment::package (void) const

{
	return (this->mpackage);
}

ocomment & ocomment::package (char const * package)

{
	this->mpackage = otext::replace (this->mpackage, package);
	return (* this);
}

#endif
#endif

/*====================================================================*
 *
 *   char const * release (void) const;
 *
 *   get and set the release comment string;
 *
 *--------------------------------------------------------------------*/

#if oCOMMENT_EXTENDBAR
#if oCOMMENT_CUSTOMIZE

char const * ocomment::release (void) const

{
	return (this->mrelease);
}

ocomment & ocomment::release (char const * release)

{
	this->mrelease = otext::replace (this->mrelease, release);
	return (* this);
}

#endif
#endif

/*====================================================================*
 *
 *   char const * license (void) const;
 *
 *   get and set the license comment string;
 *
 *--------------------------------------------------------------------*/

#if oCOMMENT_EXTENDBAR
#if oCOMMENT_CUSTOMIZE

char const * ocomment::license (void) const

{
	return (this->mlicense);
}

ocomment & ocomment::license (char const * license)

{
	this->mlicense = otext::replace (this->mlicense, license);
	return (* this);
}

#endif
#endif

/*====================================================================*
 *
 *   char const * special (void) const;
 *
 *   get and set the special comment string;
 *
 *--------------------------------------------------------------------*/

#if oCOMMENT_EXTENDBAR
#if oCOMMENT_CUSTOMIZE

char const * ocomment::special (void) const

{
	return (this->mspecial);
}

ocomment & ocomment::special (char const * special)

{
	this->mspecial = otext::replace (this->mspecial, special);
	return (* this);
}

#endif
#endif

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
 *	putc ('/', stdout);
 *      while ((c != '/') && (c != EOF))
 *      {
 *          	while ((c != '*') && (c != EOF))
 *         	{
 *            		putc (c, stdout);
 *            		c = getc (stdin);
 *         	}
 *         	putc (c, stdout);
 *         	c = getc (stdin);
 *      }
 *      putc ('/', stdout);
 *
 *   and
 *
 *      putc ('/', stdout);
 *      do {
 *         	ungetc (c, stdin);
 *         	do {
 *            		c = getc(stdin);
 *            		putc (c,stdout);
 *         	} while ((c != '*') && (c != EOF));
 *         	c = getc (stdin);
 *      } while ((c != '/') && (c != EOF));
 *      putc ('/', stdout);
 *
 *--------------------------------------------------------------------*/

signed ocomment::clang (signed c)

{
	this->mcount = 0;
	std::cout.put ('/');
	c = std::cin.get ();
	while ((c != '/') && (c != EOF))
	{
		while ((c != '*') && (c != EOF));
		{

#if oCOMMENT_EXTENDBAR

/*
 *   if the character after as asterisk is UPPER or LOWER then collect the entire string
 *   and keep track of the length; if the string ends in asterisk then replace place it with
 *   another of fixed length using the same character; otherwise, replace it with another of
 *   the same length using the same character;
 */

			if ((c == this->mupper) || (c == this->mlower))
			{
				c = ocomment::breaker (c);
			}

#if oCOMMENT_CUSTOMIZE

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

#endif
#endif

#if oCOMMENT_PADMARGIN

/*
 *   if the next character is newline then flush the buffer and reset sp to the start; write the
 *   newline and one space then find the first non-blank character on the next comment line; if
 *   that character is not asterisk then write an asterisk and one or more spaces; increment the
 *   line counter for later;
 */

			else while (c == '\n')
			{
				ocomment::content ();
				* this->minsert++ = '\n';
				* this->minsert++ = ' ';
				do 
				{
					c = std::cin.get ();
				}
				while (oascii::isblank (c));
				if (c != '*')
				{
					* this->minsert++ = '*';
					* this->minsert++ = ' ';
					* this->minsert++ = ' ';
					* this->minsert++ = ' ';
				}
			}

#endif

			* this->minsert++ = c;
			c = std::cin.get ();
		}

#if 1

		do 
		{
			c = std::cin.get ();
		}
		while (c == '*');

#else

/*
 *	reduce strings of asterisks to one asterisk;
 */

		c = std::cin.get ();
		if (ocomment::anyset (oCOMMENT_B_SHORT))
		{
			while (c == '*')
			{
				c = std::cin.get ();
			}
		}

#endif

	}
	if (ocomment::anyset (oCOMMENT_B_TRIPLE) && ! this->mcount)
	{
		std::cout.put ('*');
		std::cout.put ('\n');
		std::cout.put (' ');
		this->minsert--;
	}
	ocomment::content ();
	if (ocomment::anyset (oCOMMENT_B_TRIPLE) && ! this->mcount)
	{
		std::cout.put ('\n');
		std::cout.put (' ');
		std::cout.put ('*');
	}
	std::cout.put ('/');
	std::cout.put ('\n');
	c = std::cin.get ();
	return (c);
}

/*====================================================================*
 *
 *   signed breaker (signed c);
 *
 *--------------------------------------------------------------------*/

#if oCOMMENT_EXTENDBAR

signed ocomment::breaker (signed c)

{
	signed width = 0;
	signed start = c;
	while (c == start)
	{
		c = std::cin.get ();
		width++;
	}
	if (c == '*')
	{
		width = this->mwidth;
	}
	while (width-- > 0)
	{
		* this->minsert++ = (char) (start);
	}
	return (c);
}

#endif

/*====================================================================*
 *
 *   signed message (unsigned char c, char const * string);
 *
 *   replace comment line with new one;
 *
 *   copy c then string to buffer; read and discard characters from
 *   stdin until newline or EOF is read; return read character;
 *
 *--------------------------------------------------------------------*/

#if oCOMMENT_EXTENDBAR
#if oCOMMENT_CUSTOMIZE

signed ocomment::message (signed c, char const * string)

{
	if (ocomment::anyset (oCOMMENT_B_DISCARD))
	{
		do 
		{
			c = std::cin.get ();
		}
		while (oascii::isblank (c));
		while (c == * string++)
		{
			c = std::cin.get ();
		};
	}
	else 
	{
		* this->minsert++ = ocomment::anyset (oCOMMENT_B_PERMANENT)? ' ': c;
		* this->minsert++ = ' ';
		* this->minsert++ = ' ';
		while (* string)
		{
			* this->minsert++ = * string++;
		}
	}
	while (oascii::nobreak (c))
	{
		c = std::cin.get ();
	}
	return (c);
}

#endif
#endif

/*====================================================================*
 *
 *   ocomment::content (void);
 *
 *   print buffer after removing trailing white space;
 *
 *--------------------------------------------------------------------*/

ocomment & ocomment::content (void)

{
	static unsigned count = 0;
	this->mcount++;
	this->moutput = this->mbuffer;
	while (this->minsert > this->moutput)
	{
		this->minsert--;
		if (oascii::isspace (* this->minsert))
		{
			continue;
		}
		this->minsert++;
		break;
	}
	if (std::memcmp (this->mbuffer, "\n *", this->minsert - this->moutput))
	{
		count = 0;
	}
	else 
	{
		count++;
	}
	if (count < 2) while (this->moutput < this->minsert)
	{
		std::cout.put (* this->moutput++);
	}
	this->minsert = this->mbuffer;
	return (* this);
}

/*====================================================================*
 *
 *   ocomment (size_t length)
 *
 *--------------------------------------------------------------------*/

ocomment::ocomment (size_t length)

{
	this->mbuffer = new char [length];
	this->minsert = this->mbuffer;
	this->mlength = length;
	this->mcount = 0;

#if oCOMMENT_EXTENDBAR

	this->mupper = oCOMMENT_C_UPPER;
	this->mlower = oCOMMENT_C_LOWER;
	this->mwidth = oCOMMENT_WIDTH;

#if oCOMMENT_CUSTOMIZE

	this->mpackage = new char [1];
	this->mpackage [0] = (char) (0);
	this->mrelease = new char [1];
	this->mrelease [0] = (char) (0);
	this->mlicense = new char [1];
	this->mlicense [0] = (char) (0);

#endif
#endif

	return;
}

/*====================================================================*
 *
 *   ocomment (void)
 *
 *--------------------------------------------------------------------*/

ocomment::ocomment (void)

{
	this->mlength = oCOMMENT_LENGTH;
	this->mbuffer = new char [this->mlength];
	this->minsert = this->mbuffer;
	this->mcount = 0;

#if oCOMMENT_EXTENDBAR

	this->mupper = oCOMMENT_C_UPPER;
	this->mlower = oCOMMENT_C_LOWER;
	this->mwidth = oCOMMENT_WIDTH;

#if oCOMMENT_CUSTOMIZE

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

#endif
#endif

	return;
}

/*====================================================================*
 *
 *   ~ ocomment (void)
 *
 *--------------------------------------------------------------------*/

ocomment::~ ocomment (void)

{

#if oCOMMENT_EXTENDBAR
#if oCOMMENT_CUSTOMIZE

	delete [] this->mpreface;
	delete [] this->mpackage;
	delete [] this->mrelease;
	delete [] this->mlicense;
	delete [] this->mspecial;

#endif
#endif

	delete [] this->mbuffer;
	return;
}

/*====================================================================*
 *   end definition
 *--------------------------------------------------------------------*/

#endif



