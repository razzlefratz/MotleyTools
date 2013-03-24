/*====================================================================*
 *
 *   oversion.hpp - declarations of the oversion class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oVERSION_HEADER
#define oVERSION_HEADER

/*====================================================================*
 *   custom header files; 
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#define COMPANY "Charles Maier"
#define PROJECT "Motley Toolkit"
#define PACKAGE "motley-tools"
#define VERSION "1.8"
#define RELEASE "3"
#define COMPILE __TIME__ " " __DATE__
#define CONTACT "cmaier@cmassoc.net"
#define LICENSE "Internet Software Consortium License"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oversion 

{
public:
	oversion ();
	virtual ~ oversion ();
	oversion & print ();
private:
};


/*====================================================================*
 *   end declarations
 *--------------------------------------------------------------------*/

#endif

