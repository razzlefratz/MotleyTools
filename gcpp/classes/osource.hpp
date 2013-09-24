/*====================================================================*
 *
 *   osource.hpp - osource class declaration;     
 *
 *   the osource class implements a range of test scanning primatives
 *   used to format C, C++, PHP, HTML, XML and other forms of source
 *   code by inspecting the punctuation and manipulating supprounding
 *   white space;
 *
 *   additions to this class MUST be independent of language keywords
 *   and constructs; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oSOURCE_HEADER
#define oSOURCE_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *   interface declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) osource

{
public: 
	osource ();
	virtual ~ osource ();
	static signed context (signed c, char const * charset);
	static signed content (signed c, signed o, signed e);
	static signed context (signed c, signed o, signed e);
	static signed connect (signed c, signed o, signed e);
	static signed command (signed c, signed e);
	static signed content (signed c, signed e);
	static signed context (signed c, signed e);
	static signed literal (signed c, signed e);
	static signed consume (signed c);
	static signed context (signed c);
	static signed command (signed c);
	static signed literal (signed c);
	static signed comment (signed c);
	static signed moniker (signed c);
	static signed numeric (signed c);
	static signed operate (signed c);
	static signed terminate (signed c);
	static signed escaped (signed c);
	static signed _context (signed c, signed o, signed e);
	static signed _content (signed c, signed o, signed e);
	static signed _context (signed c, signed e);
	static signed _command (signed c, signed e);
	static signed _literal (signed c, signed e);
	static signed _content (signed c, signed e);
	static signed _comment (signed c);
	static signed skip (signed c, signed o, signed e);
	static signed keep (signed c, signed o, signed e);
	static signed peek (signed c);
	static signed span (signed c);
	static signed find (signed c);
	static signed keep (signed c);
	static signed skip (signed c);
};

/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif



