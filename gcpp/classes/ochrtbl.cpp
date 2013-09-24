/*====================================================================*
 *
 *   ochrtbl.cpp - definition of ochrtbl class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCHRTBL_SOURCE
#define oCHRTBL_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <climits>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ochrtbl.hpp"

/*====================================================================*
 *
 *   char ochrtbl::convert (unsigned c) const;
 *
 *   convert character c to the character stored in mtable [];
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

unsigned ochrtbl::convert (unsigned c) const

{
	return (this->mtable [c & UCHAR_MAX]);
}

/*====================================================================*
 *
 *   ochrtbl & convert (  char *string);
 *
 *   convert each character in string;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ochrtbl & ochrtbl::convert (char * string)

{
	if (string) while (* string)
	{
		* string = this->mtable [(unsigned) (* string)];
	}
	return (* this);
}

/*====================================================================*
 *
 *   signed compare (char const *string1, char const *string2)
 *
 *   compare two strings and return -1, 0 or 1 to indicate that the first
 *   string lexographically precedes, matches or follows the second using
 *   the specified collating sequence.
 *
 *   the collating sequence is table driven; the absolute character value
 *   is used to retrieve the relative character value used in comparison;
 *
 *   For example, if 'B' is to precede 'A' then fill table['B'] with some
 *   value that is less than table['A']; it's all up to you;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed ochrtbl::compare (char const * string1, char const * string2) const

{
	if (string1 == string2)
	{
		return (0);
	}
	if (! string1)
	{
		return (- 1);
	}
	if (! string2)
	{
		return (1);
	}
	while (this->mtable [(unsigned) (* string1)] == this->mtable [(unsigned) (* string2)])
	{
		if (! this->mtable [(unsigned) (* string1)])
		{
			return (0);
		}
		string1++;
		string2++;
	}
	return (this->mtable [(unsigned) (* string1)] < this->mtable [(unsigned) (* string2)]? - 1: 1);
}

/*====================================================================*
 *
 *   ochrtbl::ochrtbl ();
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ochrtbl::ochrtbl ()

{
	ochrtbl::c = (char) (0);
	return;
}

/*====================================================================*
 *
 *   ochrtbl::~ochrtbl ();
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ochrtbl::~ ochrtbl ()

{
	return;
}

/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif



