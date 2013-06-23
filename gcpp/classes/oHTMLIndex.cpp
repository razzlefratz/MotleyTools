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

#include "oHTMLIndex.hpp"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

oAnchorElement manchor;
owebpage mwebpage;
owildcard mwildcard;
oindent mindent;
olist mlist;

/*====================================================================*
 *
 *   oHTMLIndex & IndexTitle (char const * string);
 *
 *   assign the string argument to the page title;
 *
 *--------------------------------------------------------------------*/

oHTMLIndex & oHTMLIndex::IndexTitle (char const * string) 

{
	oHTMLIndex::mwebpage.PageTitle (string);
	return (* this);
}


char const * oHTMLIndex::IndexTitle () const 

{
	return (oHTMLIndex::mwebpage.PageTitle ());
}


/*====================================================================*
 *
 *   oHTMLIndex & IndexStyle (char const * stylesheet);
 *
 *   assign the string argument to the page title;
 *
 *--------------------------------------------------------------------*/

oHTMLIndex & oHTMLIndex::IndexStyle (char const * stylesheet) 

{
	oHTMLIndex::mwebpage.PageStyle (stylesheet);
	return (* this);
}


char const * oHTMLIndex::IndexStyle () const 

{
	return (oHTMLIndex::mwebpage.PageStyle ());
}


/*====================================================================*
 *
 *   oHTMLIndex & oHTMLIndex::include(char const *filename)
 *
 *   include the filename string in the index if not already present;
 *
 *--------------------------------------------------------------------*/

oHTMLIndex & oHTMLIndex::include (char const * filename) 

{
	if (!oHTMLIndex::mlist.item (filename)) 
	{
		oHTMLIndex::mlist.insertitem (new oitem (filename));
	}
	return (* this);
}


/*====================================================================*
 *
 *   oHTMLIndex & oHTMLIndex::collect(char const * pathname, char const * filename);
 *
 *   search the specified folder for files that match the wildcard
 *   filename string; include matching filenames in the index;
 *
 *--------------------------------------------------------------------*/

oHTMLIndex & oHTMLIndex::collect (char const * pathname, char const * filename) 

{
	DIR * dir;
	if ((dir = opendir (pathname)) != (DIR *) (0)) 
	{
		struct dirent * dirent;
		while ((dirent = readdir (dir)) != (struct dirent *)(0)) 
		{
			if (oHTMLIndex::mwildcard.match (dirent->d_name, filename)) 
			{
				this->include (dirent->d_name);
			}
		}
		closedir (dir);
	}
	return (* this);
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

oHTMLIndex & oHTMLIndex::anchor ()
{
	oHTMLIndex::mindent.print (this->mlevel, 0, "");
	oHTMLIndex::manchor.StartTag ();
	std::cout << oHTMLIndex::mitem->name ();
	oHTMLIndex::manchor.EndTag ();
	return (*this);
}

oHTMLIndex & oHTMLIndex::publish (unsigned count) 

{
	size_t index = 0;
	size_t limit = count = (oHTMLIndex::mlist.count () + (count - 1)) / count;
	oHTMLIndex::mwebpage.PageHeader ();
	oHTMLIndex::mwebpage.MarkStart ();
	oHTMLIndex::mindent.print (this->mlevel++, this->mspace, "<h1>");
	oHTMLIndex::mindent.print (this->mlevel, this->mspace, oHTMLIndex::mwebpage.PageTitle ());
	oHTMLIndex::mindent.print (this->mlevel--, this->mspace, "</h1>");
	oHTMLIndex::mindent.print (this->mlevel++, this->mspace, "<table class='" oHTMLINDEX_CLASS "'>");
	oHTMLIndex::mindent.print (this->mlevel++, this->mspace, "<tr class='" oHTMLINDEX_CLASS "'>");
	while (index < limit) 
	{
		oHTMLIndex::mindent.print (this->mlevel++, this->mspace, "<td class='" oHTMLINDEX_CLASS "'>");
		oHTMLIndex::mindent.level (this->mlevel++);
		std::cout << "<ol start='" << index + 1 << "'>";
		oHTMLIndex::mindent.space (1);
		while (index < limit) 
		{
			oHTMLIndex::mitem = oHTMLIndex::mlist.items (index++);
			oHTMLIndex::mindent.print (this->mlevel++, this->mspace, "<li class='" oHTMLINDEX_CLASS "'>");
			oHTMLIndex::mindent.print (this->mlevel, 0, "");
			oHTMLIndex::manchor.CoreAttributes.IdentityAttribute->value (oHTMLIndex::mlist.count ());
			oHTMLIndex::manchor.CoreAttributes.ClassAttribute->value ("index");
			oHTMLIndex::manchor.CoreAttributes.TitleAttribute->value (oHTMLIndex::mitem->name ());
			oHTMLIndex::manchor.LinkAttributes.ReferenceAttribute->value (oHTMLIndex::mitem->name ());
			oHTMLIndex::manchor.StartTag ();
			std::cout << oHTMLIndex::mitem->name ();
			oHTMLIndex::manchor.EndTag ();
			oHTMLIndex::mindent.print (0, this->mspace, "");
			oHTMLIndex::mindent.print (this->mlevel--, this->mspace, "</li>");
		}
		oHTMLIndex::mindent.print (this->mlevel--, this->mspace, "</ol>");
		oHTMLIndex::mindent.print (this->mlevel--, this->mspace, "</td>");
		if ((limit += count) > oHTMLIndex::mlist.count ()) 
		{
			limit = oHTMLIndex::mlist.count ();
		}
	}
	oHTMLIndex::mindent.print (this->mlevel--, this->mspace, "</tr>");
	oHTMLIndex::mindent.print (this->mlevel--, this->mspace, "</table>");
	oHTMLIndex::mwebpage.MarkEnd ();
	oHTMLIndex::mwebpage.BodyFooter ();
	oHTMLIndex::mwebpage.PageFooter ();
	return (* this);
}


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

oHTMLIndex::oHTMLIndex () 

{
	this->mlevel = 0;
	this->mspace = 1;
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

