/*====================================================================*
 *
 *   odepend.hpp - interface for the odepend class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oDEPEND_HEADER
#define oDEPEND_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/oqueue.hpp"
#include "../classes/opathspec.hpp"
#include "../classes/oascii.hpp"

/*====================================================================*
 *   constants;
 *--------------------------------------------------------------------*/

#define oDEPEND_SYMBOL_LENGTH 1024

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) odepend: private opathspec, private oascii 

{
public:
	odepend ();
	odepend (char const * nodename);
	virtual~ odepend ();
	static odepend nodes;
	static oqueue queue;
	odepend & populate (char colon, char comma, bool invert);
	odepend & connect (char const * source, char const * target);
	odepend * store (char const * nodename);
	odepend * fetch (char const * nodename);
	odepend & enumerate ();
	odepend & structure ();
	odepend & component ();
	odepend & targets ();
	odepend & sources ();
private:
	odepend * mbelow;
	odepend * mprior;
	odepend * mafter;
	char * mstring;
};

/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif

