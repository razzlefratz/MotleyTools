/*====================================================================*
 *
 *   oversion.cpp - implementation of the oversion class.
 *
 *   this class
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oVERSION_SOURCE
#define oVERSION_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oversion.hpp"

/*====================================================================*
 *
 *   oversion & version (void);
 *
 *   print usage vector on stderr; this presents the user with a help
 *   summary; program_name is defined in ogetoptv::getoptv() but it could be
 *   defined in main or another component; getoptv.h is included above
 *   for GETOPTV_C_OPTIONS which is normally '-' but could be anything; 
 *
 *--------------------------------------------------------------------*/

oversion & oversion::version (void) 

{
	extern char const * program_name;
	std::cerr << program_name << " ";
	std::cerr << PACKAGE << "-";
	std::cerr << VERSION << ".";
	std::cerr << RELEASE << " ";
	std::cerr << "C++" << " ";
	std::cerr << COMPANY << " ";
	std::cerr << __TIME__ << " ";
	std::cerr << __DATE__ << std::endl;
	return (*this);
}


/*====================================================================*
 *
 *   oversion ();
 *
 *--------------------------------------------------------------------*/

oversion::oversion () 

{
	return;
}


/*====================================================================*
 *   
 *   ~oversion ();
 *
 *--------------------------------------------------------------------*/

oversion::~oversion () 

{
	return;
}


/*====================================================================*
 *   end implementation
 *--------------------------------------------------------------------*/

#endif

