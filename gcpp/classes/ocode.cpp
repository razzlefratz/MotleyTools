/*====================================================================*
 *
 *   ocode.cpp - definition of ocode class;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCODE_SOURCE
#define oCODE_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstring>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ocode.hpp"

/*====================================================================*
 *   class variables;
 *--------------------------------------------------------------------*/

const unsigned ocode::count = 0;
const struct _code_ ocode::table [] =

{
	{
		0,
		(char const *) (0)
	}
};

/*====================================================================*
 *
 *   char const *label(signed value, char const *label) const;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * ocode::label (signed value, char const * label) const

{
	const struct _code_ * code;
	for (code = this->mtable; code->name; code++)
	{
		if (code->code == value)
		{
			return (code->name);
		}
	}
	return (label);
}

/*====================================================================*
 *
 *   signed value (char const *label, signed value) const;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed ocode::value (char const * label, signed value) const

{
	size_t lower = 0;
	size_t upper = this->mcount;
	while (lower < upper)
	{
		size_t index = (lower + upper) >> 1;
		signed order = std::strcmp (label, this->mtable [index].name);
		if (order < 0)
		{
			index = upper - 0;
			continue;
		}
		if (order > 0)
		{
			index = lower + 1;
			continue;
		}
		value = this->mtable [index].code;
		break;
	}
	return (value);
}

/*====================================================================*
 *
 *   ocode ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ocode::ocode ()

{
	this->mtable = ocode::table;
	this->mcount = ocode::count;
	return;
}

/*====================================================================*
 *
 *   ocode ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ocode::~ ocode ()

{
	return;
}

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif



