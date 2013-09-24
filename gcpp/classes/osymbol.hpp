/*====================================================================*
 *
 *   osymbol.hpp - interface for the osymbol class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oSYMBOL_HEADER
#define oSYMBOL_HEADER

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/oqueue.hpp"
#include "../classes/otext.hpp"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

class __declspec(dllexport) osymbol: private otext

{
public: 
	osymbol (char const * symbol);
	osymbol (char const * symbol, char const * string);
	virtual ~ osymbol();
	bool defined(char const * symbol) const;
	char const * expand(char const * symbol) const;
	char const * lookup(char const * symbol) const;
	osymbol & define(char const * symbol, char const * string);
	osymbol & revert(char const * symbol);
	osymbol & enumerate();
	osymbol & print();
	osymbol & clear();
private: 
	const osymbol * node(char const * symbol) const;
	osymbol * mprior;
	osymbol * mafter;
	oqueue * mqueue;
};

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif



