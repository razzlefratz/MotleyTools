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
#include "../classes/osession.hpp"
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

class __declspec (dllexport) owebpage: public oindent, private otext

{
public: 
	owebpage (void);
	virtual ~ owebpage (void);
	char const * title (void) const;
	char const * stylesheet (void) const;
	owebpage & title (char const *);
	owebpage & stylesheet (char const *);
	oMetaElement MetaElement;
	oPageLinkElement PrevPageLink;
	oPageLinkElement HomePageLink;
	oPageLinkElement NextPageLink;
	owebpage & PageHeader (void);
	owebpage & BodyHeader (void);
	owebpage & LinkHeader (void);
	owebpage & MarkStart (void);
	owebpage & MarkEnd (void);
	owebpage & LinkFooter (void);
	owebpage & BodyFooter (void);
	owebpage & PageFooter (void);
	owebpage & css2 (void);
private: 
	osession session;
	char * mtitle;
	char * mowner;
	char * mstylesheet;
};

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif



