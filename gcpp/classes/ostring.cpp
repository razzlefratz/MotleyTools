/*====================================================================*
 *
 *   ostring.cpp - implementation of the ostring class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oSTRING_SOURCE
#define oSTRING_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sys/types.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ostring.hpp"

/*====================================================================*
 *   data initialization;
 *--------------------------------------------------------------------*/

ochrlwr ostring::chrlwr;
ochrupr ostring::chrupr;

/*====================================================================*
 *
 *   const unsigned length () const;
 *
 *   return the current string length;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

const size_t ostring::length () const

{
	return (this->mlength);
}

/*====================================================================*
 *
 *   char const * string () const;
 *
 *   return the current string as a string constant;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * ostring::string () const

{
	return ((char const *) (this->mstring));
}

/*====================================================================*
 *
 *   ostring & string (char const * string);
 *
 *   replace the current string with a new string;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ostring & ostring::string (char const * string)

{
	if (std::strcmp (string, this->mstring))
	{
		delete [] this->mstring;
		this->mlength = std::strlen (string);
		this->mstring = new char [this->mlength +  1];
		std::strcpy (this->mstring, string);
	}
	return (* this);
}

/*====================================================================*
 *
 *   char const * first (size_t count);
 *
 *   return the first count characters of the current string as a
 *   string constant;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * ostring::first (size_t count)

{
	delete [] this->mbuffer;
	if (count > this->mlength)
	{
		count = this->mlength;
	}
	this->mbuffer = new char [count +  1];
	std::strncpy (this->mbuffer, this->mstring, count);
	this->mbuffer [count] = (char) (0);
	return (this->mbuffer);
}

/*====================================================================*
 *
 *   char const * final (size_t count);
 *
 *   return the final (right most) count characters as a string constant;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * ostring::final (size_t count)

{
	delete [] this->mbuffer;
	if (count > this->mlength)
	{
		count = this->mlength;
	}
	this->mbuffer = new char [this->mlength - count +  1];
	std::strncpy (this->mbuffer, this->mstring +  this->mlength - count, count);
	this->mbuffer [count] = (char) (0);
	return (this->mbuffer);
}

/*====================================================================*
 *
 *   char const * operator << (size_t count);
 *
 *   shift the current string count characters to the left;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * ostring::operator << (size_t count)

{
	if (count > this->mlength)
	{
		count = this->mlength;
	}
	delete [] this->mbuffer;
	this->mbuffer = new char [this->mlength - count +  1];
	std::strncpy (this->mbuffer, this->mstring +  count, this->mlength - count);
	this->mbuffer [this->mlength - count] = (char) (0);
	return (this->mbuffer);
}

/*====================================================================*
 *
 *   char const * operator >> (size_t count);
 *
 *   shift the string count characters to the right;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * ostring::operator >> (size_t count)

{
	if (count > this->mlength)
	{
		count = this->mlength;
	}
	delete [] this->mbuffer;
	this->mbuffer = new char [this->mlength - count +  1];
	std::strncpy (this->mbuffer, this->mstring, this->mlength - count);
	this->mbuffer [this->mlength - count] = (char) (0);
	return (this->mbuffer);
}

/*====================================================================*
 *
 *   ostring & operator = (char const * string);
 *
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ostring & ostring::operator = (char const * string)

{
	return (this->string (string));
}

/*====================================================================*
 *
 *   ostring & operator == (char const * string);
 *
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool ostring::operator == (char const * string) const

{
	return (std::strcmp (this->mstring, string) == 0);
}

/*====================================================================*
 *
 *   ostring & operator != (char const * string);
 *
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool ostring::operator != (char const * string) const

{
	return (std::strcmp (this->mstring, string) != 0);
}

/*====================================================================*
 *
 *   ostring & operator <= (char const * string);
 *
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool ostring::operator <= (char const * string) const

{
	return (std::strcmp (this->mstring, string) <= 0);
}

/*====================================================================*
 *
 *   ostring & operator >= (char const * string);
 *
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool ostring::operator >= (char const * string) const

{
	return (std::strcmp (this->mstring, string) >= 0);
}

/*====================================================================*
 *
 *   ostring & operator <= (char const * string);
 *
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool ostring::operator < (char const * string) const

{
	return (std::strcmp (this->mstring, string) < 0);
}

/*====================================================================*
 *
 *   ostring & operator >= (char const * string);
 *
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool ostring::operator > (char const * string) const

{
	return (std::strcmp (this->mstring, string) > 0);
}

/*====================================================================*
 *
 *   bool operator * (char const * charset) const;
 *
 *   return true if string contains only characters from charset;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool ostring::operator * (char const * charset) const

{
	return (this->ischarset (charset));
}

/*====================================================================*
 *
 *   bool ischarset (char const * charset) const;
 *
 *   return true if string contains only characters from charset;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool ostring::ischarset (char const * charset) const

{
	for (unsigned mindex = 0; mindex < this->mlength; ++ mindex)
	{
		if (! std::strchr (charset, this->mstring [mindex]))
		{
			return (false);
		}
	}
	return (true);
}

/*====================================================================*
 *
 *   bool incharset (char const * charset) const;
 *
 *   return true if string contains any characters from charset;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool ostring::incharset (char const * charset) const

{
	for (unsigned mindex = 0; mindex < this->mlength; ++ mindex)
	{
		if (std::strchr (charset, this->mstring [mindex]))
		{
			return (true);
		}
	}
	return (false);
}

/*====================================================================*
 *
 *   ostring & read (char const * filename);
 *
 *   read an entire input stream into the input buffer;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ostring & ostring::read (char const * filename)

{
	if ((filename) && (* filename))
	{
		std::ifstream stream;
		stream.open (filename, std::ios::binary);
		if (stream.good ())
		{
			this->read (& stream);
		}
		stream.close ();
	}
	return (* this);
}

/*====================================================================*
 *
 *   ostring & read ();
 *
 *   read the standard input stream into the input buffer;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ostring & ostring::read ()

{
	std::cin.seekg (0, std::ios::end);
	off_t length = std::cin.tellg ();
	std::cin.seekg (0, std::ios::beg);
	delete [] this->mstring;
	this->mstring = new char [length +  1];
	std::cin.read (this->mstring, length);
	this->mstring [length] = (char) (0);
	this->mlength = length;
	return (* this);
}

/*====================================================================*
 *
 *   ostring & read (ifstream *stream);
 *
 *   read an entire input stream into the input buffer;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ostring & ostring::read (std::ifstream * stream)

{
	stream->seekg (0, std::ios::end);
	off_t length = stream->tellg ();
	stream->seekg (0, std::ios::beg);
	delete [] this->mstring;
	this->mstring = new char [length +  1];
	stream->read (this->mstring, length);
	this->mstring [length] = (char) (0);
	this->mlength = length;
	return (* this);
}

/*====================================================================*
 *
 *   char const * field (size_t start, size_t count);
 *
 *   return up to count characters from the start position as a string
 *   constant;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * ostring::field (size_t start, size_t count)

{
	if (start > this->mlength)
	{
		start = this->mlength;
	}
	if (count > this->mlength - start)
	{
		count = this->mlength - start;
	}
	delete [] this->mbuffer;
	this->mbuffer = new char [count +  1];
	std::strncpy (this->mbuffer, this->mstring +  start, count);
	this->mbuffer [count] = (char) (0);
	return (this->mbuffer);
}

/*====================================================================*
 *
 *   ostring & trim (char const * charset);
 *
 *   remove leading and trailing in charset from string;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ostring & ostring::trim (char const * charset)

{
	char * first = this->mstring;
	char * final = this->mstring +  this->mlength -1;
	while ((first < final) && (std::strchr (charset, * first)))
	{
		first++;
	}
	while ((first < final) && (std::strchr (charset, * final)))
	{
		final--;
	}
	char * field = this->mstring;
	while (first <= final)
	{
		* field++ = * first++;
	}
	* first = (char) (0);
	this->mlength = (size_t) (first - this->mstring);
	return (* this);
}

/*====================================================================*
 *
 *   ostring & enclose (char const * example);
 *
 *   enclose the current string with the first and final characters from
 *   the example string argument;
 *
 *   for example, wrap ("[]") or wrap ("[...]") encloses the current string
 *   in brackets and wrap ("|") or wrap ("||") encloses it in vertical bars;
 *   also, wrap ("/", wrap ("*")) creates a C language comment string;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ostring & ostring::enclose (char const * example)

{
	if ((example) && (* example))
	{
		size_t length = std::strlen (example);
		char * buffer = this->mstring;
		this->mstring = new char [this->mlength +  3];
		this->mstring [0] = example [0];
		std::strcpy (& this->mstring [1], buffer);
		this->mstring [++ this->mlength] = example [length -1];
		this->mstring [++ this->mlength] = (char) (0);
		delete [] buffer;
	}
	return (* this);
}

/*====================================================================*
 *
 *   ostring & prefix (char const * string);
 *
 *   prefix the current string with the character string argument;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ostring & ostring::prefix (char const * string)

{
	char * buffer = this->mstring;
	this->mlength += std::strlen (string);
	this->mstring = new char [this->mlength +  1];
	std::strcpy (this->mstring, string);
	std::strcat (this->mstring, buffer);
	delete [] buffer;
	return (* this);
}

/*====================================================================*
 *
 *   ostring & suffix (char const * string);
 *
 *   suffix the current string with the character string argument;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ostring & ostring::suffix (char const * string)

{
	char * buffer = this->mstring;
	this->mlength += std::strlen (string);
	this->mstring = new char [this->mlength +  1];
	std::strcpy (this->mstring, buffer);
	std::strcat (this->mstring, string);
	delete [] buffer;
	return (* this);
}

/*====================================================================*
 *
 *   ostring & reduce (char const * charset);
 *
 *   replace stings of characters from the charset string argument with
 *   the first character of the charset string argument;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ostring & ostring::reduce (char const * charset)

{
	if ((charset) && (* charset))
	{
		char * sp = this->mstring;
		while (* sp)
		{
			if (std::strchr (charset, * sp))
			{
				* sp = * charset;
			}
			sp++;
		}
	}
	return (* this);
}

/*====================================================================*
 *
 *   ostring & select (char const * charset);
 *
 *   remove characters from the current string if they are not from the
 *   charset string argument;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ostring & ostring::select (char const * charset)

{
	if ((charset) && (* charset))
	{
		char * cp = this->mstring;
		char * sp = this->mstring;
		while ((* cp = * sp++))
		{
			if (std::strchr (charset, * cp))
			{
				cp++;
			}
		}
		this->mlength = (size_t) (cp - this->mstring);
	}
	return (* this);
}

/*====================================================================*
 *
 *   ostring & remove (char const * charset);
 *
 *   remove characters from the current string if they are from the
 *   charset string argument;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ostring & ostring::remove (char const * charset)

{
	if ((charset) && (* charset))
	{
		char * cp = this->mstring;
		char * sp = this->mstring;
		while ((* cp = * sp++))
		{
			if (! std::strchr (charset, * cp))
			{
				cp++;
			}
		}
		this->mlength = (size_t) (cp - this->mstring);
	}
	return (* this);
}

/*====================================================================*
 *
 *   ostring & tolower ();
 *
 *   convert all letters in the current string to lower case;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ostring & ostring::tolower ()

{
	ostring::chrlwr.convert (this->mstring);
	return (* this);
}

/*====================================================================*
 *
 *   ostring & toupper ();
 *
 *   convert all letters in the current string to upper case;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ostring & ostring::toupper ()

{
	ostring::chrupr.convert (this->mstring);
	return (* this);
}

/*====================================================================*
 *
 *   ostring & clear ();
 *
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ostring & ostring::clear ()

{
	delete [] this->mstring;
	this->mstring = new char [1];
	this->mstring [0] = (char) (0);
	this->mlength = 0;
	return (* this);
}

/*====================================================================*
 *
 *   signed compare (register char const * string1, register char const * string2, register const unsigned char ct[])
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

signed ostring::compare (register char const * string1, register char const * string2, register const unsigned char ct [])

{
	if (string1 == string2)
	{
		return (0);
	}
	if (! string1)
	{
		return (-1);
	}
	if (! string2)
	{
		return (+  1);
	}
	while (ct [(unsigned) (* string1)] == ct [(unsigned) (* string2)])
	{
		if (ct [(unsigned) (* string1)] == (char) (0))
		{
			return (0);
		}
		string1++;
		string2++;
	}
	return (ct [(unsigned) (* string1)] < ct [(unsigned) (* string2)]? -1: +  1);
}

/*====================================================================*
 *
 *   ostring::ostring (char const * string, size_t start, size_t count);
 *
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ostring::ostring (char const * string, size_t start, size_t count)

{
	unsigned limit = std::strlen (string);
	if (start > limit)
	{
		start = limit;
	}
	if (count > limit - start)
	{
		count = limit - start;
	}
	this->mlength = count;
	this->mstring = new char [this->mlength +  1];
	std::strncpy (this->mstring, string +  start, count);
	this->mstring [this->mlength] = (char) (0);
}

/*====================================================================*
 *
 *   ostring::ostring (char const * string);
 *
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ostring::ostring (char const * string)

{
	this->mbuffer = new char [1];
	this->mbuffer [0] = (char) (0);
	this->mlength = std::strlen (string);
	this->mstring = new char [this->mlength +  1];
	std::strcpy (this->mstring, string);
}

/*====================================================================*
 *
 *   ostring::ostring ();
 *
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ostring::ostring ()

{
	this->mbuffer = new char [1];
	this->mbuffer [0] = (char) (0);
	this->mstring = new char [1];
	this->mstring [0] = (char) (0);
	this->mlength = 0;
}

/*====================================================================*
 *
 *   ostring::~ostring ();
 *
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ostring::~ ostring ()

{
	delete [] this->mbuffer;
	delete [] this->mstring;
}

/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif



