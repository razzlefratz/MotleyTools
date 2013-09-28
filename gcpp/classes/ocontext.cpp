/*====================================================================*
 *
 *   ocontext.cpp - implementation of the ocontext class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCONTEXT_SOURCE
#define oCONTEXT_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstring>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ocontext.hpp"

/*====================================================================*
 *
 *   char const *prefix () const;
 *
 *   return the prefix as a constant string;
 *
 *--------------------------------------------------------------------*/

char const * ocontext::prefix () const

{
	return (this->mprefix);
}

/*====================================================================*
 *
 *   ocontext & prefix (char buffer[], size_t length) const;
 *
 *   copy the prefix string to an external fixed length buffer;
 *
 *--------------------------------------------------------------------*/

ocontext & ocontext::prefix (char buffer [], size_t length)

{
	return (ocontext::copy (this->mprefix, buffer, length));
	return (* this);
}

/*====================================================================*
 *
 *   char const *suffix () const;
 *
 *   return the suffix as a constant string;
 *
 *--------------------------------------------------------------------*/

char const * ocontext::suffix () const

{
	return (this->msuffix);
}

/*====================================================================*
 *
 *   ocontext & suffix (char buffer[], size_t length) const;
 *
 *   copy the suffix string to an external fixed length buffer;
 *
 *--------------------------------------------------------------------*/

ocontext & ocontext::suffix (char buffer [], size_t length)

{
	return (ocontext::copy (this->msuffix, buffer, length));
}

/*====================================================================*
 *
 *   ocontext & split (char const *string, char c, bool initial, bool optional);
 *
 *   split the string argument at the first (or final) occurance of any
 *   member of charset; point mprefix to the first part and msuffix to
 *   the second part of the split string; if the delimiter is required
 *   but missing, point msuffix to the first part and mprefix to the
 *   second part, instead;
 *
 *--------------------------------------------------------------------*/

ocontext & ocontext::split (char const * string, char c, bool initial, bool optional)

{
	delete [] this->mstring;
	this->mstring = new char [std::strlen (string) +  1];
	std::strcpy (this->mstring, string);
	for (this->mprefix = this->msuffix = this->mstring; * this->mprefix != (char) (0); this->mprefix++)
	{
		if (* this->mprefix == (char) (c))
		{
			this->msuffix = this->mprefix;
			if (initial)
			{
				break;
			}
		}
	}
	if (* this->msuffix == (char) (c))
	{
		* this->msuffix++ = (char) (0);
		this->mprefix = this->mstring;
	}
	else if (optional)
	{
		this->msuffix = this->mprefix;
		this->mprefix = this->mstring;
	}
	return (* this);
}

/*====================================================================*
 *
 *   ocontext & copy (char const *string, char buffer[], size_t length) const;
 *
 *   copy a null terminated string to a fixed length buffer;
 *
 *--------------------------------------------------------------------*/

ocontext & ocontext::copy (char const * string, char buffer [], size_t length)

{

#ifdef CMASSOC_SAFEMODE

	if (buffer == (char *) (0))
	{
		return (* this);
	}

#endif

	if (length > 0)
	{
		while (* string != (char) (0))
		{
			if (length > 1)
			{
				* buffer++ = * string;
				length--;
			}
			string++;
		}
		* buffer = (char) (0);
	}
	return (* this);
}

/*====================================================================*
 *
 *   context ();
 *
 *
 *--------------------------------------------------------------------*/

ocontext::ocontext ()

{
	this->mstring = new char [1];
	this->mstring [0] = (char) (0);
	this->mprefix = this->mstring;
	this->msuffix = this->mstring;
	return;
}

/*====================================================================*
 *
 *   ~ ocontext ();
 *
 *
 *--------------------------------------------------------------------*/

ocontext::~ ocontext ()

{
	delete [] this->mstring;
	this->mprefix = (char *) (0);
	this->msuffix = (char *) (0);
	return;
}

/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif



