/*====================================================================*
 *
 *   ochrtable.cpp - definition of ochrtable class;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCHRTABLE_SOURCE
#define oCHRTABLE_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <climits>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/strlib.h"
#include "../classes/ochrtable.hpp"

/*====================================================================*
 *
 *   ochrtable & ochrtable::toupper();
 *
 *   refresh upper case letters and replace lower case letters with 
 *   upper case letters;
 *
 *--------------------------------------------------------------------*/

ochrtable & ochrtable::toupper () 

{
	for (c = 'A'; c <= 'Z'; ochrtable::mtable [c++] = (char) (c));
	for (c = 'a'; c <= 'z'; ochrtable::mtable [c++] = (char) (c - ('a' - 'A')));
	return (*this);
}


/*====================================================================*
 *
 *   ochrtable & ochrtable::tolower();
 *
 *   refresh lower case letters and replace upper case letters with 
 *   lower case letters;
 *
 *--------------------------------------------------------------------*/

ochrtable & ochrtable::tolower () 

{
	for (c = 'A'; c <= 'Z'; ochrtable::mtable [c++] = (char) (c + ('a' - 'A')));
	for (c = 'a'; c <= 'z'; ochrtable::mtable [c++] = (char) (c));
	return (*this);
}


/*====================================================================*
 *
 *   ochrtable & ochrtable::charset(char const *charset1, char const *charset2);
 *
 *   replace characters from charset1 with corresponding characters 
 *   from charset2; if no corresponding character exists in charset2 
 *   then replace with NUL;
 *
 *--------------------------------------------------------------------*/

ochrtable & ochrtable::charset (char const * charset1, char const * charset2) 

{
	if ((charset1) && (charset2)) 
	{
		while (*charset1) 
		{
			ochrtable::mtable [(unsigned)(*charset1++)] = *charset2;
			if (*charset2) 
			{
				charset2++;
			}
		}
	}
	return (*this);
}


/*====================================================================*
 *
 *   ochrtable & ochrtable::mreset();
 *
 *
 *--------------------------------------------------------------------*/

ochrtable & ochrtable::mreset () 

{
	unsigned value = 0;
	while (value < (UCHAR_MAX+1)) 
	{
		ochrtable::mtable [value] = (unsigned char)(value);
		value++;
	}
	return (*this);
}


/*====================================================================*
 *
 *   ochrtable();
 *
 *--------------------------------------------------------------------*/

ochrtable::ochrtable () 

{
	ochrtable::mtable = new unsigned char [UCHAR_MAX + 1];
	ochrtable::mreset ();
	ochrtbl::mtable = ochrtable::mtable;
	return;
}


/*====================================================================*
 *
 *   ~ochrtable();
 *
 *--------------------------------------------------------------------*/

ochrtable::~ochrtable () 

{
	delete [] this->mtable;
	return;
}


/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif

