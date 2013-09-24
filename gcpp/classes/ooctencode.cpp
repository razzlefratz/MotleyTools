/*====================================================================*
 *
 *   ooctencode.cpp - implementation of the ooctencode class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oOCTENCODE_SOURCE
#define oOCTENCODE_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ooctencode.hpp"

/*====================================================================*
 *   constant definitions and declarations; 
 *--------------------------------------------------------------------*/

char const ooctencode::mdigit [] = "01234567";

/*====================================================================*
 *
 *   char * ooctencode::numeric(char *string,  const unsigned c);
 *
 *   encode the string argument with the three digit octal representation 
 *   of the character argument; terminate encoding with NUL;
 *
 *--------------------------------------------------------------------*/

char * ooctencode::numeric (char * string, const unsigned c)

{
	* string++ = ooctencode::mdigit [(c >> 6) & 0x0003];
	* string++ = ooctencode::mdigit [(c >> 3) & 0x0007];
	* string++ = ooctencode::mdigit [(c >> 0) & 0x0007];
	* string = (char) (0);
	return (string);
}

/*====================================================================*
 *
 *   char * ooctencode::literal(char *string,  const unsigned c)
 *
 *   encode the string argument with the three digit octal representation of 
 *   the character argument; prefix encoding with an escape character;
 *
 *--------------------------------------------------------------------*/

char * ooctencode::literal (char * string, const unsigned c)

{
	* string++ = '\\';
	string = ooctencode::numeric (string, c);
	return (string);
}

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

ooctencode::ooctencode ()

{
	return;
}

ooctencode::~ ooctencode ()

{
	return;
}

/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif



