/*====================================================================*
 *
 *   opcap.hpp - interface for the opcap class  
 *
 *   host interface information;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oPCAP_HEADER
#define oPCAP_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <net/if.h>
#include <net/ethernet.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) opcap 

{
public:
	opcap ();
	virtual~ opcap ();
	static unsigned if_nametoindex (char const * ifname);
	static char * if_indextoname (unsigned ifindex, char * ifname);
	static struct if_nameindex * if_nameindex (void);
	static void if_freenameindex (struct if_nameindex * if_nameindex);
};


/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif

