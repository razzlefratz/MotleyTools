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
#define oINDENT_OFFSET "\t"
#define oINDENT_FINISH ""
#define oINDENT_RECORD "\n"

/*====================================================================*
 *   class interface;
 *--------------------------------------------------------------------*/

class __declspec(dllexport) oindent

{
public: 
	oindent (void);
	virtual ~ oindent(void);
	signed space(void) const;
	signed level(void) const;
	char const * margin(void) const;
	char const * offset(void) const;
	char const * finish(void) const;
	char const * record(void) const;
	oindent & increment(void);
	oindent & decrement(void);
	oindent & space(signed space);
	oindent & level(signed level);
	oindent & margin(char const * string);
	oindent & offset(char const * string);
	oindent & finish(char const * string);
	oindent & record(char const * string);
	oindent & endline();
	oindent & endline(signed space);
	oindent & endline(char const * finish, char const * record, signed space);
	oindent & newline();
	oindent & newline(signed level);
	oindent & newline(char const * margin, char const * offset, signed level);
	oindent & print(void);
	oindent & print(char const * string);
	oindent & print(signed level, signed space, char const * string);
	static void print(char const * prefix, char const * suffix, signed count);
protected: 
	signed mlevel;
	signed mspace;
private: 
	char * mmargin;
	char * moffset;
	char * mfinish;
	char * mrecord;
};

/*====================================================================*
 *   end interface declaration;
 *--------------------------------------------------------------------*/

#endif



