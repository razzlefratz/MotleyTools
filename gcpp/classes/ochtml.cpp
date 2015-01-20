/*====================================================================*
 *
 *   ochtml.cpp - definition of ochtml class;
 *
 *   format c language source files as html with associated css stylesheet
 *   references; the mwebpage references these (or similar) css definitions;
 *   pick any colors you like but use fixed fonts;
 *
 *      span.comments { color: green; }
 *      span.compiler { color: black; }
 *      span.language { color: black; }
 *      span.reserved { color: black; }
 *      span.standard { color: black; }
 *      span.constant { color: red; }
 *      span.variable { color: blue; }
 *      span.operator { color: black; }
 *      span.function { color: blue; }
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCHTML_SOURCE
#define oCHTML_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include <cstring>
#include <fstream>
#include <iostream>

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#include "../classes/ochtml.hpp"
#include "../classes/oerror.hpp"

/*====================================================================*
 *   data initialization;
 *--------------------------------------------------------------------*/

ofilespec ochtml::filespec;

/*====================================================================*
 *
 *   void css2 (void);
 *
 *   print a compatible CSS stylesheet on stdout so that element and
 *   property names match HTML output;
 *
 *--------------------------------------------------------------------*/

ochtml & ochtml::css2 (void)

{
	std::cout << "a:hover { text-decoration: underline; }" << std::endl;
	std::cout << "a { text-decoration: none; }" << std::endl;
	std::cout << "a:link { color: navy; }" << std::endl;
	std::cout << "a:active { }" << std::endl;
	std::cout << "a:visited { color: navy; }" << std::endl;
	std::cout << "body { background:white; color:black; font:normal 12pt courier; margin: 10px 20px 10px 20px; }" << std::endl;
	std::cout << "pre  { background:white; color:black; font:normal 12pt courier; margin: 10px 20px 10px 20px; }" << std::endl;
	std::cout << "div.bodyheader { margin: 10px 10px 10px 10px; test-align: center; }" << std::endl;
	std::cout << "div.linkheader { margin: 10px 10px 10px 10px; text-align: left; }" << std::endl;
	std::cout << "div.linkfooter { margin: 10px 10px 10px 10px; text-align: right; }" << std::endl;
	std::cout << "div.bodyfooter { margin: 10px 10px 10px 10px; text-align: center; }" << std::endl;
	std::cout << "span.comments { color: green; }" << std::endl;
	std::cout << "span.compiler { color: black; }" << std::endl;
	std::cout << "span.language { color: black; }" << std::endl;
	std::cout << "span.reserved { color: black; }" << std::endl;
	std::cout << "span.standard { color: black; }" << std::endl;
	std::cout << "span.constant { color: red; }" << std::endl;
	std::cout << "span.variable { color: blue; }" << std::endl;
	std::cout << "span.operator { color: black; }" << std::endl;
	std::cout << "span.function { color: fuschia; }" << std::endl;
	return (* this);
}

/*====================================================================*
 *
 *   ochtml & html (char const *filename);
 *
 *   open the named c language source file, read the contents and write
 *   an html page to stdout; the page displays the original file having
 *   comments, keywords, constants, variables and operators highlighed in
 *   various colors for visual effect; selected constants, variable and
 *   filenames may have hyperlinks to companion pages;
 *
 *--------------------------------------------------------------------*/

ochtml & ochtml::html (char const * filename)

{
	std::ofstream output;
	std::streambuf * buf;
	ochtml::level (0);
	ochtml::space (1);
	this->mindex = 1;
	filename = ochtml::filespec.filespec (filename).fullpath ();
	if (this->mfile.read (filename).isempty ())
	{
		oerror::print ("can't open %s for input", filename);
	}
	filename = ochtml::filespec.savename (".html");
	output.open (filename, std::fstream::out);
	if (! output.is_open ())
	{
		oerror::print ("can't open %s for output", filename);
	}
	buf = std::cout.rdbuf (output.rdbuf ());
	ochtml::title (filename);
	ochtml::PageHeader ();
	ochtml::LinkHeader ();
	std::cout << "<pre>" << std::endl;
	while (! this->mfile.isempty ())
	{
		unsigned level = 0;
		switch (this->mfile.flush ().scantoken ().tokentype ())
		{
		case CL_T_COMMENTS:
			this->mspan.CoreAttributes.IdentityAttribute->value ("");
			this->mspan.CoreAttributes.ClassAttribute->value ("comments");
			this->mspan.StartTag ();
			this->mfile.write ();
			this->mspan.EndTag ();
			break;
		case CL_T_COMPILER:
			this->mspan.CoreAttributes.IdentityAttribute->value ("");
			this->mspan.CoreAttributes.ClassAttribute->value ("compiler");
			this->mspan.StartTag ();
			this->mfile.write ();
			this->mspan.EndTag ();
			break;
		case CL_T_LANGUAGE:
			this->mspan.CoreAttributes.IdentityAttribute->value ("");
			this->mspan.CoreAttributes.ClassAttribute->value ("language");
			this->mspan.StartTag ();
			this->mfile.write ();
			this->mspan.EndTag ();
			break;
		case CL_T_RESERVED:
			this->mspan.CoreAttributes.IdentityAttribute->value ("");
			this->mspan.CoreAttributes.ClassAttribute->value ("reserved");
			this->mspan.StartTag ();
			this->mfile.write ();
			this->mspan.EndTag ();
			break;
		case CL_T_STANDARD:
			this->mspan.CoreAttributes.IdentityAttribute->value (this->mindex++);
			this->mspan.CoreAttributes.ClassAttribute->value ("standard");
			this->mspan.StartTag ();
			this->mfile.write ();
			this->mspan.EndTag ();
			break;
		case CL_T_CONSTANT:
			this->mspan.CoreAttributes.IdentityAttribute->value (this->mindex++);
			this->mspan.CoreAttributes.ClassAttribute->value ("constant");
			this->mspan.StartTag ();
			this->mfile.write ();
			this->mspan.EndTag ();
			break;
		case CL_T_FUNCTION:
		case CL_T_VARIABLE:
			if (! level)
			{
				this->mspan.CoreAttributes.IdentityAttribute->value (this->mindex++);
				this->mspan.CoreAttributes.ClassAttribute->value ("variable");
				this->mspan.StartTag ();
				this->mfile.write ();
				this->mspan.EndTag ();
				strcpy (this->murl, "#");
				strcat (this->murl, this->mfile.tokentext ());
				this->minternal.define (this->mfile.tokentext (), this->murl);
			}
			else if (this->minternal.defined (this->mfile.tokentext ()))
			{
				this->mlink.CoreAttributes.IdentityAttribute->value ("");

#if 0

				this->mlink.LinkAttributes.ReferenceAttribute->value (this->minternal.expand (this->mfile.tokentext ()));

#else

				this->mlink.LinkAttributes.ReferenceAttribute->value (this->mindex++);

#endif

				this->mlink.StartTag ();
				this->mfile.write ();
				this->mlink.EndTag ();
			}
			else if (this->mexternal.defined (this->mfile.tokentext ()))
			{
				this->mlink.CoreAttributes.IdentityAttribute->value ("");

#if 0

				this->mlink.LinkAttributes.ReferenceAttribute->value (this->mexternal.expand (this->mfile.tokentext ()));

#else

				this->mlink.LinkAttributes.ReferenceAttribute->value (this->mindex++);

#endif

				this->mlink.StartTag ();
				this->mfile.write ();
				this->mlink.EndTag ();
			}
			else if (clibword.defined (this->mfile.tokentext ()))
			{
				this->mspan.CoreAttributes.IdentityAttribute->value ("");
				this->mspan.CoreAttributes.ClassAttribute->value ("variable");
				this->mspan.StartTag ();
				this->mfile.write ();
				this->mspan.EndTag ();
			}
			else 
			{
				this->mspan.CoreAttributes.IdentityAttribute->value ("");
				this->mspan.CoreAttributes.ClassAttribute->value ("variable");
				this->mspan.StartTag ();
				this->mfile.write ();
				this->mspan.EndTag ();
			}
			break;
		case CL_T_OPERATOR:
		case CL_T_SEPERATE:
			if (this->mfile.istoken ("#"))
			{
				this->mfile.write ();
				this->directive ();
			}
			else if (this->mfile.istoken ("(") || this->mfile.istoken ("{"))
			{
				this->mfile.write ();
				level++;
			}
			else if (this->mfile.istoken (")") || this->mfile.istoken ("}"))
			{
				this->mfile.write ();
				level--;
			}
			else for (char const * sp = this->mfile.tokentext (); * sp; ++ sp)
			{
				std::cout << this->mglyph.string (* sp);
			}
			break;
		default: 
			this->mfile.write ();
			break;
		}
	}
	std::cout << "</pre>" << std::endl;
	ochtml::LinkFooter ();
	ochtml::BodyFooter ();
	ochtml::PageFooter ();
	this->mfile.clear ();
	std::cout.rdbuf (buf);
	output.close ();
	return (* this);
}

/*====================================================================*
 *
 *   void directive ();
 *
 *   under construction;
 *
 *--------------------------------------------------------------------*/

ochtml & ochtml::directive ()

{
	std::cout << this->mfile.flush ().scanspace ().tokentext ();
	switch (cprocword.indexof (this->mfile.flush ().scantoken ().tokentext ()))
	{
	case oCPROCWORD_O_DEFINE:
		this->mspan.CoreAttributes.IdentityAttribute->value (this->mindex++);
		this->mspan.CoreAttributes.ClassAttribute->value ("keyword");
		this->mspan.StartTag ();
		this->mfile.write ();
		this->mspan.EndTag ();
		std::cout << this->mfile.flush ().scanspace ().tokentext ();
		this->mfile.flush ().scantoken ();
		this->mspan.CoreAttributes.IdentityAttribute->value ("");
		this->mspan.CoreAttributes.ClassAttribute->value ("variable");
		this->mspan.StartTag ();
		this->mfile.write ();
		this->mspan.EndTag ();
		strcpy (this->murl, "#");
		strcat (this->murl, this->mfile.tokentext ());
		this->minternal.define (this->mfile.tokentext (), this->murl);
		break;

#if 0        

/*
 * no special action performed for these directives at this time;
 */

	case oCPROCWORD_O_ELIF:
	case oCPROCWORD_O_ELSE:
	case oCPROCWORD_O_ENDIF:
	case oCPROCWORD_O_ERROR:
	case oCPROCWORD_O_IF:
	case oCPROCWORD_O_IFDEF:
	case oCPROCWORD_O_IFNDEF:

#endif

	case oCPROCWORD_O_INCLUDE:
		this->mspan.CoreAttributes.IdentityAttribute->value (this->mindex++);
		this->mspan.CoreAttributes.ClassAttribute->value ("reserved");
		this->mspan.StartTag ();
		this->mfile.write ();
		this->mspan.EndTag ();
		std::cout << this->mfile.flush ().scanspace ().tokentext ();
		if (this->mfile.isbreak ('\"'))
		{
			std::cout << "&quot;";
			this->mfile.scanbreak ().flush ().scanuntil ("\"");
			this->mlink.CoreAttributes.IdentityAttribute->value ("");
			this->mlink.CoreAttributes.ClassAttribute->value ("variable");
			this->mlink.LinkAttributes.ReferenceAttribute->value (ochtml::filespec.filespec (this->mfile.tokentext ()).savename (".html"));
			this->mlink.StartTag ();
			this->mfile.write ();
			this->mlink.EndTag ();
			this->mfile.scanbreak ().flush ();
			std::cout << "&quot;";
		}
		else if (this->mfile.isbreak ('\''))
		{
			std::cout << "&apos;";
			this->mfile.scanbreak ().flush ().scanuntil ("\'");
			this->mspan.CoreAttributes.IdentityAttribute->value ("");
			this->mspan.CoreAttributes.ClassAttribute->value ("variable");
			this->mspan.StartTag ();
			this->mfile.write ();
			this->mlink.EndTag ();
			this->mfile.scanbreak ().flush ();
			std::cout << "&apos;";
		}
		else if (this->mfile.isbreak ('<'))
		{
			std::cout << "&lt;";
			this->mfile.scanbreak ().flush ().scanuntil (">");
			this->mspan.CoreAttributes.IdentityAttribute->value ("");
			this->mspan.CoreAttributes.ClassAttribute->value ("variable");
			this->mspan.StartTag ();
			this->mfile.write ();
			this->mspan.EndTag ();
			this->mfile.scanbreak ().flush ();
			std::cout << "&gt;";
		}

#if 0         

		else if (this->mfile.isbreak ('['))
		{
			std::cout << this->mfile.tokentext ();
			this->mfile.scanbreak ().flush ().scanuntil ("]");
			this->mspan.CoreAttributes.IdentityAttribute->value ("");
			this->mspan.CoreAttributes.ClassAttribute->value ("variable");
			this->mspan.StartTag ();
			this->mfile.write ();
			this->mspan.EndTag ();
			this->mfile.flush ().scanbreak ();
			std::cout << this->mfile.tokentext ();
		}
		else if (this->mfile.isbreak ('('))
		{
			std::cout << this->mfile.tokentext ();
			this->mfile.scanbreak ().flush ().scanuntil (")");
			this->mspan.CoreAttributes.IdentityAttribute->value ("");
			this->mspan.CoreAttributes.ClassAttribute->value ("variable");
			this->mspan.StartTag ();
			this->mfile.write ();
			this->mspan.EndTag ();
			this->mfile.flush ().scanbreak ();
			std::cout << this->mfile.tokentext ();
		}

#endif

		else 
		{
			this->mfile.write ();
		}
		break;

#if 0        

/*
 * no special action performed for these directives at this time;
 */

	case oCPROCWORD_O_LINE:
	case OCPROCWORD_O_PRAGMA:
	case oCPROCWORD_O_UNDEF:

#endif

	default: 
		this->mspan.CoreAttributes.IdentityAttribute->value (this->mindex++);
		this->mspan.CoreAttributes.ClassAttribute->value ("keyword");
		this->mspan.StartTag ();
		this->mfile.write ();
		this->mspan.EndTag ();
		break;
	}
	return (* this);
}

/*====================================================================*
 *
 *   ochtml(char const * stylesheet);
 *
 *--------------------------------------------------------------------*/

ochtml::ochtml (char const * stylesheet)

{
	owebpage::stylesheet (stylesheet);
	this->murl = new char [FILENAME_MAX + 1];
	this->murl [0] = (char) (0);
	this->mindex = 1;
	return;
}

/*====================================================================*
 *
 *   ochtml();
 *
 *--------------------------------------------------------------------*/

ochtml::ochtml ()

{
	owebpage::stylesheet (oCHTML_PAGE_STYLESHEET);
	this->murl = new char [FILENAME_MAX + 1];
	this->murl [0] = (char) (0);
	this->mindex = 1;
	return;
}

/*====================================================================*
 *
 *   ~ochtml();
 *
 *--------------------------------------------------------------------*/

ochtml::~ ochtml ()

{
	return;
}

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif



