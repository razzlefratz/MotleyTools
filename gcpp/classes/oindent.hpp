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
	oindent (void);
	virtual~ oindent (void);
	oindent & margin (char const * string);
	oindent & indent (char const * string);
	oindent & finish (char const * string);
	oindent & record (char const * string);
	char const * margin (void) const;
	char const * indent (void) const;
	char const * finish (void) const;
	char const * record (void) const;
	oindent & space (void);
	oindent & space (signed space);
	oindent & level (void);
	oindent & level (signed level);
	oindent & print (signed level, signed space, char const * string);
	static void newline (char const * margin, char const * indent, signed align);
	static void endline (char const * finish, char const * record, signed space);
	static void print (char const * margin, char const * indent, signed level);
protected:
	signed mlevel;
	signed mspace;
private:
	char * mmargin;
	char * mindent;
	char * mfinish;
	char * mrecord;
};

/*====================================================================*
 *   end interface declaration;
 *--------------------------------------------------------------------*/

#endif

