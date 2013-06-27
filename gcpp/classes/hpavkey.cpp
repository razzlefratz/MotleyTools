/*====================================================================*
 *
 *   hpavkey.cpp - 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstdio>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <errno.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ogetoptv.hpp"
#include "../classes/oputoptv.hpp"
#include "../classes/oversion.hpp"
#include "../classes/oerror.hpp"
#include "../classes/convert.h"
#include "../../gcc/tools/types.h"
#include "../classes/flags.h"
#include "../classes/oHPAVKey.hpp"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef CMASSOC_MAKEFILE
#include "../classes/ogetoptv.cpp"
#include "../classes/oputoptv.cpp"
#include "../classes/oversion.cpp"
#include "../classes/oerror.cpp"
#include "../classes/oflagword.cpp"
#include "../classes/oSHA256.cpp"
#include "../classes/oHPAVKey.cpp"
#endif

/*====================================================================*
 *    
 *   int main (int argc, char const *argv []);
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	static char const * optv [] = 
	{
		"DMNqv",
		PUTOPTV_S_FUNNEL,
		"HomePlug AV key generator",
		"D\thash DAK passwords",
		"M\thash NMK passwords",
		"N\thash NID passwords",
		(char const *) (0)
	};
	ogetoptv getopt (1);
	oputoptv putopt;
	oerror error;
	oHPAVKey key;
	const uint8_t * digest;
	char const * string;
	char const * sp;
	signed mode = 0;
	signed c;
	if (argc == 1) 
	{
		putopt.putoptv (optv);
	}
	while ((c = getopt.getoptv (argc, argv, optv)) != -1) 
	{
		switch ((char) (c)) 
		{
		case 'D':
			mode = HPAVKEY_DAK;
			break;
		case 'M':
			mode = HPAVKEY_NMK;
			break;
		case 'N':
			mode = HPAVKEY_NID;
			break;
		case 'q':
			key.clrbits (HPAVKEY_SILENCE);
			break;
		case 'v':
			key.setbits (HPAVKEY_VERBOSE);
			break;
		default:
			break;
		}
	}
	while ((getopt.argc ()) && (* getopt.argv ())) 
	{
		sp = string = * getopt.argv ();
		while (* sp != (char)(0)) 
		{
			if (((unsigned)(* sp) < 0x20) || ((unsigned)(* sp) > 0x7F)) 
			{
				break;
			}
			sp++;
		}
		if (* sp != (char)(0)) 
		{
			error.error (0, EINVAL, "string \"%s\" has illegal characters", string);
		}
		else if ((sp - string) < HPAVKEY_PHRASE_MIN) 
		{
			error.error (0, EINVAL, "string \"%s\" is less than %d characters", string, HPAVKEY_PHRASE_MIN);
		}
		else if ((sp - string) > HPAVKEY_PHRASE_MAX) 
		{
			error.error (0, EINVAL, "string \"%s\" is more than %d characters", string, HPAVKEY_PHRASE_MAX);
		}
		else if (mode == HPAVKEY_DAK) 
		{
			digest = key.DAK (string).digest ();
			key.show (digest, HPAVKEY_DAK_LEN, string);
		}
		else if (mode == HPAVKEY_NMK) 
		{
			digest = key.NMK (string).digest ();
			key.show (digest, HPAVKEY_NMK_LEN, string);
		}
		else if (mode == HPAVKEY_NID) 
		{
			digest = key.NID (string, 0).digest ();
			key.show (digest, HPAVKEY_NID_LEN, string);
		}
		else 
		{
			digest = key.SHA (string).digest ();
			key.show (digest, HPAVKEY_SHA_LEN, string);
		}
		getopt++;
	}
	exit (0);
}

