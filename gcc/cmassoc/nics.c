/*====================================================================*
 *
 *   nics.c - network interface enumerator;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <memory.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/getoptv.h"
#include "../tools/putoptv.h"
#include "../tools/version.h"
#include "../tools/error.h"
#include "../tools/memory.h"
#include "../tools/types.h"
#include "../ether/ether.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/error.c"
#include "../tools/hexdecode.c"
#include "../tools/decdecode.c"
#include "../tools/hexstring.c"
#include "../tools/decstring.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../ether/hostnics.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define NICS 32

/*====================================================================*
 *
 *   static bool ignore (struct nic * nic);
 *
 *   return true if the interface ethernet address is either all
 *   zeros or all ones, indicating the interface is either disabled
 *   or not in use;
 *
 *--------------------------------------------------------------------*/

static bool disabled (struct nic * nic)

{
	byte address [ETHER_ADDR_LEN];
	memset (address, 0x00, sizeof (address));
	if (! memcmp (address, nic->ethernet, sizeof (address)))
	{
		return (true);
	}
	memset (address, 0xFF, sizeof (address));
	if (! memcmp (address, nic->ethernet, sizeof (address)))
	{
		return (true);
	}
	return (false);
}

/*====================================================================*
 *
 *   int main (int argc, char const * argv []);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv [])

{
	static char const * optv [] =
	{
		"",
		PUTOPTV_S_DIVINE,
		"Ethernet Interface Enumerator",
		(char const *) (0)
	};
	char string [ETHER_ADDR_LEN * 3];
	struct nic nics [NICS];
	struct nic * nic = nics;
	unsigned size = hostnics (nics, NICS);
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (argc)
	{
		error (1, ENOTSUP, ERROR_TOOMANY);
	}
	while (size--)
	{
		if (! disabled (nic))
		{
			printf (" %d", nic->ifindex);
			printf (" %s", hexstring (string, sizeof (string), nic->ethernet, sizeof (nic->ethernet)));
			printf (" %s", decstring (string, sizeof (string), nic->internet, sizeof (nic->internet)));
			printf (" %s", nic->ifname);
			printf (" %s", nic->ifdesc);
			printf ("\n");
		}
		nic++;
	}
	return (0);
}

