/*====================================================================*
 *
 *   obreak.hpp - interface for the obreak classr;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oBREAK_HEADER
#define oBREAK_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) obreak 

{
public:
	obreak (size_t length);
	virtual ~ obreak ();
	obreak & print (char const *string);
private:
	char *mupper;
	char *mlower;
};


/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif

