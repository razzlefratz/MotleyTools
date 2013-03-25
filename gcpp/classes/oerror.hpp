/*====================================================================*
 *
 *   oerror.hpp - interface for the oerror class.
 *
 *   this class implements the useful GNU error() and error_at_line()
 *   functions with some additions;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oERROR_HEADER
#define oERROR_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/types.h"

/*====================================================================*
 *   class declarations;
 *--------------------------------------------------------------------*/

class oerror 

{
public:
	oerror ();
	virtual ~ oerror ();
	static void print (char const *format, ...);
	static void error (char const *format, ...);
	static void syntax (char const * file, unsigned line, char const * format, ...);
	static void error (signed status, errno_t number, char const * format, ...);
	static void error (signed status, char const * string, char const * format, ...);
	static void error_at_line (signed status, errno_t number, char const * file, unsigned line, char const * format, ...);
};


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

