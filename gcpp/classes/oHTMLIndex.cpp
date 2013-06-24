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
#include <fstream>
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
owildcard mwildcard;
olist mlist;

/*====================================================================*
 *
 *   void css2 (void);
 *   
 *   print a compatible CSS stylesheet on stdout so that element and
 *   property names match the HTML output;
 *
 *--------------------------------------------------------------------*/

oHTMLIndex & oHTMLIndex::css2 (void) 

{
	std::cout << "a:hover { text-decoration: underline; }" << std::endl;
	std::cout << "a.index { text-decoration: none; }" << std::endl;
	std::cout << "a:visited { color: #000080; }" << std::endl;
	std::cout << "body { background:white; color:black; font:normal 10pt courier; margin: 10px 20px 10px 20px; }" << std::endl;
	std::cout << "pre  { background:white; color:black; font:normal 10pt courier; margin: 10px 20px 10px 20px; }" << std::endl;
	std::cout << "li.index { color: black; list-style: outside; padding: 00px 00px 00px 05px; }" << std::endl;
	return (* this);
}

/*====================================================================*
 *
 *   oHTMLIndex & include (char const *filename)
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
 *   oHTMLIndex & collect (char const * pathname, char const * filename);
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
 *   oHTMLIndex & publish (unsigned count);
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
	unsigned index = 0;
	unsigned limit = count = (oHTMLIndex::mlist.count () + (count - 1)) / count;
	oHTMLIndex::PageHeader ();
	oHTMLIndex::MarkStart ();
	oHTMLIndex::print (this->mlevel++, this->mspace, "<h1>");
	oHTMLIndex::print (this->mlevel, this->mspace, oHTMLIndex::title ());
	oHTMLIndex::print (this->mlevel--, this->mspace, "</h1>");
	oHTMLIndex::print (this->mlevel++, this->mspace, "<table class='" oHTMLINDEX_CLASS "'>");
	oHTMLIndex::print (this->mlevel++, this->mspace, "<tr class='" oHTMLINDEX_CLASS "'>");
	while (index < limit) 
	{
		oHTMLIndex::print (this->mlevel++, this->mspace, "<td class='" oHTMLINDEX_CLASS "'>");
		oHTMLIndex::level (this->mlevel++);
		std::cout << "<ol start='" << index + 1 << "'>";
		oHTMLIndex::space (1);
		while (index < limit) 
		{
			oHTMLIndex::mitem = oHTMLIndex::mlist.items (index++);
			oHTMLIndex::print (this->mlevel++, this->mspace, "<li class='" oHTMLINDEX_CLASS "'>");
			oHTMLIndex::print (this->mlevel, 0, "");
			oHTMLIndex::manchor.CoreAttributes.IdentityAttribute->value (index);
			oHTMLIndex::manchor.CoreAttributes.ClassAttribute->value ("index");
			oHTMLIndex::manchor.CoreAttributes.TitleAttribute->value (oHTMLIndex::mitem->name ());
			oHTMLIndex::manchor.LinkAttributes.ReferenceAttribute->value (oHTMLIndex::mitem->name ());
			oHTMLIndex::manchor.StartTag ();
			oHTMLIndex::print (0, 0, oHTMLIndex::mitem->name ());
			oHTMLIndex::manchor.EndTag ();
			oHTMLIndex::print (0, this->mspace, "");
			oHTMLIndex::print (this->mlevel--, this->mspace, "</li>");
		}
		oHTMLIndex::print (this->mlevel--, this->mspace, "</ol>");
		oHTMLIndex::print (this->mlevel--, this->mspace, "</td>");
		if ((limit += count) > oHTMLIndex::mlist.count ()) 
		{
			limit = oHTMLIndex::mlist.count ();
		}
	}
	oHTMLIndex::print (this->mlevel--, this->mspace, "</tr>");
	oHTMLIndex::print (this->mlevel--, this->mspace, "</table>");
	oHTMLIndex::MarkEnd ();
	oHTMLIndex::BodyFooter ();
	oHTMLIndex::PageFooter ();
	return (* this);
}

/*====================================================================*
 *
 *   oHTMLIndex (void);
 *   
 *--------------------------------------------------------------------*/

oHTMLIndex::oHTMLIndex (void) 

{
	owebpage::stylesheet (oHTMLINDEX_STYLESHEET);
	this->mlevel = 0;
	this->mspace = 1;
	return;
}

/*====================================================================*
 *
 *   ~oHTMLIndex (void);
 *   
 *--------------------------------------------------------------------*/

oHTMLIndex::~oHTMLIndex (void) 

{
	return;
}

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif

