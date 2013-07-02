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
#include "../classes/ocgotowords.hpp"
#include "../classes/ocexitwords.hpp"

/*====================================================================*
 *   interface declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) octidy: public osource, public oindent, public oinclude, public ocomment 

{
public:
	octidy ();
	virtual~ octidy ();
	signed charlie (signed c);
	signed atheros (signed c);
	signed program (signed c);
	signed statement (signed c);
	signed preamble (signed c, signed e);
	signed context (signed c, char const * charset) const;
	signed context (signed c, signed o, signed e) const;
	signed context (signed c, signed e) const;
	signed context (signed c) const;
	signed comment (signed c) const;
	signed escaped (signed c) const;
	signed _context (signed c, signed o, signed e) const;
	signed _context (signed c, signed e) const;
	signed find (signed c) const;
private:
	static ocgotowords gotowords;
	static ocexitwords exitwords;
};

/*====================================================================*
 *   end definitions and declarations;
 *--------------------------------------------------------------------*/

#endif

