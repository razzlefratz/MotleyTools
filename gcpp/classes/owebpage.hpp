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
 *   class constants;
 *--------------------------------------------------------------------*/

#define oWEBPAGE_PAGE_TITLE "untitled"
#define oWEBPAGE_PAGE_STYLE "index.css"
#define oWEBPAGE_PAGE_HEADER_CLASS "pageheader"
#define oWEBPAGE_PAGE_FOOTER_CLASS "pagefooter"
#define oWEBPAGE_BODY_HEADER_CLASS "bodyheader"
#define oWEBPAGE_BODY_FOOTER_CLASS "bodyfooter"
#define oWEBPAGE_LINK_HEADER_CLASS "linkheader"
#define oWEBPAGE_LINK_FOOTER_CLASS "linkfooter"
#define oWEBPAGE_LINK_PREV_NAME "Index"
#define oWEBPAGE_LINK_HOME_NAME "Index"
#define oWEBPAGE_LINK_NEXT_NAME "Index"
#define oWEBPAGE_LINK_PREV_PAGE "index.html"
#define oWEBPAGE_LINK_HOME_PAGE "index.html"
#define oWEBPAGE_LINK_NEXT_PAGE "index.html"

/*====================================================================*
 * 
 *--------------------------------------------------------------------*/

class __declspec (dllexport) owebpage: private otext 

{
public:
	owebpage ();
	virtual~ owebpage ();
	char const * PageTitle () const;
	char const * PageStyle () const;
	signed level () const;
	owebpage & level (signed level);
	owebpage & PageTitle (char const * string);
	owebpage & PageStyle (char const * stylesheet);
	oMetaElement MetaElement;
	oPageLinkElement PrevPageLink;
	oPageLinkElement HomePageLink;
	oPageLinkElement NextPageLink;
	owebpage & PageHeader ();
	owebpage & BodyHeader ();
	owebpage & LinkHeader ();
	owebpage & MarkStart ();
	owebpage & MarkEnd ();
	owebpage & LinkFooter ();
	owebpage & BodyFooter ();
	owebpage & PageFooter ();
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

