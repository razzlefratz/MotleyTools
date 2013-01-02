/*====================================================================*
 *
 *   oattribute.hpp - oattribute class declaration;
 *
 *   this object implements a generic markup language attribute 
 *   having a name and a text property; the name property is read
 *   only but the text property is read and write;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oATTRIBUTE_HEADER
#define oATTRIBUTE_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstdio>

/*====================================================================*
 *  custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/otext.hpp"

/*====================================================================*
 *   interface declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oattribute: private otext 

{
public:
	oattribute (char const * label);
	oattribute (char const * label, char const * value);
	virtual ~ oattribute ();
	char const * label () const;
	char const * value () const;
	oattribute & value (char const * string);
	oattribute & value (unsigned number);
	oattribute & value (unsigned number, unsigned digits);
	oattribute & write ();
private:
	static char const *mspace;
	static char const *mequal;
	static char const *mquote;
	static char const *mcomma;
	char *mlabel;
	char *mvalue;
};


/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif

