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
 *   char const *owebpage::title() const;
 *
 *   return the page title as a constant string;
 *
 *--------------------------------------------------------------------*/

char const * owebpage::title () const 

{
	return (this->mtitle);
}


/*====================================================================*
 * 
 *   owebpage & owebpage::title(char const * string) 
 *
 *   replace current title with the constant string argument only
 *   if they differ;
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::title (char const * string) 

{
	this->mtitle = otext::replace (this->mtitle, string);
	return (* this);
}


/*====================================================================*
 * 
 *   char const *owebpage::stylesheet() const;
 *
 *
 *--------------------------------------------------------------------*/

char const * owebpage::stylesheet () const 

{
	return (this->mstylesheet);
}


/*====================================================================*
 * 
 *   owebpage & owebpage::stylesheet(char const *stylesheet);
 *
 *   replace the current stylesheet with the constant string argument 
 *   only if they differ;
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::stylesheet (char const * stylesheet) 

{
	this->mstylesheet = otext::replace (this->mstylesheet, stylesheet);
	return (* this);
}


/*====================================================================*
 *
 *   owebpage & owebpage::level (signed);
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::level (signed level) 

{
	this->mlevel = level;
	return (* this);
}


signed owebpage::level () const 

{
	return (this->mlevel);
}


/*====================================================================*
 * 
 *   owebpage &owebpage::topPage ();
 *
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::topPage () 

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
 *   owebpage &owebpage::header();
 *
 *   print the page header;
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::header () 

{
	this->mindent->print (this->mlevel++, this->mspace, "<div class='header'>");
	this->mindent->print (this->mlevel--, this->mspace, "</div>");
	return (* this);
}


/*====================================================================*
 *   
 *   owebpage &owebpage::topLink();
 *
 *   print the upper link division containing PREV, HOME and NEXT links;
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::topLink () 

{
	this->mindent->print (this->mlevel++, this->mspace, "<div class='toplink'>");

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
 *   owebpage &owebpage::topMark();
 *
 *   print a content prefix tag;
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::topMark () 

{
	this->mindent->print (0, this->mspace, "<!-- BEGIN CONTENT -->");
	return (* this);
}


/*====================================================================*
 *   
 *   owebpage &owebpage::botMark();
 *
 *   print a content suffix tag;
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::botMark () 

{
	this->mindent->print (0, this->mspace, "<!-- END CONTENT -->");
	return (* this);
}


/*====================================================================*
 *   
 *   owebpage &owebpage::botLink(FILE *fp);
 *
 *   print the lower link division containing PREV, HOME and NEXT links;
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::botLink () 

{
	this->mindent->print (this->mlevel++, this->mspace, "<div class='botlink'>");

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
 *   owebpage &owebpage::footer();
 *
 *   print the page footer; the footer identifies the source and data of
 *   publication plus other information; 
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::footer () 

{
	char buffer [200];
	owebpage::session.strfwhat (buffer, sizeof (buffer), "Published");
	this->mindent->print (this->mlevel++, this->mspace, "<div class='footer'>");
	this->mindent->print (this->mlevel, this->mspace, this->mowner);
	this->mindent->print (this->mlevel, this->mspace, "<br/>");
	this->mindent->print (this->mlevel, this->mspace, buffer);
	this->mindent->print (this->mlevel--, this->mspace, "</div>");
	return (* this);
}


/*====================================================================*
 *
 *   owebpage &owebpage::botPage ();
 *
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::botPage () 

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
	this->mtitle = otext::save ("untitled");
	this->mstylesheet = otext::save ("http://www.cmassoc.net/styles/cmassoc.css");
	this->mowner = otext::save ("Courtesy of <a href='mailto:cmaier@cmassoc.net'>Charles Maier Assocoiates Limited</a>, The Motley Tools Folks, Nashua NH, USA");
	owebpage::PrevPageLink.name ("PREV").link ("Index", "index.html");
	owebpage::HomePageLink.name ("HOME").link ("Index", "index.html");
	owebpage::NextPageLink.name ("NEXT").link ("Index", "index.html");
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

