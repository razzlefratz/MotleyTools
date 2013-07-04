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

#include <iostream>
#include <cstdio>
#include <cstring>
#include <ctime>

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#include "../classes/date.h"
#include "../classes/opage.hpp"

/*====================================================================*
 *
 *   char const * title () const;
 *   
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
 *   
 *--------------------------------------------------------------------*/

opage & opage::title (char const * title) 

{
	if (std::strcmp (title, this->mtitle)) 
	{
		delete [] this->mtitle;
		this->mtitle = new char [strlen (title)+1];
		std::strcpy (this->mtitle, title);
	}
	return (* this);
}

/*====================================================================*
 *
 *   unsigned rows () const;
 *   
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
 *   
 *--------------------------------------------------------------------*/

opage & opage::tabs (unsigned tabs) 

{
	this->mtabs = tabs;
	return (* this);
}

/*====================================================================*
 *
 *   int put (int c); 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

int opage::put (int c) 

{
	char header [1024] = 
	{
		0
	};
	signed length = 0;
	time_t stamp = time ((time_t *)(0));
	switch (c) 
	{
	case '\t':
		do
		{
			this->mtab++;
		}
		while (this->mtab % this->mtabs);
		break;
	case '\f':
		if (this->mcol > 0) 
		{
			this->put ('\n');
		}
		while (this->mrow < this->mrows) 
		{
			std::cout.put ('\n');
			this->mrow++;
		}
		this->mpage++;
		this->mrow = 0;
		this->mcol = 0;
		this->mtab = 0;
		length += std::snprintf (header + length, sizeof (header) - length, "Page %03d", this->mpage);
		length += std::snprintf (header + length, sizeof (header) - length, "   %-*.*s   ", this->mhdr, this->mhdr, this->mtitle);
		length += std::strftime (header + length, sizeof (header) - length, DAYTIME, localtime (& stamp));
		length += std::snprintf (header + length, sizeof (header) - length, "\n\n");
		this->put (header);
		break;
	case '\r':
		std::cout.put (c);
		this->mcol = 0;
		this->mtab = 0;
		break;
	case '\n':
		std::cout.put (c);
		this->mrow++;
		this->mcol = 0;
		this->mtab = 0;
		if (this->mrow >= this->mrows) 
		{
			this->put ('\f');
		}
		break;
	default:
		

#if 0

		if (!this->mpage && !this->mrow && !this->mcol) 
		{
			this->put ('\f');
		}

#endif

		while (this->mcol < this->mtab) 
		{
			std::cout.put (' ');
			this->mcol++;
		}
		if (iscntrl (c)) 
		{
			c = ' ';
		}
		std::cout.put (c);
		this->mcol++;
		if (this->mcol >= this->mcols) 
		{
			this->put ('\n');
		}
		break;
	}
	return (c);
}

/*====================================================================*
 *
 *   char const * put (char const * string);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * opage::put (char const * string) 

{
	if (string != (char const *)(0)) 
	{
		char const * sp = string;
		while (* sp != (char)(0)) 
		{
			this->put (* sp++);
		}
	}
	return (string);
}

/*====================================================================*
 *
 *   opage & eject ();
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

opage & opage::eject () 

{
	while (this->mrow < this->mrows) 
	{
		std::cout.put ('\n');
		this->mrow++;
	}
	this->mrow = 0;
	this->mcol = 0;
	this->mtab = 0;
	return (* this);
}

/*====================================================================*
 *
 *   opage ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

opage::opage () 

{
	this->mflags = 0;
	this->mtitle = new char [1];
	this->mtitle [0] = (char)(0);
	this->mhdr = oPAGE_COLS - 48;
	this->mrows = oPAGE_ROWS;
	this->mcols = oPAGE_COLS;
	this->mtabs = oPAGE_TABS;
	this->mpage = 0;
	this->mline = 0;
	this->mrow = 0;
	this->mcol = 0;
	this->mtab = 0;
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

opage::~opage () 

{
	return;
}

/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif

