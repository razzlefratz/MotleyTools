/*====================================================================*
 *
 *   obreak.cpp - implementation of the obreak class;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oBREAK_SOURCE
#define oBREAK_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/obreak.hpp"

/*====================================================================*
 *
 *   obreak & print(char const *string);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

obreak & obreak::print (char const *string) 

{
	std::cout << "# " << this->mupper <<"\n# " << string << ";\n# " << this->mlower << "\n\n";
	return (*this);
}


/*====================================================================*
 *
 *   obreak (size_t witdh)
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

obreak::obreak (size_t length) 

{
	this->mupper = new char [length + 1];
	this->mlower = new char [length + 1];
	for (size_t column = 0; column < length; column++) 
	{
		this->mupper [column] = '=';
		this->mlower [column] = '-';
	}
	this->mupper [length] = (char) (0);
	this->mlower [length] = (char) (0);
	return;
}


/*====================================================================*
 *
 *   ~obreak ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

obreak::~obreak () 

{
	delete [] this->mupper;
	delete [] this->mlower;
	return;
}


/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif

