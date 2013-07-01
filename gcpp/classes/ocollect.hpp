/*====================================================================*
 *
 *   ocollect.hpp - ocollect class declaration;     
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCOLLECT_HEADER
#define oCOLLECT_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *   interface declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) ocollect 

{
public:
	ocollect ();
	virtual~ ocollect ();
	signed context (signed c, char const * charset) const;
	signed context (signed c, signed o, signed e) const;
	signed content (signed c, signed o, signed e) const;
	signed requote (signed c, signed o, signed e) const;
	signed context (signed c, signed e) const;
	signed command (signed c, signed e) const;
	signed literal (signed c, signed e) const;
	signed content (signed c, signed e) const;
	signed context (signed c) const;
	signed command (signed c) const;
	signed literal (signed c) const;
	signed escaped (signed c) const;
	signed comment (signed c) const;
	signed _context (signed c, signed o, signed e) const;
	signed _content (signed c, signed o, signed e) const;
	signed _context (signed c, signed e) const;
	signed _command (signed c, signed e) const;
	signed _literal (signed c, signed e) const;
	signed _content (signed c, signed e) const;
	signed join (signed c) const;
	signed find (signed c) const;
	signed feed (signed c) const;
private:
	
};

/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif

