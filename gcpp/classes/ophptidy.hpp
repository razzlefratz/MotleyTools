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
#include "../classes/osource.hpp"
#include "../classes/oindent.hpp"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec(dllexport) ophptidy: public osource, public oindent

{
public: 
	ophptidy (void);
	virtual ~ ophptidy(void);
	signed page(signed c);
	signed statement(signed c);
	signed program(signed c);
	signed context(signed c, char const * charset) const;
	signed context(signed c, signed o, signed e) const;
	signed context(signed c, signed e) const;
	signed context(signed c) const;
	signed _context(signed c, signed o, signed e) const;
	signed _context(signed c, signed e) const;
};

/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif



