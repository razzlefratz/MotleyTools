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
 *   begin declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oHTMLIndex 

{
public:
	oHTMLIndex ();
	virtual~ oHTMLIndex ();
	oHTMLIndex & title (char const * title);
	oHTMLIndex & stylesheet (char const * stylesheet);
	char const * title () const;
	char const * stylesheet () const;
	oHTMLIndex & include (char const * filename);
	oHTMLIndex & collect (char const * pathname, char const * wildcard);
	oHTMLIndex & publish (unsigned count);
private:
	oSpanElement mspan;
	oAnchorElement mlink;
	owebpage mwebpage;
	owildcard mwildcard;
	oindent mindent;
	olist mlist;
	oitem * mitem;
	signed mlevel;
};


/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif

