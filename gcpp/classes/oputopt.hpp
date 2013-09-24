/*====================================================================*
 *
 *   oputopt.hpp - interface for the oputopt class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oPUTOPT_HEADER
#define oPUTOPT_HEADER

/*====================================================================*
 *   custom header files; 
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *   string vector indexes; 
 *--------------------------------------------------------------------*/

#define oPUTOPT_I_OPTIONS 0
#define oPUTOPT_I_COMMAND 1
#define oPUTOPT_I_PURPOSE 2
#define oPUTOPT_I_DETAILS 3

/*====================================================================*
 *   standard strings; 
 *--------------------------------------------------------------------*/

#define oPUTOPT_S_FILTER "[file [file [...]] or [< stdin][> stdout]"
#define oPUTOPT_S_FUNNEL "[file [file [...]] [> stdout]"
#define oPUTOPT_S_SEARCH "[dev:][dir][file[;file...]] [file[;file...]] [>stdout]"
#define oPUTOPT_S_DIVINE "[> stdout]"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oputopt

{
public: 
	oputopt ();
	virtual ~ oputopt ();
	oputopt & chkopt (char const * optv [], char const * options);
	oputopt & putopt (char const * optv []);
	oputopt & putopt (char const * optv [], signed exitcode);
protected: 
private: 
};

#endif



