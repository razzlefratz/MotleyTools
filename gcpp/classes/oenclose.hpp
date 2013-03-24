/*====================================================================*
 *
 *   oenclose.hpp - interface for the oenclose class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oENCLOSE_HEADER
#define oENCLOSE_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/ocollect.hpp"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oenclose: private ocollect 

{
public:
	oenclose ();
	virtual ~ oenclose ();
	signed program (signed c, signed e) const;
	signed inner_program (signed c, signed e) const;
	signed condition (signed c) const;
	signed statement (signed c) const;
	signed expression (signed c) const;
private:
};


/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif

