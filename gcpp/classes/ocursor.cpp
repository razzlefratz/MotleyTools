/*====================================================================*
 *
 *   ocursor.cpp - implementation of the ocursor class.
 * 
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCURSOR_SOURCE
#define oCURSOR_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstdio>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ocursor.hpp"

/*====================================================================*
 *
 *   size_t ocursor::charcount() const;
 *
 *
 *--------------------------------------------------------------------*/

size_t ocursor::charcount () const 

{
	return (this->mchar);
}

/*====================================================================*
 *
 *   size_t ocursor::linecount() const;
 *
 *
 *--------------------------------------------------------------------*/

size_t ocursor::linecount () const 

{
	return (this->mline);
}

/*====================================================================*
 *
 *   size_t ocursor::pagecount() const;
 *
 *
 *--------------------------------------------------------------------*/

size_t ocursor::pagecount () const 

{
	return (this->mpage);
}

/*====================================================================*
 *
 *   size_t ocursor::rowcount() const;
 *
 *
 *--------------------------------------------------------------------*/

size_t ocursor::rowcount () const 

{
	return (this->mrow);
}

/*====================================================================*
 *
 *   size_t ocursor::colcount() const;
 *
 *
 *--------------------------------------------------------------------*/

size_t ocursor::colcount () const 

{
	return (this->mcol);
}

/*====================================================================*
 *
 *   ocursor & ocursor::count(char c);
 *
 *
 *--------------------------------------------------------------------*/

ocursor & ocursor::count (char c) 

{
	switch ((char) (c)) 
	{
	case '\f':
		mchar++;
		mpage++;
		mrow = 1;
		mcol = 0;
		break;
	case '\r':
		mchar++;
		mcol = 0;
		break;
	case '\n':
		mchar++;
		mline++;
		mrow++;
		mcol = 0;
		break;
	case '\t':
		mchar++;
		while (++mrow % 8);
		break;
	default:
		mchar++;
		mcol++;
		break;
	}
	return (* this);
}

/*====================================================================*
 *
 *   ocursor & ocursor::clear();
 *
 *
 *--------------------------------------------------------------------*/

ocursor & ocursor::clear () 

{
	mchar = 0;
	mline = 1;
	mpage = 1;
	mrow = 1;
	mcol = 0;
	return (* this);
}

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

ocursor::ocursor () 

{
	this->clear ();
	return;
};

ocursor::~ocursor () 

{
	return;
}

/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif

