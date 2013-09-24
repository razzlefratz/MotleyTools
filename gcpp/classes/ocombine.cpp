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
 *   char const *string () const;
 *
 *   return the prefix as a constant string; 
 *
 *--------------------------------------------------------------------*/

char const * ocontext::string () const

{
	return (this->mstring);
}

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
 *   ocontext & string (char buffer[], size_t length) const;
 *
 *   copy the string to an external buffer; 
 *
 *--------------------------------------------------------------------*/

ocontext & ocontext::string (char buffer [], size_t length)

{

#ifdef CMASSOC_SAFEMODE

	if (buffer == (char *) (0))
	{
		return (* this);
	}

#endif

	if (length > 0)
	{
		for (char const * string = this->mstring; * string != (char) (0); ++ string)
		{
			if (length > 1)
			{
				* buffer++ = * string;
				length--;
			}
		}
		* buffer = (char) (0);
	}
	return (* this);
}

/*====================================================================*
 *
 *   ocontext & prefix (char buffer[], size_t length) const;
 *
 *   copy the prefix to an external buffer; 
 *
 *--------------------------------------------------------------------*/

ocontext & ocontext::prefix (char buffer [], size_t length)

{

#ifdef CMASSOC_SAFEMODE

	if (buffer == (char *) (0))
	{
		return (* this);
	}

#endif

	if (length > 0)
	{
		for (char const * string = this->mprefix; * string != (char) (0); ++ string)
		{
			if (length > 1)
			{
				* buffer++ = * string;
				length--;
			}
		}
		* buffer = (char) (0);
	}
	return (* this);
}

/*====================================================================*
 *
 *   ocontext & suffix (char buffer[], size_t length) const;
 *
 *   copy the prefix to an external buffer; 
 *
 *--------------------------------------------------------------------*/

ocontext & ocontext::suffix (char buffer [], size_t length)

{

#ifdef CMASSOC_SAFEMODE

	if (buffer == (char *) (0))
	{
		return (* this);
	}

#endif

	if (length > 0)
	{
		for (char const * string = this->msuffix; * string != (char) (0); ++ string)
		{
			if (length > 1)
			{
				* buffer++ = * string;
				length--;
			}
		}
		* buffer = (char) (0);
	}
	return (* this);
}

/*====================================================================*
 *
 *   ocontext & split (char const *string, char const *charset, bool first, bool required);
 *
 *   split the string argument at the first (or final) occurance of any
 *   member of charset; point mprefix to the first part and msuffix to
 *   the second part of the split string; if the delimiter was required
 *   but missing, point msuffix to the first part and mprefix to the
 *   second part, instead; 
 *
 *--------------------------------------------------------------------*/

ocontext & ocontext::split (char const * string, char const * charset, bool first, bool required)

{
	delete [] this->mstring;
	this->mstring = new char [strlen (string) +  1];
	strcpy (this->mstring, string);
	this->mprefix = this->mstring;
	this->msuffix = (char *) (0);
	while (* this->mprefix != (char) (0))
	{
		if (ocontext::member (charset, * this->mprefix))
		{
			this->msuffix = this->mprefix;
			if (first)
			{
				break;
			}
		}
		this->mprefix++;
	}
	if (this->msuffix != (char *) (0))
	{
		* this->msuffix++ = (char) (0);
		this->mprefix = this->mstring;
	}
	else if (! required)
	{
		this->msuffix = this->mprefix;
		this->mprefix = this->mstring;
	}
	else 
	{
		this->msuffix = this->mstring;
	}
	return (* this);
}

ocontext & ocontext::merge (char const * prefix, char const * middle, char const * suffix)

{
	size_t length = 0;
	length += std::strlen (prefix);
	length += std::strlen (middle);
	length += std::strlen (suffix);
	delete [] this->mstring;
	this->mprefix = this->msuffix = this->mstring = new char [length +  1];;
	if ((prefix == (char const *) (0)) || (* prefix == (char) (0)))
	{
		while (* suffix != (char) (0))
		{
			* this->mprefix++ = * suffix++;
		}
		* this->mprefix = (char) (0);
		this->mprefix = this->msuffix;
		return (* this);
	}
	if ((suffix == (char const *) (0)) || (* suffix == (char) (0)))
	{
		this->mprefix = this->msuffix = this->mstring = new char [strlen (prefix) +  1];;
		while (* prefix != (char) (0))
		{
			* this->msuffix++ = * prefix++;
		}
		* this->msuffix = (char) (0);
		this->msuffix = this->mprefix;
		return (* this);
	}
	while (* prefix != (char) (0))
	{
		* this->mprefix++ = * prefix++;
	}
	while (* middle != (char) (0))
	{
		* this->mprefix++ = * middle++;
	}
	while (* suffix != (char) (0))
	{
		* this->mprefix++ = * suffix++;
	}
	* this->mprefix = (char) (0);
	this->msuffix = this->mprefix;
	return (* this);
}

/*====================================================================*
 *
 *   bool member (char const *string, char c);
 *
 *   return true if charcter c is in string; NUL always returns false;
 *
 *--------------------------------------------------------------------*/

bool ocontext::member (char const * string, char c)

{
	while (* string != (char) (0))
	{
		if (* string++ == c)
		{
			return (true);
		}
	}
	return (false);
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



