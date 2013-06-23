/*====================================================================*
 *
 *   odiscard.hpp - odiscard class declaration;
 *
 *   consume and discard segments of well-formed source code;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oDISCARD_HEADER
#define oDISCARD_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *   interface declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) odiscard 

{
public:
	odiscard ();
	virtual~ odiscard ();
	signed context (signed c, char const * charset) const;
	signed context (signed c, signed o, signed e) const;
	signed content (signed c, signed o, signed e) const;
	signed context (signed c, signed e) const;
	signed command (signed c, signed e) const;
	signed literal (signed c, signed e) const;
	signed content (signed c, signed e) const;
	signed context (signed c) const;
	signed command (signed c) const;
	signed literal (signed c) const;
	signed escaped (signed c) const;
	signed comment (signed c) const;
	signed inner_context (signed c, signed o, signed e) const;
	signed inner_content (signed c, signed o, signed e) const;
	signed inner_context (signed c, signed e) const;
	signed inner_literal (signed c, signed e) const;
	signed inner_command (signed c, signed e) const;
	signed inner_content (signed c, signed e) const;
private:
	
};

/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif

