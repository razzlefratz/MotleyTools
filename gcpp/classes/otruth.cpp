/*====================================================================*
 *
 *   otruth.cpp - definition of otruth class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oTRUTH_SOURCE
#define oTRUTH_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <climits>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/otruth.hpp"

/*====================================================================*
 *   class variables;
 *--------------------------------------------------------------------*/

const size_t otruth::count = 8;
const struct _code_ otruth::table [] =

{
	{
		false,
		"0"
	},
	{
		true,
		"1"
	},
	{
		false,
		"false"
	},
	{
		false,
		"no"
	},
	{
		false,
		"off"
	},
	{
		true,
		"on"
	},
	{
		true,
		"true"
	},
	{
		true,
		"yes"
	},
	{
		0,
		(char const *) (0)
	}
};

/*====================================================================*
 *
 *   otruth();
 *
 *   set base code table to truth table;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otruth::otruth ()

{
	otruth::mtable = otruth::table;
	otruth::mcount = otruth::count;
	return;
}

/*====================================================================*
 *
 *   ~otruth();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otruth::~ otruth ()

{
	return;
}

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif



