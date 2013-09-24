/*====================================================================*
 *
 *   opage.cpp - implementation of the opage class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oPAGE_SOURCE
#define oPAGE_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#include "../classes/opage.hpp"
#include "../../gcc/date/date.h"

/*====================================================================*
 *
 *   char const * title () const;
 *   
 *   return current title string;
 *   
 *--------------------------------------------------------------------*/

char const * opage::title () const

{
	return (this->mtitle);
}

/*====================================================================*
 *
 *   opage & title (char const * title);
 *   
 *   set new title string if different from current title string;
 *   
 *--------------------------------------------------------------------*/

opage & opage::title (char const * title)

{
	this->mtitle = opage::replace (this->mtitle, title);
	return (* this);
}

/*====================================================================*
 *
 *   unsigned rows () const;
 *   
 *   return maximum row count;
 *   
 *--------------------------------------------------------------------*/

unsigned opage::rows () const

{
	return (this->mrows);
}

/*====================================================================*
 *
 *   opage & rows (unsigned rows)
 *   
 *   set maximum row count;
 *   
 *--------------------------------------------------------------------*/

opage & opage::rows (unsigned rows)

{
	this->mrows = rows;
	return (* this);
}

/*====================================================================*
 *
 *   unsigned cols () const;
 *   
 *   return maximum column count;
 *   
 *--------------------------------------------------------------------*/

unsigned opage::cols () const

{
	return (this->mcols);
}

/*====================================================================*
 *
 *   opage & cols (unsigned cols)
 *   
 *   set maximum column count;
 *   
 *--------------------------------------------------------------------*/

opage & opage::cols (unsigned cols)

{
	this->mcols = cols;
	return (* this);
}

/*====================================================================*
 *
 *   unsigned tabs () const;
 *   
 *   return current tab offset;
 *   
 *--------------------------------------------------------------------*/

unsigned opage::tabs () const

{
	return (this->mtabs);
}

/*====================================================================*
 *
 *   opage & tabs (unsigned tabs)
 *   
 *   set tab offset;
 *   
 *--------------------------------------------------------------------*/

opage & opage::tabs (unsigned tabs)

{
	this->mtabs = tabs;
	return (* this);
}

/*====================================================================*
 *
 *   signed put (signed c);
 *
 *   print one character on stdout; automatically update page, line,
 *   row and column counters; insert page headers and footers where
 *   needed;
 *
 *--------------------------------------------------------------------*/

signed opage::put (signed c)

{
	if (! this->mrow && ! this->mcol)
	{
		opage::header ();
		this->mrow = 1;
		this->mcol = 1;
	}
	if (c == EOF)
	{
		opage::put ('\f');
	}
	else if (c == '\f')
	{
		while (this->mrow < this->mrows)
		{
			opage::put ('\n');
		}
		opage::footer ();
		this->mpage++;
		this->mrow = 0;
		this->mcol = 0;
	}
	else if (c == '\r')
	{
		std::cout.put (c);
		this->mcol = 1;
	}
	else if (c == '\n')
	{
		std::cout.put (c);
		this->mline++;
		this->mrow++;
		this->mcol = 1;
	}
	else if (c == '\t')
	{
		while (this->mcol % this->mtabs)
		{
			opage::put (' ');
		}
		opage::put (' ');
	}
	else if (iscntrl (c))
	{
		std::cout.put (' ');
		this->mcol++;
	}
	else 
	{
		std::cout.put (c);
		this->mcol++;
	}
	if (this->mcol > this->mcols)
	{
		opage::put ('\n');
	}
	if (this->mrow > this->mrows)
	{
		opage::put ('\f');
	}
	return (c);
}

/*====================================================================*
 *
 *   opage & put (char const * string);
 *
 *   print a string on stdout;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

opage & opage::put (char const * string)

{
	if (string) while (* string)
	{
		opage::put (* string++);
	}
	return (* this);
}

/*====================================================================*
 *
 *   void opage::header ();
 *
 *   print page header on stdout; the footer does not affect current 
 *   row or column counters; one blank line separates text from the 
 *   footer;
 *
 *--------------------------------------------------------------------*/

opage & opage::header ()

{
	char buffer [this->mcols];
	time_t stamp = time ((time_t *) (0));
	signed length;
	signed offset;
	length = this->mcols - DAYTIME_LEN - 2;
	length = std::snprintf (buffer, this->mcols, "%-*.*s  ", length, length, this->mtitle);
	for (offset = 0; offset < length; offset++)
	{
		std::cout.put (buffer [offset]);
	}
	length = std::strftime (buffer, sizeof (buffer), DAYTIME, std::localtime (& stamp));
	for (offset = 0; offset < length; offset++)
	{
		std::cout.put (buffer [offset]);
	}
	std::cout.put ('\n');
	std::cout.put ('\n');
	return (* this);
}

/*====================================================================*
 *
 *   void footer (struct _page_ * page);
 * 
 *   print page footer on stdout; the footer does not affect current 
 *   row or column counters; one blank line separates text from the 
 *   footer;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

opage & opage::footer ()

{
	char buffer [this->mcols];
	signed length = std::snprintf (buffer, this->mcols, "- %d -", this->mpage);
	signed offset = this->mcols;
	if (length < offset)
	{
		offset -= length;
		offset /= 2;
	}
	else 
	{
		length = offset;
		offset = 0;
	}
	std::cout.put ('\n');
	while (offset > 0)
	{
		std::cout.put (' ');
		offset--;
	}
	while (length > 0)
	{
		std::cout.put (buffer [offset++]);
		length--;
	}
	std::cout.put ('\n');
	return (* this);
}

/*====================================================================*
 *
 *   opage (char const * title);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

opage::opage (char const * title)

{
	this->mtitle = new char [std::strlen (title) +  1];
	std::strcpy (this->mtitle, title);
	this->mrows = oPAGE_ROWS;
	this->mcols = oPAGE_COLS;
	this->mtabs = oPAGE_TABS;
	this->mpage = 1;
	this->mline = 1;
	this->mrow = 0;
	this->mcol = 0;
	return;
}

/*====================================================================*
 *
 *   opage::~opage ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

opage::~ opage ()

{
	delete [] this->mtitle;
	return;
}

/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif



