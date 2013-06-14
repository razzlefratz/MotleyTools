/*====================================================================*
 *
 *   ohexencode.cpp - implementation of the ohexencode class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oHEXENCODE_SOURCE
#define oHEXENCODE_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ohexencode.hpp"

/*====================================================================*
 *   constant definitisions and declarations;
 *--------------------------------------------------------------------*/

char const ohexencode::mdigit [] = "0123456789ABCDEF";

/*====================================================================*
 *
 *   char * octet (char *string, char const c);
 *
 *   encode string with the two digit hexidecimal representation of 
 *   the character argument and terminate with NUL;  
 *
 *--------------------------------------------------------------------*/

char * ohexencode::octet (char * string, char const c) 

{
	* string++ = ohexencode::mdigit [(c >> 4) & 0x0F];
	* string++ = ohexencode::mdigit [(c >> 0) & 0x0F];
	* string = (char) (0);
	return (string);
}


/*====================================================================*
 *
 *   char * literal (char *string, char const c);
 *
 *
 *--------------------------------------------------------------------*/

char * ohexencode::literal (char * string, char const c) 

{
	* string++ = '\\';
	* string++ = 'x';
	string = ohexencode::octet (string, c);
	return (string);
}


/*====================================================================*
 *
 *   char * iso (char *string, char const c);
 *
 *
 *--------------------------------------------------------------------*/

char * ohexencode::iso (char * string, char const c) 

{
	* string++ = '#';
	* string++ = 'x';
	string = ohexencode::octet (string, c);
	return (string);
}


/*====================================================================*
 *
 *   char * html (char *string, char const c);
 *
 *   encode the string argument with the two digit hexidecimal representation 
 *   of the character argument; prefix encoding with "&#x"; suffix encoding
 *   the ";";
 *
 *--------------------------------------------------------------------*/

char * ohexencode::html (char * string, char const c) 

{
	* string++ = '&';
	string = ohexencode::iso (string, c);
	* string++ = ';';
	* string = (char) (0);
	return (string);
}


/*====================================================================*
 *
 *   char * clang (char *string, char const c);
 *
 *
 *--------------------------------------------------------------------*/

char * ohexencode::clang (char * string, char const c) 

{
	* string++ = '0';
	* string++ = 'x';
	string = ohexencode::octet (string, c);
	return (string);
}


/*====================================================================*
 *
 *   char * ietf (char *string, char const c);
 *
 *
 *--------------------------------------------------------------------*/

char * ohexencode::ietf (char * string, char const c) 

{
	* string++ = '%';
	string = ohexencode::octet (string, c);
	return (string);
}


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

ohexencode::ohexencode () 

{
	return;
}


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

ohexencode::~ohexencode () 

{
	return;
}


/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif

