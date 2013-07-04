/*====================================================================*
 *
 *   omacro.hpp - interface for the omacro class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oMACRO_HEADER
#define oMACRO_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include <cstdio>

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/osymbol.hpp"
#include "../classes/oscantext.hpp"
#include "../classes/oflagword.hpp"

/*====================================================================*
 *   class constants;
 *--------------------------------------------------------------------*/

#define oMACRO_SYMBOL_LENGTH 10
#define oMACRO_STRING_LENGTH 255

#define oMACRO_B_DEFINE (1 << 0)
#define oMACRO_B_EXPAND (1 << 1)

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) omacro: public oflagword 

{
public:
	omacro ();
	virtual ~ omacro ();
	bool defined (char const * symbol) const;
	char const * expand (char const * string);
	omacro & define (char const * string);
	omacro & revert (char const * symbol);
	omacro & enumerate (char const * string);
	omacro & clear ();
private:
	char const * argument (unsigned number) const;
	omacro & append (char const * string);
	osymbol * mfunction;
	osymbol * margument;
	unsigned mlength;
	unsigned mextent;
	char * mbuffer;
	static char const msymbol;
	static char const mprefix;
	static char const msuffix;
};

/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif

