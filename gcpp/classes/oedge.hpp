/*====================================================================*
 *
 *   oedge.hpp - interface for the oedge classr;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oEDGE_HEADER
#define oEDGE_HEADER

/*====================================================================*
 *   custom header files; 
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/onode.hpp"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oedge 

{
public:
	oedge (onode * sourcenode, onode * targetnode);
	virtual ~ oedge ();
	onode * source () const;
	onode * target () const;
	char const * title () const;
	signed value () const;
	oedge & value (signed value);
private:
	onode * msource;
	onode * mtarget;
	char const * mtitle;
	signed mvalue;
};

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif

