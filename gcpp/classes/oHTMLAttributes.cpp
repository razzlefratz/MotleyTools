/*==========================================================================/
 *
 *   oHTMLAttributes.cpp - definition of oHTMLAttributes class.
 *
 *   this object implements the detection, lookup and retrieval of HTML
 *   attribute names;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oHTMLATTRIBUTUTES_SOURCE
#define oHTMLATTRIBUTUTES_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oHTMLAttributes.hpp"

/*====================================================================*
 *
 *   oHTMLAttributes ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oHTMLAttributes::oHTMLAttributes () 

{
	static char const * table [] = 
	{
		"abbr",
		"accept",
		"accept_charset",
		"accesskey",
		"action",
		"align",
		"alink",
		"alt",
		"archive",
		"axis",
		"background",
		"bgcolor",
		"border",
		"botmargin",
		"cellpadding",
		"cellspacing",
		"char",
		"charoff",
		"charset",
		"checked",
		"cite",
		"class",
		"classid",
		"clear",
		"code",
		"codebase",
		"codetype",
		"color",
		"cols",
		"colspan",
		"compact",
		"content",
		"coords",
		"data",
		"datetime",
		"declare",
		"defer",
		"dir",
		"disabled",
		"enctype",
		"face",
		"for",
		"frame",
		"frameborder",
		"headers",
		"height",
		"href",
		"hreflang",
		"hspace",
		"http-equiv",
		"id",
		"ismap",
		"label",
		"lang",
		"language",
		"link",
		"longdesc",
		"marginheight",
		"marginwidth",
		"maxlength",
		"media",
		"method",
		"multiple",
		"name",
		"nohref",
		"noresize",
		"noshade",
		"nowrap",
		"object",
		"ol",
		"onblur",
		"onchange",
		"onclick",
		"ondblclick",
		"onfocus",
		"onkeydown",
		"onkeypress",
		"onkeyup",
		"onmousedown",
		"onmousemove",
		"onmouseout",
		"onmouseover",
		"onmouseup",
		"onreset",
		"onselect",
		"onsubmit",
		"onunload",
		"profile",
		"prompt",
		"readonly",
		"rel",
		"rev",
		"rows",
		"rowspan",
		"rules",
		"scheme",
		"scope",
		"scrolling",
		"selected",
		"shape",
		"size",
		"span",
		"src",
		"start",
		"style",
		"summary",
		"tabindex",
		"target",
		"text",
		"title",
		"topmargin",
		"type",
		"usemap",
		"valign",
		"value",
		"valuetype",
		"version",
		"vlink",
		"vspace",
		"width",
		(char const *)(0)
	};
	okeywords::mtitle = "HTMLAttribute";
	okeywords::mcount = sizeof (table) / sizeof (char const *) - 1;
	okeywords::mtable = table;
	okeywords::mcheck ();
	return;
}


/*====================================================================*
 *
 *   ~oHTMLAttributes ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oHTMLAttributes::~oHTMLAttributes () 

{
	return;
}


/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif

