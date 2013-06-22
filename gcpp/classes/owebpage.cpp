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

oenviron session;

/*====================================================================*
 *
 *   owebpage & level (signed);
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::level (signed level) 

{
	this->mlevel = level;
	return (* this);
}

/*====================================================================*
 *
 *   signed level () const;
 *
 *--------------------------------------------------------------------*/

signed owebpage::level () const 

{
	return (this->mlevel);
}

/*====================================================================*
 * 
 *   char const * PageStyle () const;
 *
 *   return the stylesheet as a constant character string;
 *
 *--------------------------------------------------------------------*/

char const * owebpage::PageStyle () const 

{
	return (this->mstylesheet);
}

/*====================================================================*
 * 
 *   owebpage & PageStyle (char const * stylesheet);
 *
 *   replace the current stylesheet with the constant string argument 
 *   only if they differ;
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::PageStyle (char const * stylesheet) 

{
	this->mstylesheet = otext::replace (this->mstylesheet, stylesheet);
	return (* this);
}

/*====================================================================*
 * 
 *   char const * PageTitle () const;
 *
 *   return the page title as a constant string;
 *
 *--------------------------------------------------------------------*/

char const * owebpage::PageTitle () const 

{
	return (this->mtitle);
}

/*====================================================================*
 * 
 *   owebpage & PageTitle (char const * string) 
 *
 *   replace current title with the constant string argument only
 *   if they differ;
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::PageTitle (char const * string) 

{
	this->mtitle = otext::replace (this->mtitle, string);
	return (* this);
}

/*====================================================================*
 * 
 *   owebpage & PageHeader ();
 *
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::PageHeader () 

{
	this->mindent->print (this->mlevel, this->mspace, "<?xml version='1.0' encoding='iso-8859-1'?>");
	this->mindent->print (this->mlevel, this->mspace, "<!DOCTYPE HTML PUBLIC '//W3C//DTD XHTML 1.0 Transitional//EN'>");
	this->mindent->print (this->mlevel++, this->mspace, "<html xmlns='http://www.w3.org/1999/xhtml'>");
	this->mindent->print (this->mlevel++, this->mspace, "<head>");
	this->mindent->print (this->mlevel++, this->mspace, "<title>");
	this->mindent->print (this->mlevel, this->mspace, this->mtitle);
	this->mindent->print (this->mlevel--, this->mspace, "</title>");
	owebpage::MetaElement.EmptyTag (this->mlevel, this->mspace);
	owebpage::MetaElement.Contents ("robots", "noindex,nofollow").EmptyTag (this->mlevel, this->mspace);
	owebpage::MetaElement.Contents ("author", "charles maier").EmptyTag (this->mlevel, this->mspace);
	owebpage::MetaElement.Contents ("generator", "Motley Tools").EmptyTag (this->mlevel, this->mspace);
	owebpage::MetaElement.Contents ("keywords", "peace, love, beauty, truth").EmptyTag (this->mlevel, this->mspace);
	this->mindent->print (this->mlevel, 0, "<link href='");
	this->mindent->print (0, 0, this->mstylesheet);
	this->mindent->print (0, this->mspace, "' rel='stylesheet' type='text/css'/>");
	this->mindent->print (this->mlevel--, this->mspace, "</head>");
	this->mindent->print (this->mlevel++, this->mspace, "<body>");
	return (* this);
}

/*====================================================================*
 *   
 *   owebpage & BodyHeader ();
 *
 *   print the page header;
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::BodyHeader () 

{
	this->mindent->print (this->mlevel++, this->mspace, "<div class='" oWEBPAGE_BODY_HEADER_CLASS "'>");
	this->mindent->print (this->mlevel--, this->mspace, "</div>");
	return (* this);
}

/*====================================================================*
 *   
 *   owebpage & LinkHeader ();
 *
 *   print the upper link division containing PREV, HOME and NEXT links;
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::LinkHeader () 

{
	this->mindent->print (this->mlevel++, this->mspace, "<div class='" oWEBPAGE_LINK_HEADER_CLASS "'>");

#if 0

	this->mindent->print (this->mlevel, this->mspace, owebpage::PrevPageLink.string ());
	this->mindent->print (this->mlevel, this->mspace, owebpage::HomePageLink.string ());
	this->mindent->print (this->mlevel, this->mspace, owebpage::NextPageLink.string ());

#else

	owebpage::PrevPageLink.write ();
	owebpage::HomePageLink.write ();
	owebpage::NextPageLink.write ();

#endif

	this->mindent->print (this->mlevel--, this->mspace, "</div>");
	return (* this);
}

/*====================================================================*
 *   
 *   owebpage & MarkStart ();
 *
 *   print a content prefix tag;
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::MarkStart () 

{
	this->mindent->print (0, this->mspace, "<!-- BEGIN CONTENT -->");
	return (* this);
}

/*====================================================================*
 *   
 *   owebpage & MarkEnd ();
 *
 *   print a content suffix tag;
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::MarkEnd () 

{
	this->mindent->print (0, this->mspace, "<!-- END CONTENT -->");
	return (* this);
}

/*====================================================================*
 *   
 *   owebpage & LinkFooter ();
 *
 *   print the lower link division containing PREV, HOME and NEXT links;
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::LinkFooter () 

{
	this->mindent->print (this->mlevel++, this->mspace, "<div class='" oWEBPAGE_LINK_FOOTER_CLASS "'>");

#if 0

	this->mindent->print (this->mlevel, this->mspace, owebpage::PrevPageLink.string ());
	this->mindent->print (this->mlevel, this->mspace, owebpage::HomePageLink.string ());
	this->mindent->print (this->mlevel, this->mspace, owebpage::NextPageLink.string ());

#else

	owebpage::PrevPageLink.write ();
	owebpage::HomePageLink.write ();
	owebpage::NextPageLink.write ();

#endif

	this->mindent->print (this->mlevel--, this->mspace, "</div>");
	return (* this);
}

/*====================================================================*
 *   
 *   owebpage & BodyFooter ();
 *
 *   print the page footer; the footer identifies the source and data of
 *   publication plus other information; 
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::BodyFooter () 

{
	char buffer [512];
	owebpage::session.strfwhat (buffer, sizeof (buffer), "Published");
	this->mindent->print (this->mlevel++, this->mspace, "<div class='" oWEBPAGE_BODY_FOOTER_CLASS "'>");
	this->mindent->print (this->mlevel, this->mspace, this->mowner);
	this->mindent->print (this->mlevel, this->mspace, "<br/>");
	this->mindent->print (this->mlevel, this->mspace, buffer);
	this->mindent->print (this->mlevel--, this->mspace, "</div>");
	return (* this);
}

/*====================================================================*
 *
 *   owebpage & PageFooter ();
 *
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::PageFooter () 

{
	this->mindent->print (this->mlevel--, this->mspace, "</body>");
	this->mindent->print (this->mlevel--, this->mspace, "</html>");
	return (* this);
}

/*====================================================================*
 *
 *   owebpage ();
 *   
 *   
 *--------------------------------------------------------------------*/

owebpage::owebpage () 

{
	this->mtitle = otext::save (oWEBPAGE_PAGE_TITLE);
	this->mstylesheet = otext::save (oWEBPAGE_PAGE_STYLE);
	this->mowner = otext::save ("Courtesy of <a href='mailto:cmaier@cmassoc.net'>Charles Maier Associates Limited</a>, The Motley Tools Folks, Nashua NH, USA");
	owebpage::PrevPageLink.name ("PREV").link (oWEBPAGE_LINK_PREV_NAME, oWEBPAGE_LINK_PREV_PAGE);
	owebpage::HomePageLink.name ("HOME").link (oWEBPAGE_LINK_HOME_NAME, oWEBPAGE_LINK_HOME_PAGE);
	owebpage::NextPageLink.name ("NEXT").link (oWEBPAGE_LINK_NEXT_NAME, oWEBPAGE_LINK_NEXT_PAGE);
	this->mindent = new oindent ();
	this->mlevel = 0;
	this->mspace = 1;
	return;
}

/*====================================================================*
 *
 *   ~owebpage ();
 *   
 *   
 *--------------------------------------------------------------------*/

owebpage::~owebpage () 

{
	delete []this->mtitle;
	delete []this->mstylesheet;
	delete []this->mowner;
	delete this->mindent;
	return;
}

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif

