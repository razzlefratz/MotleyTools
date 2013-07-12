/*====================================================================*
 *
 *   octidy.hpp - octidy class definitions and declarations;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCTIDY_HEADER
#define oCTIDY_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/osource.hpp"
#include "../classes/oindent.hpp"
#include "../classes/oinclude.hpp"
#include "../classes/ocomment.hpp"
#include "../classes/ocexitwords.hpp"

/*====================================================================*
 *   interface declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) octidy:  private osource, public oindent, public oinclude, public ocomment 

{ 
public: 
	octidy (void); 
	virtual ~ octidy (void); 
	signed charlie (signed c); 
	signed atheros (signed c); 
	signed program (signed c); 
	signed statement (signed c); 
	signed context (signed c, char const * charset) const; 
	signed context (signed c, signed o, signed e) const; 
	signed context (signed c, signed e) const; 
	signed context (signed c) const; 
	signed _context (signed c, signed o, signed e) const; 
	signed _context (signed c, signed e) const; 
private: 
	static ocexitwords exitwords; 
}; 

/*====================================================================*
 *   end definitions and declarations;
 *--------------------------------------------------------------------*/

#endif


