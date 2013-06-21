/*====================================================================*
 *
 *   oblock.cpp - C Language blocker;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef OCBLOCK_HEADER
#define OCBLOCK_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/ocollect.hpp"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) ocblock: private ocollect 

{
public:
	ocblock ();
	virtual~ ocblock ();
	signed program (signed c, signed e);
private:
	signed statement (signed c);
	signed condition (signed c);
};


/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif

