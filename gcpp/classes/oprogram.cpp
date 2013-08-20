/*====================================================================*
 *
 *   oprogram.cpp - implementation of the oprogram class.
 *
 *   the oprogram class is a generic source code formatter for C-style
 *   languages including C, C++, PHP, java, CSS and DNS; as one example,
 *   this file was probably formatted by oprogram;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oPROGRAM_SOURCE
#define oPROGRAM_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstdio>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oprogram.hpp"
#include "../classes/oascii.hpp"

/*====================================================================*
 *
 *   signed css2 (signed c);
 *
 *   read from stdin and write to stdout; indent C style text based
 *   on '{', ';' and '}' characters; leave '#' comments alone; this
 *   program is suitable for css functions, awk programs and bind 
 *   name.conf files;
 *
 *--------------------------------------------------------------------*/

signed oprogram::css2 (signed c) 

{
	oprogram::level (0);
	oprogram::space (0);
	while (c != EOF) 
	{
		if (oascii::isspace (c)) 
		{
			c = oprogram::find (c);
			continue;
		}
		if ((c == ',') || (c == ';')) 
		{
			c = oprogram::keep (c);
			c = oprogram::find (c);
			continue;
		}
		if (c == '{') 
		{
			oprogram::endline (2);
			oprogram::newline ();
			c = oprogram::keep (c);
			c = oprogram::find (c);
			oprogram::increment ();
			oprogram::space (1);
			continue;
		}
		if (c == '}') 
		{
			oprogram::decrement ();
			oprogram::endline (1);
			oprogram::newline ();
			c = oprogram::keep (c);
			c = oprogram::find (c);
			oprogram::space (1);
			continue;
		}
		oprogram::endline ();
		oprogram::newline ();
		c = oprogram::context (c, "{;}</>");
		oprogram::space (1);
	}
	oprogram::endline (1);
	return (c);
}

/*====================================================================*
 *
 *   signed java (signed c);
 *
 *   read from stdin and write to stdout; indent C style text based
 *   on '{', ';' and '}' characters; leave '#' comments alone; this
 *   program is suitable for java functions;
 *
 *--------------------------------------------------------------------*/

signed oprogram::java (signed c) 

{
	oprogram::space (0);
	oprogram::level (0);
	while (c != EOF) 
	{
		if (oascii::isspace (c)) 
		{
			c = oprogram::find (c);
			continue;
		}
		if ((c == ',') || (c == ';')) 
		{
			c = oprogram::keep (c);
			c = oprogram::find (c);
			continue;
		}
		if (c == '{') 
		{
			oprogram::endline (1);
			oprogram::newline ();
			c = oprogram::keep (c);
			c = oprogram::find (c);
			oprogram::increment ();
			oprogram::space (1);
			continue;
		}
		if (c == '}') 
		{
			oprogram::decrement ();
			oprogram::endline (1);
			oprogram::newline ();
			c = oprogram::keep (c);
			c = oprogram::find (c);
			oprogram::space (1);
			continue;
		}
		oprogram::endline ();
		oprogram::newline ();
		c = oprogram::context (c, "{;}</>");
		oprogram::space (1);
	}
	oprogram::endline (1);
	return (c);
}

/*====================================================================*
 *
 *   oprogram ()
 *
 *--------------------------------------------------------------------*/

oprogram::oprogram () 

{
	return;
}

/*====================================================================*
 *
 *   ~oprogram ()
 *
 *--------------------------------------------------------------------*/

oprogram::~oprogram () 

{
	return;
}

/*====================================================================*
 *   end implementation
 *--------------------------------------------------------------------*/

#endif

