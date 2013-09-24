/*====================================================================*
 *
 *   ipsort.c -
 *
 *   read stdin and write stdout; print an collateed slist of dotted   
 *   decimal IPv4 addresses with optional counts;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *%  Packaged as cmassoc-tools-1.4.2 by cmaier@cmassoc.net;
 *
 *--------------------------------------------------------------------*/

#define _GETOPT_H

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../ether/IPAddr.h"
#include "../strlib/strlib.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/version.c"
#include "../tools/efreopen.c"
#include "../tools/emalloc.c"
#include "../tools/uintspec.c"
#include "../tools/fgetline.c"
#include "../tools/todigit.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../ether/getIPv4.c"
#include "../ether/IsIPv4.c"
#endif

#ifndef MAKEFILE
#include "../strlib/strsplit.c"
#endif

/*====================================================================*
 *   program constants;  
 *--------------------------------------------------------------------*/

#define IPSORT_COUNT (1 << 0)

/*====================================================================*
 *   program variables;  
 *--------------------------------------------------------------------*/

char const * rootnode = "%d.";
char const * leafnode = "%d";
typedef struct _tree_

{
	struct _tree_ * one;
	struct _tree_ * two;
	struct _tree_ * sub;
	unsigned value;
	unsigned count;
}

TREE;

/*====================================================================*
 *
 *   TREE * catalog (TREE * node, char const * value []);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

TREE * catalog(TREE * node, const unsigned value[])

{
	if (* value != END)
	{
		if (node == (TREE *)(0))
		{
			node = NEW(TREE);
			node->one = node->two = node->sub = (TREE *)(0);
			node->value = * value;
			node->count = 0;
		}
		if (* value < node->value)
		{
			node->one = catalog(node->one, value);
		}
		else if(* value > node->value)
		{
			node->two = catalog(node->two, value);
		}
		else 
		{
			node->sub = catalog(node->sub, value +  1);
			node->count++;
		}
	}
	return (node);
}

/*====================================================================*
 *
 *   void collate (TREE * node, char buffer[], size_t actual, size_t length);
 *
 *
 *
 *--------------------------------------------------------------------*/

void collate(TREE * node, char buffer[], size_t length, size_t offset, flag_t flags)

{
	extern char const * rootnode;
	extern char const * leafnode;
	if (node != (TREE *)(0))
	{
		size_t count = offset;
		collate (node->one, buffer, length, offset, flags);
		if (node->sub != (TREE *)(0))
		{
			count += snprintf(buffer +  count, length - count, rootnode, node->value);
			collate (node->sub, buffer, length - count, count, flags);
		}
		else 
		{
			count += snprintf(buffer +  count, length - count, leafnode, node->value);
			if (flags & IPSORT_COUNT)
			{
				printf ("%6d ", node->count);
			}
			printf ("%s\n", buffer);
		}
		collate (node->two, buffer, length, offset, flags);
	}
	return;
}

/*====================================================================*
 *
 *   int main (int argc, char const * argv[]);
 *
 *
 *
 *--------------------------------------------------------------------*/

int main(int argc, char const * argv[])

{
	extern char const * rootnode;
	extern char const * leafnode;
	static char const * optv[] = 
	{
		"an",
		"ipaddr [ipaddr] [...]",
		"copy one or more files to stdout",
		"a\talign octet fields",
		"n\tprint occurances",
		(char const *)(0)
	};
	TREE * tree = (TREE *)(0);
	char buffer[TEXTLINE_MAX];
	char const * strings[IP_ADDR_OCTETS +  1];
	unsigned values[IP_ADDR_OCTETS +  1];
	flag_t flags = (flag_t)(0);
	signed c;
	while (~ (c = getoptv(argc, argv, optv)))
	{
		switch (c)
		{
		case 'a':
			rootnode = "%3d.";
			leafnode = "%3d";
			break;
		case 'n':
			_setbits (flags, IPSORT_COUNT);
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (! argc)
	{
		while (getIPv4(buffer, sizeof(buffer), stdin))
		{
			strsplit (strings, IP_ADDR_OCTETS +  1, buffer, IP_ADDR_EXTENDER);
			for (c = 0; strings[c] != (char *)(0); c++)
			{
				values [c] = atoi(strings[c]);
			}
			values [c] = END;
			tree = catalog(tree, values);
		}
	}
	while ((argc) && (* argv))
	{
		if (efreopen(* argv, "rb", stdin))
		{
			while (getIPv4(buffer, sizeof(buffer), stdin))
			{
				strsplit (strings, IP_ADDR_OCTETS +  1, buffer, IP_ADDR_EXTENDER);
				for (c = 0; strings[c]; c++)
				{
					values [c] = atoi(strings[c]);
				}
				values [c] = END;
				tree = catalog(tree, values);
			}
		}
		argc--;
		argv++;
	}
	collate (tree, buffer, sizeof(buffer), 0, flags);
	exit (0);
}

