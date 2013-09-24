/*====================================================================*
 *
 *   owebpage.cpp - definition of the owebpage class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oWEBPAGE_SOURCE
#define oWEBPAGE_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <ctime>
#include <cstdlib>
#include <cstring>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/owebpage.hpp"

/*====================================================================*
 *   data initialization; 
 *--------------------------------------------------------------------*/

osession session;

/*====================================================================*
 * 
 *   char const * title (void) const;
 *
 *   return the page title as a constant string;
 *
 *--------------------------------------------------------------------*/

char const * owebpage::title (void) const

{
	return (this->mtitle);
}

/*====================================================================*
 * 
 *   owebpage & title (char const * title) 
 *
 *   replace current title with another if they differ;
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::title (char const * title)

{
	this->mtitle = otext::replace (this->mtitle, title);
	return (* this);
}

/*====================================================================*
 * 
 *   char const * stylesheet (void) const;
 *
 *   return the stylesheet url as a constant character string;
 *
 *--------------------------------------------------------------------*/

char const * owebpage::stylesheet (void) const

{
	return (this->mstylesheet);
}

/*====================================================================*
 * 
 *   owebpage & stylesheet (char const * stylesheet);
 *
 *   replace the current stylesheet url with another if they differ;
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::stylesheet (char const * stylesheet)

{
	this->mstylesheet = otext::replace (this->mstylesheet, stylesheet);
	return (* this);
}

/*====================================================================*
 *
 *   void css2 (void);
 *   
 *   print a compatible CSS stylesheet on stdout so that element and
 *   property names match HTML output;
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::css2 (void)

{
	std::cout << "a:hover { text-decoration: underline; }" << std::endl;
	std::cout << "a { text-decoration: none; }" << std::endl;
	std::cout << "a:link { color: navy; }" << std::endl;
	std::cout << "a:active { }" << std::endl;
	std::cout << "a:visited { color: maroon; }" << std::endl;
	std::cout << "body { background:white; color:black; font:normal 12pt courier; margin: 10px 20px 10px 20px; }" << std::endl;
	std::cout << "pre  { background:white; color:black; font:normal 12pt courier; margin: 10px 20px 10px 20px; }" << std::endl;
	std::cout << "div.bodyheader { margin: 10px 10px 10px 10px; test-align: center; }" << std::endl;
	std::cout << "div.linkheader { margin: 10px 10px 10px 10px; text-align: left; }" << std::endl;
	std::cout << "div.linkfooter { margin: 10px 10px 10px 10px; text-align: right; }" << std::endl;
	std::cout << "div.bodyfooter { margin: 10px 10px 10px 10px; text-align: center; }" << std::endl;
	return (* this);
}

/*====================================================================*
 * 
 *   owebpage & PageHeader (void);
 *
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::PageHeader (void)

{
	owebpage::print (this->mlevel, this->mspace, "<?xml version='1.0' encoding='iso-8859-1'?>");
	owebpage::print (this->mlevel, this->mspace, "<!DOCTYPE HTML PUBLIC '//W3C//DTD XHTML 1.0 Transitional//EN'>");
	owebpage::print (this->mlevel++, this->mspace, "<html xmlns='http://www.w3.org/1999/xhtml'>");
	owebpage::print (this->mlevel++, this->mspace, "<head>");
	owebpage::print (this->mlevel++, this->mspace, "<title>");
	owebpage::print (this->mlevel, this->mspace, this->mtitle);
	owebpage::print (this->mlevel--, this->mspace, "</title>");
	owebpage::MetaElement.Contents ("robots", "noindex,nofollow").EmptyTag (this->mlevel, this->mspace);
	owebpage::MetaElement.Contents ("author", "charles maier").EmptyTag (this->mlevel, this->mspace);
	owebpage::MetaElement.Contents ("generator", "Motley Tools").EmptyTag (this->mlevel, this->mspace);
	owebpage::MetaElement.Contents ("keywords", "peace, love, beauty, truth").EmptyTag (this->mlevel, this->mspace);
	owebpage::print (this->mlevel, 0, "<link href='");
	owebpage::print (0, 0, this->mstylesheet);
	owebpage::print (0, this->mspace, "' rel='stylesheet' type='text/css'/>");
	owebpage::print (this->mlevel--, this->mspace, "</head>");
	owebpage::print (this->mlevel++, this->mspace, "<body>");
	return (* this);
}

/*====================================================================*
 *   
 *   owebpage & BodyHeader (void);
 *
 *   print the page header;
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::BodyHeader (void)

{
	owebpage::print (this->mlevel++, this->mspace, "<div class='" oWEBPAGE_BODY_HEADER_CLASS "'>");
	owebpage::print (this->mlevel--, this->mspace, "</div>");
	return (* this);
}

/*====================================================================*
 *   
 *   owebpage & LinkHeader (void);
 *
 *   print the upper link division containing PREV, HOME and NEXT links;
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::LinkHeader (void)

{
	owebpage::print (this->mlevel++, this->mspace, "<div class='" oWEBPAGE_LINK_HEADER_CLASS "'>");
	owebpage::newline ();
	owebpage::PrevPageLink.write ();
	owebpage::endline ();
	owebpage::newline ();
	owebpage::HomePageLink.write ();
	owebpage::endline ();
	owebpage::newline ();
	owebpage::NextPageLink.write ();
	owebpage::endline ();
	owebpage::print (this->mlevel--, this->mspace, "</div>");
	return (* this);
}

/*====================================================================*
 *   
 *   owebpage & MarkStart (void);
 *
 *   print a content prefix tag;
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::MarkStart (void)

{
	owebpage::print (0, this->mspace, "<!-- BEGIN CONTENT -->");
	return (* this);
}

/*====================================================================*
 *   
 *   owebpage & MarkEnd (void);
 *
 *   print a content suffix tag;
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::MarkEnd (void)

{
	owebpage::print (0, this->mspace, "<!-- END CONTENT -->");
	return (* this);
}

/*====================================================================*
 *   
 *   owebpage & LinkFooter (void);
 *
 *   print the lower link division containing PREV, HOME and NEXT links;
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::LinkFooter (void)

{
	owebpage::print (this->mlevel++, this->mspace, "<div class='" oWEBPAGE_LINK_FOOTER_CLASS "'>");
	owebpage::newline ();
	owebpage::PrevPageLink.write ();
	owebpage::endline ();
	owebpage::newline ();
	owebpage::HomePageLink.write ();
	owebpage::endline ();
	owebpage::newline ();
	owebpage::NextPageLink.write ();
	owebpage::endline ();
	owebpage::print (this->mlevel--, this->mspace, "</div>");
	return (* this);
}

/*====================================================================*
 *   
 *   owebpage & BodyFooter (void);
 *
 *   print the page footer; the footer identifies the source and data of
 *   publication plus other information; 
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::BodyFooter (void)

{
	char buffer [512];
	owebpage::session.strfwhat (buffer, sizeof (buffer), "Published");
	owebpage::print (this->mlevel++, this->mspace, "<div class='" oWEBPAGE_BODY_FOOTER_CLASS "'>");

// owebpage::print (this->mlevel, this->mspace, this->mowner);

	owebpage::print (this->mlevel, this->mspace, "<br/>");
	owebpage::print (this->mlevel, this->mspace, buffer);
	owebpage::print (this->mlevel--, this->mspace, "</div>");
	return (* this);
}

/*====================================================================*
 *
 *   owebpage & PageFooter (void);
 *
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::PageFooter (void)

{
	owebpage::print (this->mlevel--, this->mspace, "</body>");
	owebpage::print (this->mlevel--, this->mspace, "</html>");
	return (* this);
}

/*====================================================================*
 *
 *   owebpage ();
 *   
 *   
 *--------------------------------------------------------------------*/

owebpage::owebpage (void)

{
	this->mtitle = otext::save (oWEBPAGE_PAGE_TITLE);
	this->mstylesheet = otext::save (oWEBPAGE_PAGE_STYLE);
	this->mowner = otext::save ("Courtesy of <a href='mailto:cmaier@cmassoc.net'>Charles Maier Associates Limited</a>, The Motley Tools Folks, Nashua NH, USA");
	owebpage::PrevPageLink.name ("PREV").link (oWEBPAGE_LINK_PREV_NAME, oWEBPAGE_LINK_PREV_PAGE);
	owebpage::HomePageLink.name ("HOME").link (oWEBPAGE_LINK_HOME_NAME, oWEBPAGE_LINK_HOME_PAGE);
	owebpage::NextPageLink.name ("NEXT").link (oWEBPAGE_LINK_NEXT_NAME, oWEBPAGE_LINK_NEXT_PAGE);
	return;
}

/*====================================================================*
 *
 *   ~owebpage (void);
 *   
 *   
 *--------------------------------------------------------------------*/

owebpage::~ owebpage (void)

{
	delete [] this->mtitle;
	delete [] this->mstylesheet;
	delete [] this->mowner;
	return;
}

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif



