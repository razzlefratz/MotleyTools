/*====================================================================*
 *
 *   opassword.hpp - interface for the opassword class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oPASSWORD_HEADER
#define oPASSWORD_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <climits>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *   declare interfaces;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) opassword 

{
public:
	opassword (unsigned seed);
	virtual ~ opassword ();
	unsigned count () const;
	unsigned space () const;
	unsigned group () const;
	opassword & count (unsigned count);
	opassword & space (unsigned space);
	opassword & group (unsigned group);
	opassword & print (unsigned value);
private:
	unsigned mindex;
	unsigned mcount;
	unsigned mgroup;
	char * mcharset;
	char mbreak;
};


/*====================================================================*
 *   end declarations;
 *--------------------------------------------------------------------*/

#endif

