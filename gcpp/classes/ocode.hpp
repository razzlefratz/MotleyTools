/*====================================================================*
 *
 *   ocode.hpp - declaration of ocode class;
 *
 *   this object implements a generic means of storing information by
 *   name and classification; it is used by the olist, oheap, oroster, 
 *   oglossary and ocatalog oject classes; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCODE_HEADER
#define oCODE_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/otypes.hpp"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec(dllexport) ocode

{
public: 
	ocode ();
	virtual ~ ocode();
	char const * label(signed value, char const * label) const;
	signed value(char const * label, signed value) const;
protected: 
	const struct _code_ * mtable;
	unsigned mcount;
private: 
	static const struct _code_ table[];
	static const unsigned count;
	char const * mlabel;
	signed mvalue;
};

/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif



