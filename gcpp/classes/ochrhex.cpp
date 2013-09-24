/*====================================================================*
 *
 *   ochrhex.cpp - implementation of the ochrhex class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCHRHEX_SOURCE
#define oCHRHEX_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ochrhex.hpp"

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

char const * ochrhex::digits = "0123456789ABCDEF";

/*====================================================================*
 *
 *   char *ochrhex::tohex(char *string, unsigned c)
 *
 *   encode string with NUL terminated representation of character value
 *   c and return the terminator address;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char * ochrhex::tohex (char * string, unsigned c)

{
	* string++ = ochrhex::digits [(c >> 4) & 0x000F];
	* string++ = ochrhex::digits [(c >> 0) & 0x000F];
	* string = (char) (0);
	return (string);
}

/*====================================================================*
 *   
 *   char * toietf (char * string, unsigned c);
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char * ochrhex::toietf (char * string, unsigned c)

{
	* string++ = '%';
	string = ochrhex::tohex (string, c);
	return (string);
}

/*====================================================================*
 *   
 *   char * toiso (char * string, unsigned c);
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char * ochrhex::toiso (char * string, unsigned c)

{
	* string++ = '#';
	* string++ = 'x';
	string = ochrhex::tohex (string, c);
	return (string);
}

/*====================================================================*
 *   
 *   char * tohtml (char * string, unsigned c);
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char * ochrhex::tohtml (char * string, unsigned c)

{
	* string++ = '&';
	string = ochrhex::toiso (string, c);
	* string++ = ';';
	* string = (char) (0);
	return (string);
}

/*====================================================================*
 *   
 *   char * toconst (char * string, unsigned c);
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char * ochrhex::toconst (char * string, unsigned c)

{
	* string++ = '0';
	* string++ = 'x';
	string = ochrhex::tohex (string, c);
	return (string);
}

/*====================================================================*
 *   
 *   ochrhex ();
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ochrhex::ochrhex ()

{
	return;
}

/*====================================================================*
 *   
 *   ~ochrhex ();
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ochrhex::~ ochrhex ()

{
	return;
}

/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif



