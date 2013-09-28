/*====================================================================*
 *
 *   oISOGlyph.cpp - definition of the oISOGlyph class.
 *
 *   this object implement the conversion of special characters to their
 *   equivalent ISO glyph name for use on HTML pages;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oISOGLYPH_SOURCE
#define oISOGLYPH_SOURCE

/*====================================================================*
 *   standard header files;
 *--------------------------------------------------------------------*/

#include <limits.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oISOGlyph.hpp"

/*====================================================================*
 *   data initialization;
 *--------------------------------------------------------------------*/

char const * oISOGlyph::mtable [UCHAR_MAX +  1] =

{
	"#x00",
	"#x01",
	"#x02",
	"#x03",
	"#x04",
	"#x05",
	"#x06",
	"#x07",
	"#x08",
	"#x09",
	"#x0A",
	"#x0B",
	"#x0C",
	"#x0D",
	"#x0E",
	"#x0F",
	"#x10",
	"#x11",
	"#x12",
	"#x13",
	"#x14",
	"#x15",
	"#x16",
	"#x17",
	"#x18",
	"#x19",
	"#x1A",
	"#x1B",
	"#x1C",
	"#x1D",
	"#x1E",
	"#x1F",
	" ",
	"!",
	"quot",
	"#",
	"$",
	"%",
	"amp",
	"apos",
	"(",
	")",
	"*",
	"+",
	",",
	"-",
	".",
	"/",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	":",
	";",
	"lt",
	"=",
	"gt",
	"?",
	"@",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"[",
	"\\",
	"]",
	"^",
	"_",
	"`",
	"a",
	"b",
	"c",
	"d",
	"e",
	"f",
	"g",
	"h",
	"i",
	"j",
	"k",
	"l",
	"m",
	"n",
	"o",
	"p",
	"q",
	"r",
	"s",
	"t",
	"u",
	"v",
	"w",
	"x",
	"y",
	"z",
	"{",
	"|",
	"}",
	"~",
	"#x7F",
	"#x80",
	"#x81",
	"#x82",
	"#x83",
	"#x84",
	"#x85",
	"#x86",
	"#x87",
	"#x88",
	"#x89",
	"#x8A",
	"#x8B",
	"#x8C",
	"#x8D",
	"#x8E",
	"#x8F",
	"#x90",
	"#x91",
	"#x92",
	"#x93",
	"#x94",
	"#x95",
	"ndash",
	"mdash",
	"#x98",
	"#x99",
	"#x9A",
	"rsaquo",
	"#x9C",
	"#x9D",
	"#x9E",
	"#x9F",
	"nbsp",
	"iexcl",
	"cent",
	"pound",
	"curren",
	"yen",
	"brvbar",
	"sect",
	"uml",
	"copy",
	"ordf",
	"laquo",
	"not",
	"shy",
	"reg",
	"macr",
	"deg",
	"plusmn",
	"sup2",
	"sup3",
	"acute",
	"micro",
	"para",
	"middot",
	"cedil",
	"sup1",
	"ordm",
	"raquo",
	"frac14",
	"frac12",
	"frac34",
	"iquest",
	"Agrave",
	"Aacute",
	"Acirc",
	"Atilde",
	"Auml",
	"Aring",
	"AElig",
	"Ccedil",
	"Egrave",
	"Eacute",
	"Ecirc",
	"Euml",
	"Igrave",
	"Iacute",
	"Icirc",
	"Iuml",
	"Eth",
	"Ntilde",
	"Ograve",
	"Oacute",
	"Ocirc",
	"Otilde",
	"Ouml",
	"times",
	"Oslash",
	"Ugrave",
	"Uacute",
	"Ucirc",
	"Uuml",
	"Yacute",
	"Thorn",
	"szlig",
	"agrave",
	"aacute",
	"acirc",
	"atilde",
	"auml",
	"aring",
	"aelig",
	"ccedil",
	"egrave",
	"eacute",
	"ecirc",
	"euml",
	"igrave",
	"iacute",
	"icirc",
	"iuml",
	"eth",
	"ntilde",
	"ograve",
	"oacute",
	"ocirc",
	"otilde",
	"ouml",
	"divide",
	"oslash",
	"ugrave",
	"uacute",
	"ucirc",
	"uuml",
	"yacute",
	"thorn",
	"yuml"
};

/*====================================================================*
 *
 *   char const string (signed c) const;
 *
 *   return the ISO glyph string for the ASCII character argument;
 *   for example, 'A' returns "A", '<' returns "&lt;" and '\t'
 *   returns "&0x09;";
 *
 *--------------------------------------------------------------------*/

char const * oISOGlyph::string (signed c)

{
	char const * string = oISOGlyph::mtable [c & UCHAR_MAX];
	char * sp = this->mstring;
	if (string [1])
	{
		* sp++ = '&';
		while (* string)
		{
			* sp++ = * string++;
		}
		* sp++ = ';';
	}
	else 
	{
		* sp++ = * string;
	}
	* sp = (char) (0);
	return ((char const *) (this->mstring));
}

/*====================================================================*
 *
 *   oISOGlyph (void);
 *
 *--------------------------------------------------------------------*/

oISOGlyph::oISOGlyph (void)

{
	this->mstring = new char [16];
	this->mstring [0] = (char) (0);
	return;
}

/*====================================================================*
 *
 *   ~oISOGlyph (void);
 *
 *--------------------------------------------------------------------*/

oISOGlyph::~ oISOGlyph (void)

{
	delete [] this->mstring;
	return;
}

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif



