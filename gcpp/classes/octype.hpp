/*====================================================================*
 *
 *   octype.hpp - interface for the octype class.
 *
 *   the octype class support standard character typing functions
 *   using a transliteration table;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCTYPE_HEADER
#define oCTYPE_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *   class declarations;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) octype 

{
public:
	octype ();
	virtual~ octype ();
	static bool isascii (signed c);
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
	static bool isquote (signed c);
	static bool isblank (signed c);
	static bool isbreak (signed c);
	static bool nobreak (signed c);
	static bool nmtoken (signed c);
	static signed toupper (signed c);
	static signed tolower (signed c);
	static signed tocntrl (signed c);
	static signed toascii (signed c);
	static signed todigit (signed c);
private:
	static const unsigned short mtable [];
};

/*====================================================================*
 *   end declarations;
 *--------------------------------------------------------------------*/

#endif

