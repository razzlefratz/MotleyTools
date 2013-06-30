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
#include "../classes/ocollect.hpp"
#include "../classes/oindent.hpp"
#include "../classes/oinclude.hpp"
#include "../classes/ocomment.hpp"
#include "../classes/ocgotowords.hpp"
#include "../classes/ocexitwords.hpp"

/*====================================================================*
 *   interface declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) octidy: public ocollect, public oindent, public oinclude, public ocomment 

{
public:
	octidy ();
	virtual~ octidy ();
	signed preamble (signed c, signed e);
	signed statement (signed c);
	signed charlie (signed c, signed e);
	signed atheros (signed c, signed e);
	signed program (signed c, signed e);
	signed context (signed c, char const * charset) const;
	signed context (signed c, signed o, signed e) const;
	signed context (signed c, signed e) const;
	signed context (signed c) const;
	signed comment (signed c) const;
	signed escaped (signed c) const;
	signed context_ (signed c, signed o, signed e) const;
	signed context_ (signed c, signed e) const;
	signed find (signed c) const;
private:
	static ocgotowords gotowords;
	static ocexitwords exitwords;
};

/*====================================================================*
 *   end definitions and declarations;
 *--------------------------------------------------------------------*/

#endif

