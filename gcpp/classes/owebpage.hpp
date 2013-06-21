/*====================================================================*
 *
 *   owebpage.hpp - declaration of owebpage class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oWEBPAGE_HEADER
#define oWEBPAGE_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstdio>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/oenviron.hpp"
#include "../classes/oindent.hpp"
#include "../classes/otext.hpp"
#include "../classes/oPageLinkElement.hpp"
#include "../classes/oMetaElement.hpp"

/*====================================================================*
 * 
 *--------------------------------------------------------------------*/

class __declspec (dllexport) owebpage: private otext 

{
public:
	owebpage ();
	virtual~ owebpage ();
	char const * title () const;
	char const * stylesheet () const;
	signed level () const;
	owebpage & title (char const * string);
	owebpage & stylesheet (char const * stylesheet);
	owebpage & level (signed level);
	oMetaElement MetaElement;
	oPageLinkElement PrevPageLink;
	oPageLinkElement HomePageLink;
	oPageLinkElement NextPageLink;
	owebpage & topPage ();
	owebpage & header ();
	owebpage & topLink ();
	owebpage & topMark ();
	owebpage & botMark ();
	owebpage & botLink ();
	owebpage & footer ();
	owebpage & botPage ();
private:
	oenviron session;
	oindent * mindent;
	char * mtitle;
	char * mstylesheet;
	char * mowner;
	signed mlevel;
	signed mspace;
};


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

