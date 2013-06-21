/*====================================================================*
 *
 *   oindent.hpp - interface for the oindent class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oINDENT_HEADER
#define oINDENT_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *   class constants;
 *--------------------------------------------------------------------*/

#define oINDENT_MARGIN ""
#define oINDENT_INDENT "\t"
#define oINDENT_FINISH ""
#define oINDENT_RECORD "\n"

/*====================================================================*
 *   class interface;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oindent 

{
public:
	oindent ();
	virtual~ oindent ();
	oindent & margin (char const * string);
	oindent & indent (char const * string);
	oindent & finish (char const * string);
	oindent & record (char const * string);
	char const * margin () const;
	char const * indent () const;
	char const * finish () const;
	char const * record () const;
	oindent & space ();
	oindent & space (signed space);
	oindent & level ();
	oindent & level (signed level);
	oindent & print (signed level, signed space, char const * string);
	static void newline (char const * margin, char const * indent, signed align);
	static void endline (char const * finish, char const * record, signed space);
	static void print (char const * prefix, char const * suffix, signed count);
private:
	unsigned mspace;
	unsigned mlevel;
	char * mmargin;
	char * mindent;
	char * mfinish;
	char * mrecord;
};


/*====================================================================*
 *   end interface declaration;
 *--------------------------------------------------------------------*/

#endif

