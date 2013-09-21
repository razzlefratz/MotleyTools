/*====================================================================*
 *
 *   oputoptv.hpp - interface for the oputoptv class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oPUTOPTV_HEADER
#define oPUTOPTV_HEADER

/*====================================================================*
 *   custom header files; 
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *   string vector indexes; 
 *--------------------------------------------------------------------*/

#define oPUTOPTV_I_OPTIONS 0
#define oPUTOPTV_I_COMMAND 1
#define oPUTOPTV_I_PROGRAM 2
#define oPUTOPTV_I_DETAILS 3

/*====================================================================*
 *   standard strings; 
 *--------------------------------------------------------------------*/

#define oPUTOPTV_S_DEVICE "[device] [device] [...] [> stdout]"
#define oPUTOPTV_S_FILTER "[file] [file] [...] or [< stdin] [> stdout]"
#define oPUTOPTV_S_FUNNEL "[file] [file] [...] [> stdout]"
#define oPUTOPTV_S_SEARCH "[dev:][dir][file[;file...]] [file[;file...]] [>stdout]"
#define oPUTOPTV_S_DIVINE "[> stdout]"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#ifndef LITERAL
#define MONIKER(x) #x
#define LITERAL(x) MONIKER(x)
#endif

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oputoptv 

{
public:
	oputoptv ();
	virtual ~ oputoptv ();
	oputoptv & chkoptv (char const * optv []);
	oputoptv & putoptv (char const * optv []);
	oputoptv & putoptv (char const * optv [], signed exitcode);
};

#endif

