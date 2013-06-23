/*====================================================================*
 *
 *   oHTMLElementNames.cpp - definition of oHTMLElementNames class;
 *
 *   this object implements the detectiOn, lookup and retrieval of HTML
 *   element names;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oHTMLELEMENTS_SOURCE
#define oHTMLELEMENTS_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oHTMLElementNames.hpp"

/*====================================================================*
 *
 *   oHTMLElementNames ();
 *
 *   assign oHTMLElementNames count and table to okeyword count and table;
 *   
 *--------------------------------------------------------------------*/

oHTMLElementNames::oHTMLElementNames () 

{
	static char const * table [] = 
	{
		"a",
		"abbr",
		"acronym",
		"address",
		"applet",
		"area",
		"b",
		"base",
		"basefont",
		"bdo",
		"bgsound",
		"big",
		"blockquote",
		"body",
		"br",
		"button",
		"caption",
		"center",
		"cite",
		"code",
		"col",
		"colgroup",
		"dd",
		"del",
		"dfn",
		"dir",
		"div",
		"dl",
		"dt",
		"em",
		"embed",
		"fieldset",
		"font",
		"form",
		"frame",
		"frameset",
		"h1",
		"h2",
		"h3",
		"h4",
		"h5",
		"h6",
		"head",
		"hr",
		"html",
		"i",
		"iframe",
		"img",
		"input",
		"ins",
		"isindex",
		"kbd",
		"label",
		"li",
		"link",
		"listing",
		"map",
		"marquee",
		"menu",
		"meta",
		"noframes",
		"noscript",
		"object",
		"ol",
		"optgroup",
		"option",
		"p",
		"param",
		"plaintext",
		"pre",
		"q",
		"s",
		"samp",
		"script",
		"select",
		"small",
		"span",
		"strike",
		"strong",
		"style",
		"sub",
		"sup",
		"table",
		"tbody",
		"td",
		"textarea",
		"tfoot",
		"th",
		"thead",
		"title",
		"tr",
		"tt",
		"u",
		"ul",
		"var",
		"wbr",
		"xml",
		"xmp",
		(char const *)(0)
	};
	okeywords::mtitle = "HTMLElement";
	okeywords::mcount = sizeof (table) / sizeof (char const *) - 1;
	okeywords::mtable = table;
	okeywords::mcheck ();
	return;
}


/*====================================================================*
 *
 *   ~oHTMLElementNames ();
 *   
 *--------------------------------------------------------------------*/

oHTMLElementNames::~oHTMLElementNames () 

{
	return;
}


/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif

