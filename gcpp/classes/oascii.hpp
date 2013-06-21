/*====================================================================*
 *
 *   oascii.hpp - oascii class declaration;
 *
 *   character classification and conversion; this is a customxed
 *   and customizable implementation of the standard ctype macros 
 *   and library functions;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oASCII_HEADER
#define oASCII_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oascii 

{
public:
	oascii ();
	virtual~ oascii ();

#ifndef WIN32

	static bool isascii (signed c);

#endif

	static bool isalpha (signed c);
	static bool isupper (signed c);
	static bool islower (signed c);
	static bool isdigit (signed c);
	static bool isxdigit (signed c);
	static bool isalnum (signed c);
	static bool ispunct (signed c);
	static bool isspace (signed c);
	static bool isprint (signed c);
	static bool isgraph (signed c);
	static bool iscntrl (signed c);
	static bool isident (signed c);
	static bool isarith (signed c);
	static bool islogic (signed c);
	static bool isgroup (signed c);
	static bool isquote (signed c);
	static bool isblank (signed c);
	static bool ismatch (signed c, signed o);
	static bool isbreak (signed c);
	static bool isbreak (signed c, signed o);
	static bool nobreak (signed c);
	static bool nobreak (signed c, signed o);
	static bool nmtoken (signed c);
	static signed toupper (signed c);
	static signed tolower (signed c);
	static signed tocntrl (signed c);
	static signed todigit (signed c);

#ifndef WIN32

	static signed toascii (signed c);

#endif

private:
	static const unsigned short mtable [];
};


/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif

