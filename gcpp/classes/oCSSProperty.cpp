/*====================================================================*
 *
 *   oCSSProperty.cpp - definition of the oCSSProperty class.
 *
 *   symbol table containing CSS property names;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCSSPROPERTY_SOURCE
#define oCSSPROPERTY_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oCSSProperty.hpp"

/*====================================================================*
 *
 *   oCSSProperty ();
 *   
 *
 *--------------------------------------------------------------------*/

oCSSProperty::oCSSProperty ()

{
	static char const * table [] = 
	{
		"azimuth",
		"background",
		"background-attachment",
		"background-color",
		"background-image",
		"background-position",
		"background-repeat",
		"border",
		"border-bottom",
		"border-bottom-color",
		"border-bottom-style",
		"border-bottom-width",
		"border-collapse",
		"border-color",
		"border-left",
		"border-left-color",
		"border-left-style",
		"border-left-width",
		"border-right",
		"border-right-color",
		"border-right-style",
		"border-right-width",
		"border-spacing",
		"border-style",
		"border-top",
		"border-top-color",
		"border-top-style",
		"border-top-width",
		"border-width",
		"bottom",
		"caption-side",
		"clear",
		"clip",
		"color",
		"content",
		"counter-increment",
		"counter-reset",
		"cue",
		"cue-after",
		"cue-before",
		"cursor",
		"direction",
		"display",
		"elevation",
		"empty-cells",
		"float",
		"font",
		"font-family",
		"font-size",
		"font-size-adjust",
		"font-stretch",
		"font-style",
		"font-variant",
		"font-weight",
		"height",
		"left",
		"letter-spacing",
		"line-height",
		"list-style",
		"list-style-image",
		"list-style-position",
		"list-style-type",
		"margin",
		"margin-bottom",
		"margin-left",
		"margin-right",
		"margin-top",
		"marker-offset",
		"marks",
		"max-height",
		"max-width",
		"min-height",
		"min-width",
		"orphans",
		"outline",
		"outline-color",
		"outline-style",
		"outline-width",
		"overflow",
		"padding",
		"padding-bottom",
		"padding-left",
		"padding-right",
		"padding-top",
		"page",
		"page-break-after",
		"page-break-before",
		"page-break-inside",
		"pause",
		"pause-after",
		"pause-before",
		"pitch",
		"pitch-range",
		"play-during",
		"position",
		"quotes",
		"richness",
		"right",
		"size",
		"speak",
		"speak-header",
		"speak-numeral",
		"speak-punctuation",
		"speech-rate",
		"stress",
		"table-layout",
		"text-align",
		"text-decoration",
		"text-indent",
		"text-shadow",
		"text-transform",
		"top",
		"unicode-bidi",
		"vertical-align",
		"visibility",
		"voice-family",
		"volume",
		"white-space",
		"widows",
		"width",
		"word-spacing",
		"z-index",
		(char const *) (0)
	};
	okeywords::mtitle = "CSSProperty";
	okeywords::mcount = sizeof (table) / sizeof (char const *) - 1;
	okeywords::mtable = table;
	okeywords::mcheck ();
	return;
}

/*====================================================================*
 *
 *   ~oCSSProperty ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oCSSProperty::~ oCSSProperty ()

{
	return;
}

/*====================================================================*
 *    end definition;
 *--------------------------------------------------------------------*/

#endif



