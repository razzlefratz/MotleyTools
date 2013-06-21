/*====================================================================*
 *
 *   oifs.hpp - interface for the oifs class  
 *
 *   host interface enumerator;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oIFS_HEADER
#define oIFS_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdint.h>
#include <net/if.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/oif.hpp"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oifs 

{
public:
	oifs ();
	virtual~ oifs ();
	unsigned Count (void) const;
	unsigned Index (void) const;
	oifs & Select (unsigned);
	oifs & SelectPrev ();
	oifs & SelectNext ();
	oifs & SelectFirst ();
	oifs & SelectFinal ();
	oifs & Enumerate (void);
	oif & Selected () const;
	oif & operator [] (unsigned);
	oifs & operator -- (signed);
	oifs & operator ++ (signed);
private:
	oif * mtable;
	unsigned mcount;
	unsigned mindex;
};


/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif

