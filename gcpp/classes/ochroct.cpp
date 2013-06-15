/*====================================================================*
 *
 *   ochroct.cpp - implementation of the ochroct class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCHROCT_SOURCE
#define oCHROCT_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ochroct.hpp"

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

char const * ochroct::digits = "012345678";

/*====================================================================*
 *
 *   char *ochroct::tooctal(char *string, unsigned c);
 *   char *ochroct::tounix(char *string, unsigned c);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char * ochroct::tooctal (char * string, unsigned c) 

{
	* string++ = ochroct::digits [(c >> 6) & 0x0003];
	* string++ = ochroct::digits [(c >> 3) & 0x0007];
	* string++ = ochroct::digits [(c >> 0) & 0x0007];
	* string = (char) (0);
	return (string);
}


char * ochroct::tounix (char * string, unsigned c) 

{
	* string++ = '\\';
	string = ochroct::tooctal (string, c);
	return (string);
}


/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

ochroct::ochroct () 

{
	return;
};


ochroct::~ochroct () 

{
	return;
}


/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif

