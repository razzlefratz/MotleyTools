/*====================================================================*
 *
 *   ocstringpp - interface for the ostring class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oSTRING_HEADER
#define oSTRING_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <fstream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/ochrlwr.hpp"
#include "../classes/ochrupr.hpp"

/*====================================================================*
 *   begin declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) ostring 

{
public:
	ostring ();
	ostring (char const * string);
	ostring (char const * string, size_t start, size_t count);
	virtual ~ ostring ();
	const size_t length () const;
	char const * string () const;
	ostring & string (char const * string);
	char const * first (size_t count);
	char const * final (size_t count);
	char const * field (size_t start, size_t count);
	char const * operator << (size_t count);
	char const * operator >> (size_t count);
	ostring & operator = (char const * string);
	bool operator == (char const * string) const;
	bool operator != (char const * string) const;
	bool operator < (char const * string) const;
	bool operator > (char const * string) const;
	bool operator <= (char const * string) const;
	bool operator >= (char const * string) const;
	bool operator * (char const * charset) const;
	bool ischarset (char const * charset) const;
	bool incharset (char const * charset) const;
	ostring & clear ();
	ostring & read (char const * filename);
	ostring & read (std::ifstream * stream);
	ostring & read ();
	ostring & trim (char const * charset);
	ostring & enclose (char const * example);
	ostring & prefix (char const * string);
	ostring & suffix (char const * string);
	ostring & reduce (char const * charset);
	ostring & select (char const * charset);
	ostring & remove (char const * charset);
	ostring & tolower ();
	ostring & toupper ();
	signed strucmp (char const *);
	signed strlcmp (char const *);
	signed compare (char const *, char const *, const unsigned char table []);
private:
	static ochrlwr chrlwr;
	static ochrupr chrupr;
	size_t mlength;
	char * mbuffer;
	char * mstring;
};

/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif

