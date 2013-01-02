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
#include <iostream>
#include <fstream>

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
 *   void stylesheet ();
 *   
 *   write a compatible CSS stylesheet on stdout; the element and
 *   property names are referenced throughout the document;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ochtml & ochtml::stylesheet () 

{
	std::cout << "a:hover { text-decoration: underline; }\n";
	std::cout << "a { text-decoration: none; }\n";
	std::cout << "a:link { color: #000080; }\n";
	std::cout << "a:active { } ";
	std::cout << "a:visited { color: #000080; }\n";
	std::cout << "body { background:white; color:black; font:normal 10pt courier; margin: 10px 20px 10px 20px; }\n";
	std::cout << "pre  { background:white; color:black; font:normal 10pt courier; margin: 10px 20px 10px 20px; } \n";
	std::cout << "span.comments { color: green; }\n";
	std::cout << "span.compiler { color: black; }\n";
	std::cout << "span.language { color: black; }\n";
	std::cout << "span.reserved { color: black; }\n";
	std::cout << "span.standard { color: black; }\n";
	std::cout << "span.constant { color: red; }\n";
	std::cout << "span.variable { color: blue; }\n";
	std::cout << "span.operator { color: black; }\n";
	std::cout << "span.function { color: fuschia; }\n";
	return (*this);
}


/*====================================================================*
 *
 *   ochtml & stylesheet (char const * string);
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ochtml & ochtml::stylesheet (char const * string) 

{
	owebpage::stylesheet (string);
	return (*this);
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
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ochtml & ochtml::html (char const *filename) 

{
	std::ofstream output;
	std::streambuf *buf;
	filename = ochtml::filespec.filespec (filename).fullpath ();
	if (this->mfile.read (filename).isempty ()) 
	{
		oerror::print ("can't open %s for input", filename);
	}
	filename = ochtml::filespec.savename (".html");
	output.open (filename, std::fstream::out);
	if (!output.is_open ()) 
	{
		oerror::print ("can't open %s for output", filename);
	}
	buf = std::cout.rdbuf (output.rdbuf ());
	ochtml::topPage ();
	std::cout << "<pre>";
	while (!this->mfile.isempty ()) 
	{
		unsigned level = 0;
		switch (this->mfile.scanflush ().scantoken ().tokentype ()) 
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
			this->mspan.CoreAttributes.IdentityAttribute->value ("");
			this->mspan.CoreAttributes.ClassAttribute->value ("standard");
			this->mspan.StartTag ();
			this->mfile.write ();
			this->mspan.EndTag ();
			break;
		case CL_T_CONSTANT:
			this->mspan.CoreAttributes.IdentityAttribute->value ("");
			this->mspan.CoreAttributes.ClassAttribute->value ("constant");
			this->mspan.StartTag ();
			this->mfile.write ();
			this->mspan.EndTag ();
			break;
		case CL_T_FUNCTION:
		case CL_T_VARIABLE:
			if (!level) 
			{
				this->mspan.CoreAttributes.IdentityAttribute->value (this->mfile.tokentext ());
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
				this->mlink.LinkAttributes.ReferenceAttribute->value (this->minternal.expand (this->mfile.tokentext ()));
				this->mlink.StartTag ();
				this->mfile.write ();
				this->mlink.EndTag ();
			}
			else if (this->mexternal.defined (this->mfile.tokentext ())) 
			{
				this->mlink.LinkAttributes.ReferenceAttribute->value (this->mexternal.expand (this->mfile.tokentext ()));
				this->mlink.StartTag ();
				this->mfile.write ();
				this->mlink.EndTag ();
			}
			else if (clibword.defined (this->mfile.tokentext ())) 
			{
				this->mspan.CoreAttributes.IdentityAttribute->value (this->mfile.tokentext ());
				this->mspan.CoreAttributes.ClassAttribute->value ("variable");
				this->mspan.StartTag ();
				this->mfile.write ();
				this->mspan.EndTag ();
			}
			else 
			{
				this->mspan.CoreAttributes.IdentityAttribute->value (this->mfile.tokentext ());
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
			else for (char const * sp = this->mfile.tokentext (); *sp; ++sp) 
			{
				std::cout << this->mglyph.string (*sp);
			}
			break;
		default:
			this->mfile.write ();
			break;
		}
	}
	std::cout << "</pre>\r\n";
	ochtml::botPage ();
	this->mfile.clear ();
	std::cout.rdbuf (buf);
	output.close ();
	return (*this);
}


/*====================================================================*
 *
 *   void directive ();
 *
 *   under construction;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ochtml & ochtml::directive () 

{
	std::cout << this->mfile.scanflush ().scanspace ().tokentext ();
	switch (cprocword.indexof (this->mfile.scanflush ().scantoken ().tokentext ())) 
	{
	case oCPROCWORD_O_DEFINE:
		this->mspan.CoreAttributes.IdentityAttribute->value ("");
		this->mspan.CoreAttributes.ClassAttribute->value ("keyword");
		this->mspan.StartTag ();
		this->mfile.write ();
		this->mspan.EndTag ();
		std::cout << this->mfile.scanflush ().scanspace ().tokentext ();
		this->mfile.scanflush ().scantoken ();
		this->mspan.CoreAttributes.IdentityAttribute->value (this->mfile.tokentext ());
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
		this->mspan.CoreAttributes.IdentityAttribute->value ("");
		this->mspan.CoreAttributes.ClassAttribute->value ("reserved");
		this->mspan.StartTag ();
		this->mfile.write ();
		this->mspan.EndTag ();
		std::cout << this->mfile.scanflush ().scanspace ().tokentext ();
		if (this->mfile.isbreak ('\"')) 
		{
			std::cout << "&quot;";
			this->mfile.scanbreak ().scanflush ().scanuntil ("\"");
			this->mlink.CoreAttributes.IdentityAttribute->value ("");
			this->mlink.CoreAttributes.ClassAttribute->value ("variable");
			this->mlink.LinkAttributes.ReferenceAttribute->value (ochtml::filespec.filespec (this->mfile.tokentext ()).savename (".html"));
			this->mlink.StartTag ();
			this->mfile.write ();
			this->mlink.EndTag ();
			this->mfile.scanbreak ().scanflush ();
			std::cout << "&quot;";
		}
		else if (this->mfile.isbreak ('\'')) 
		{
			std::cout << "&apos;";
			this->mfile.scanbreak ().scanflush ().scanuntil ("\'");
			this->mspan.CoreAttributes.IdentityAttribute->value ("");
			this->mspan.CoreAttributes.ClassAttribute->value ("variable");
			this->mspan.StartTag ();
			this->mfile.write ();
			this->mlink.EndTag ();
			this->mfile.scanbreak ().scanflush ();
			std::cout << "&apos;";
		}
		else if (this->mfile.isbreak ('<')) 
		{
			std::cout << "&lt;";
			this->mfile.scanbreak ().scanflush ().scanuntil (">");
			this->mspan.CoreAttributes.IdentityAttribute->value ("");
			this->mspan.CoreAttributes.ClassAttribute->value ("variable");
			this->mspan.StartTag ();
			this->mfile.write ();
			this->mspan.EndTag ();
			this->mfile.scanbreak ().scanflush ();
			std::cout << "&gt;";
		}

#if 0         

		else if (this->mfile.isbreak ('[')) 
		{
			std::cout << this->mfile.tokentext ();
			this->mfile.scanbreak ().scanflush ().scanuntil ("]");
			this->mspan.CoreAttributes.IdentityAttribute->value ("");
			this->mspan.CoreAttributes.ClassAttribute->value ("variable");
			this->mspan.StartTag ();
			this->mfile.write ();
			this->mspan.EndTag ();
			this->mfile.scanflush ().scanbreak ();
			std::cout << this->mfile.tokentext ();
		}
		else if (this->mfile.isbreak ('(')) 
		{
			std::cout << this->mfile.tokentext ();
			this->mfile.scanbreak ().scanflush ().scanuntil (")");
			this->mspan.CoreAttributes.IdentityAttribute->value ("");
			this->mspan.CoreAttributes.ClassAttribute->value ("variable");
			this->mspan.StartTag ();
			this->mfile.write ();
			this->mspan.EndTag ();
			this->mfile.scanflush ().scanbreak ();
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
		this->mspan.CoreAttributes.IdentityAttribute->value ("");
		this->mspan.CoreAttributes.ClassAttribute->value ("keyword");
		this->mspan.StartTag ();
		this->mfile.write ();
		this->mspan.EndTag ();
		break;
	}
	return (*this);
}


/*====================================================================*
 *
 *   ochtml(char const * stylesheet);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ochtml::ochtml (char const * stylesheet) 

{
	owebpage::stylesheet (stylesheet);
	this->murl = new char [FILENAME_MAX + 1];
	this->murl [0] = (char)(0);
	return;
}


/*====================================================================*
 *
 *   ochtml();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ochtml::ochtml () 

{

// owebpage::stylesheet ("http://www.cmassoc.net/styles/clang.css");

	owebpage::stylesheet ("clang.css");
	this->murl = new char [FILENAME_MAX + 1];
	this->murl [0] = (char)(0);
	return;
}


/*====================================================================*
 *
 *   ~ochtml();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ochtml::~ochtml () 

{
	return;
}


/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif

