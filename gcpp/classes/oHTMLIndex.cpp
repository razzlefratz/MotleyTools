/*==========================================================================/
 *
 *   oHTMLIndex.cpp - definition of the oHTMLIndex class;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oHTMLINDEX_SOURCE
#define oHTMLINDEX_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include <cstring>
#include <cstdlib>
#include <iostream>

#include <dirent.h>
#include <math.h>

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#include "../classes/files.h"

#include "oHTMLIndex.hpp"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

oSpanElement mspan;
oAnchorElement mlink;
owebpage mwebpage;
owildcard mwildcard;
oindent mindent;
olist mlist;

/*====================================================================*
 *
 *   oHTMLIndex & oHTMLIndex::title(char const *string);
 *
 *   assign the string argument to the page title;
 *
 *--------------------------------------------------------------------*/

oHTMLIndex & oHTMLIndex::title (char const *string) 

{
	oHTMLIndex::mwebpage.title (string);
	return (*this);
}

char const * oHTMLIndex::title () const 

{
	return (oHTMLIndex::mwebpage.title ());
}


/*====================================================================*
 *
 *   oHTMLIndex & oHTMLIndex::stylesheet(char const *stylesheet);
 *
 *   assign the string argument to the page title;
 *
 *--------------------------------------------------------------------*/

oHTMLIndex & oHTMLIndex::stylesheet (char const *stylesheet) 

{
	oHTMLIndex::mwebpage.stylesheet (stylesheet);
	return (*this);
}

char const * oHTMLIndex::stylesheet () const 

{
	return (oHTMLIndex::mwebpage.stylesheet ());
}


/*====================================================================*
 *
 *   oHTMLIndex & oHTMLIndex::include(char const *filename)
 *
 *   include the filename string in the index if not already present;
 *
 *--------------------------------------------------------------------*/

oHTMLIndex & oHTMLIndex::include (char const *filename) 

{
	if (!oHTMLIndex::mlist.item (filename)) 
	{
		oHTMLIndex::mlist.insertitem (new oitem (filename));
	}
	return (*this);
}


/*====================================================================*
 *
 *   oHTMLIndex & oHTMLIndex::collect(char const *basename, char const *wildcard);
 *
 *   search the specified folder for filenames that match the wildcard
 *   argument string; include matching filenames in the index;
 *
 *--------------------------------------------------------------------*/

oHTMLIndex & oHTMLIndex::collect (char const *pathname, char const *wildcard) 

{
	DIR *dir;
	if ((dir = opendir (pathname)) != (DIR *) (0)) 
	{
		struct dirent *dirent;
		while ((dirent = readdir (dir)) != (struct dirent *)(0)) 
		{
			if (oHTMLIndex::mwildcard.match (dirent->d_name, wildcard)) 
			{
				this->include (dirent->d_name);
			}
		}
		closedir (dir);
	}
	return (*this);
}


/*====================================================================*
 *
 *   oHTMLIndex & oHTMLIndex::publish(char const *filename, unsigned count);
 *
 *   open a C Language source file, read the contents and write an HTML 
 *   page to stdout; the page displays the original source having
 *   comments, keywords, constants, variables and operators highlighed in
 *   various colors for visual effect; selected constants, variable and
 *   filenames may have hyperlinks to companion pages;
 *
 *--------------------------------------------------------------------*/

oHTMLIndex & oHTMLIndex::publish (unsigned count) 

{
	size_t index = 0;
	size_t limit = count = (oHTMLIndex::mlist.count () + (count - 1)) / count;
	oHTMLIndex::mwebpage.topPage ();
	oHTMLIndex::mwebpage.topMark ();
	oHTMLIndex::mindent.print (this->mlevel++, 1, "<h1>");
	oHTMLIndex::mindent.print (this->mlevel, 1, oHTMLIndex::mwebpage.title ());
	oHTMLIndex::mindent.print (this->mlevel--, 1, "</h1>");
	oHTMLIndex::mindent.print (this->mlevel++, 1, "<table class='index'>");
	oHTMLIndex::mindent.print (this->mlevel++, 1, "<tr class='index'>");
	while (index < limit) 
	{
		oHTMLIndex::mindent.print (this->mlevel++, 1, "<td class='index'>");
		oHTMLIndex::mindent.level (this->mlevel++);
		std::cout << "<ol start='" << index + 1 << "'>";
		oHTMLIndex::mindent.space (1);
		while (index < limit) 
		{
			oHTMLIndex::mitem = oHTMLIndex::mlist.items (index++);
			oHTMLIndex::mlink.CoreAttributes.IdentityAttribute->value (index, 1 + (int)(log10 (mlist.count ())));
			oHTMLIndex::mlink.CoreAttributes.ClassAttribute->value ("index");
			oHTMLIndex::mlink.CoreAttributes.TitleAttribute->value (oHTMLIndex::mitem->name ());
			oHTMLIndex::mlink.LinkAttributes.ReferenceAttribute->value (oHTMLIndex::mitem->name ());
			oHTMLIndex::mindent.print (this->mlevel++, 1, "<li class='index'>");

#if 0

			oHTMLIndex::mindent.print (this->mlevel++, 1, oHTMLIndex::mlink.StartTag ());
			oHTMLIndex::mindent.print (this->mlevel, 1, oHTMLIndex::mitem->name ());
			oHTMLIndex::mindent.print (this->mlevel--, 1, oHTMLIndex::mlink.EndTag ());

#else

			oHTMLIndex::mlink.StartTag ();
			oHTMLIndex::mindent.print (this->mlevel, 1, oHTMLIndex::mitem->name ());
			oHTMLIndex::mlink.EndTag ();

#endif

			oHTMLIndex::mindent.print (this->mlevel--, 1, "</li>");
		}
		oHTMLIndex::mindent.print (this->mlevel--, 1, "</ol>");
		oHTMLIndex::mindent.print (this->mlevel--, 1, "</td>");
		if ((limit += count) > oHTMLIndex::mlist.count ()) 
		{
			limit = oHTMLIndex::mlist.count ();
		}
	}
	oHTMLIndex::mindent.print (this->mlevel--, 1, "</tr>");
	oHTMLIndex::mindent.print (this->mlevel--, 1, "</table>");
	oHTMLIndex::mwebpage.botMark ();
	oHTMLIndex::mwebpage.footer ();
	oHTMLIndex::mwebpage.botPage ();
	return (*this);
}


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

oHTMLIndex::oHTMLIndex () 

{
	this->mlevel = 0;
	return;
}

oHTMLIndex::~oHTMLIndex () 

{
	return;
}


/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif

