/*====================================================================*
 *
 *   oHTMLIndex.hpp - declaration of oHTMLIndex class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oHTMLINDEX_HEADER
#define oHTMLINDEX_HEADER

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#include "oSpanElement.hpp"
#include "oAnchorElement.hpp" 
#include "owebpage.hpp"
#include "../classes/owildcard.hpp"
#include "../classes/olist.hpp"
#include "../classes/oitem.hpp"

/*====================================================================*
 *   class constants;
 *--------------------------------------------------------------------*/

#define oHTMLINDEX_CLASS "index"

/*====================================================================*
 *   begin declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oHTMLIndex 

{
public:
	oHTMLIndex ();
	virtual~ oHTMLIndex ();
	oHTMLIndex & IndexTitle (char const *);
	oHTMLIndex & IndexStyle (char const *);
	char const * IndexTitle () const;
	char const * IndexStyle () const;
	oHTMLIndex & anchor ();
	oHTMLIndex & include (char const * filename);
	oHTMLIndex & collect (char const * pathname, char const * wildcard);
	oHTMLIndex & publish (unsigned count);
private:
	oAnchorElement manchor;
	owebpage mwebpage;
	owildcard mwildcard;
	oindent mindent;
	olist mlist;
	oitem * mitem;
	signed mlevel;
	signed mspace;
};


/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif

