/*====================================================================*
 *
 *   oprogram.hpp - oprogram class declaration;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oPROGRAM_HEADER
#define oPROGRAM_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/oindent.hpp"
#include "../classes/ocollect.hpp"

/*====================================================================*
 *   interface declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oprogram: public oindent, public ocollect 

{
public:
	oprogram ();
	virtual ~ oprogram ();
	signed context (signed c, char const * charset) const;
	signed context (signed c, signed o, signed e) const;
	signed requote (signed c, signed o, signed e) const;
	signed context (signed c, signed e) const;
	signed context (signed c) const;
	signed comment (signed c) const;
	signed moniker (signed c) const;
	signed inner_context (signed c, signed o, signed e) const;
	signed inner_context (signed c, signed e) const;
	signed find (signed c) const;
private:
};


/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif 

