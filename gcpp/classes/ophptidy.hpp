/*====================================================================*
 *
 *   ophptidy.hpp - class declaration for ophptidy class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oPHPTIDY_HEADER
#define oPHPTIDY_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/ocollect.hpp"
#include "../classes/oindent.hpp"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) ophptidy: public ocollect, public oindent 

{
public:
	ophptidy ();
	virtual~ ophptidy ();
	signed page (signed c);
	signed statement (signed c, signed level, signed space);
	signed program (signed c);
	signed context (signed c, char const * charset);
	signed context (signed c, signed o, signed e);
	signed context (signed c, signed e);
	signed context (signed c);
	signed inner_context (signed c, signed o, signed e);
	signed inner_context (signed c, signed e);
	signed find (signed c);
};

#endif

/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

