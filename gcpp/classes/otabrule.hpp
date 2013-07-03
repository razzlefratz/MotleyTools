/*====================================================================*
 *
 *   tabrule.hpp - interface for the tabrule class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef TABRULE_HEADER
#define TABRULE_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

class __declspec (dllexport) tabrule 

{
public:
	tabrule ();
	tabrule (unsigned margin, signed indent);
	virtual~ tabrule ();
	unsigned margin () const;
	unsigned indent () const;
	tabrule & clear ();
	tabrule & reset ();
	bool tabcol (unsigned column);
	tabrule & tabset (unsigned column, signed indent);
private:
	unsigned mmargin;
	unsigned mindent;
	unsigned mcolumn;
	bool * mruler;
};

#endif

