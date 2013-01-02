/*====================================================================*
 *
 *   osection.cpp - implementation of the osection class;
 *
 *   format and output script file comments used as section headers;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oSECTION_SOURCE
#define oSECTION_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/osection.hpp"

/*====================================================================*
 *
 *   osection & width (size_t width)
 *
 *   
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

osection & osection::width (size_t width) 

{
	this->mupper = new char [width + 1];
	this->mlower = new char [width + 1];
	this->mupper [width] = (char) (0);
	this->mlower [width] = (char) (0);
	while (width-- > 0) 
	{
		this->mupper [width] = '=';
		this->mlower [width] = '-';
	}
	return (*this);
}


/*====================================================================*
 *
 *   osection & title (char const *title) 
 *
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

osection & osection::title (char const *title) 

{
	std::cout << "\n";
	std::cout << this->mstart << " " << this->mupper << "\n";
	std::cout << this->mstart << " " << title << ";\n";
	std::cout << this->mstart << " " << this->mlower << "\n";
	std::cout << "\n";
	return (*this);
}


/*====================================================================*
 *
 *   osection ()
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

osection::osection () 

{
	this->mstart = new char [2];
	this->mstart [0] = '#';
	this->mstart [1] = (char)(0);
	this->mupper = new char [1];
	this->mlower = new char [1];
	this->mupper [0] = (char) (0);
	this->mlower [0] = (char) (0);
	return;
}


/*====================================================================*
 *
 *   ~osection ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

osection::~osection () 

{
	delete [] this->mstart;
	delete [] this->mupper;
	delete [] this->mlower;
	return;
}


/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif

