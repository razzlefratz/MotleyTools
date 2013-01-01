/*====================================================================*
 *
 *   int getoptv (int argc, char const *argv[], char const *optv[]);
 *
 *   this is a posix compliant getopt() function that supports no 
 *   extensions; see the posix website for specification details; 
 *
 *   <http://www.opengroup.org/onlinepubs/007904975/functions/getopt.html>
 *
 *   we implemented this function to ensure that linux and windows
 *   console s act the same; microsoft c++ would not compile 
 *   the debian version of getopt and so, after trying to fix things, 
 *   we decided to start fresh; the debian version is too complex;
 *
 *   this function conforms to posix standard; it does not support
 *   gnu style extensions like "--option" for arguments or "ab::c" 
 *   for operands; if you don't know what that means then you won't 
 *   care, either; you should avoid such extentions, anyway;
 *
 *   the posix standard says that command options and operands must 
 *   precede other arguments; this version of getopt allows options
 *   and operands to appear anywhere and makes non-compliant argv[]
 *   compliant in the process;
 *
 *   we define characters instead of coding them so that microsoft
 *   folks can use '/' instead of '-' and still preserve the posix 
 *   behaviour;
 *
 *   this version calls virtually no functions and should compile 
 *   on any posix system; 
 *
 *   debian getopt() is not posix compliant; they include getopt.h 
 *   in unistd.h; to avoid declaration conflicts, define _GETOPT_H
 *   before including any of their header files;  
 *
 *   you may include our getopt.h or declare these variables:
 *
 *    extern char *optarg;
 *    extern int optopt;
 *    extern int optind;
 *    extern int opterr;
 *
 *   you may cut and paste this c language code segment to get you 
 *   started; you must insert your own code and case breaks;
 *
 *    signed c;
 *    optind = 1;
 *    opterr = 1;
 *
 *    while ((c = getopt(argc, argv, ":ab:c")) != -1)
 *    {
 *       switch(c)
 *       {
 *          case 'a': // optopt is 'a'; optarg is NULL;
 *          case 'b': // optopt is 'b'; optarg is operand;
 *          case ':': // optopt is option; optarg is NULL; missing operand;
 *          case '?': // optopt is option; optarg is NULL; illegal option; ;
 *           default: // optopt is option: optarg is NULL; illegal option; 
 *       }
 *    }
 *
 *    after options and operands are processed, optind points to
 *    the next argv[] string; continue until optind exceeds argc
 *    or argv[] is NULL; we always check both but either will do; 
 *
 *    while ((optind < argc) && (argv[optind] != (char *)(0))
 *    {
 *       // do stuff to argv[optind++].
 *    }
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef GETOPTV_SOURCE
#define GETOPTV_SOURCE

#define _GETOPT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#ifdef GETOPTV_NETWORK
#include <netdb.h>
#endif

#ifdef __GNUC__
#include <error.h>
#include <errno.h>
#endif

#include "../tools/getoptv.h"
#include "../tools/putoptv.h"
#include "../tools/version.h"
#ifdef GETOPTV_NETWORK
#include "../tools/sizes.h"
#endif

#ifdef GETOPTV_PROGRAM

char const *program_name = "program";

#endif
#ifdef GETOPTV_NETWORK

char const *domain_name = "";
char const *host_name = "localhost";

#endif

char const *optarg = (char *) (0);
signed optopt = (char) (0);
signed optind = 1;
signed opterr = 1;

#ifdef GETOPTV_NETWORK

static char hostname [HOSTNAME_MAX];

#endif

signed getoptv (int argc, char const *argv [], char const *optv []) 

{

#ifdef GETOPTV_NETWORK

	struct hostent *hostent;

#endif 

	static char const *string;
	static unsigned count;
	unsigned index;
	if ((optind == 0) || (optind == 1)) 
	{

#ifdef GETOPTV_NETWORK

		gethostname (hostname, sizeof (hostname));
		hostent = gethostbyname (hostname);
		if (hostent != (struct hostent *)(0)) 
		{
			strncpy (hostname, hostent->h_name, sizeof (hostname));
		}
		for (host_name = domain_name = hostname; *domain_name != (char)(0); domain_name++) 
		{
			if (*domain_name == '.') 
			{
				hostname [domain_name - host_name] = (char)(0);
				domain_name++;
				break;
			}
		}

#endif
#ifdef GETOPTV_PROGRAM

		for (program_name = string = *argv; *string != (char) (0); string++) 
		{
			if (*string == '/') 
			{
				program_name = string + 1;
			}
		}

#endif

		string = (char *) (0);
		count = optind = 1;
	}
	while ((count < argc) || (string != (char *) (0))) 
	{
		if (string != (char *) (0)) 
		{
			if (*string != (char) (0)) 
			{
				char const *option;
				optarg = (char *) (0);
				optopt = *string++;
				for (option = optv [PUTOPTV_I_OPTIONS]; *option != (char) (0); option++) 
				{
					if (optopt == GETOPT_C_OPERAND) 
					{
						continue;
					}
					if (*option == GETOPT_C_OPERAND) 
					{
						continue;
					}
					if (*option == optopt) 
					{
						option++;
						if (*option != GETOPT_C_OPERAND) 
						{
							return (optopt);
						}
						if (*string != (char) (0)) 
						{
							optarg = (char *) (string);
							string = (char *) (0);
							return (optopt);
						}
						if (count < argc) 
						{
							optarg = argv [count];
							for (index = count++; index > optind; index--) 
							{
								argv [index] = argv [index - 1];
							}
							argv [optind++] = optarg;
							return (optopt);
						}
						if (opterr > 0) 
						{

#ifdef __GNUC__

							error (1, 0, "option '%c' needs an operand", optopt);

#else

							fprintf (stderr, "%s: option '%c' needs an operand\n", program_name, optopt);

#endif

						}
						if (optv [PUTOPTV_I_OPTIONS][0] == GETOPT_C_OPERAND) 
						{
							return (GETOPT_C_OPERAND);
						}
						return (GETOPT_C_ILLEGAL);
					}
				}
				if (opterr > 0) 
				{

#ifdef __GNUC__

					error (1, 0, "option '%c' has no meaning", optopt);

#else

					fprintf (stderr, "%s: option '%c' has no meaning\n", program_name, optopt);

#endif

				}
				return (GETOPT_C_ILLEGAL);
			}
			else 
			{
				string = (char *) (0);
			}
		}
		else if (count < argc) 
		{
			string = argv [count];
			if (*string == GETOPT_C_OPTION) 
			{
				for (index = count; index > optind; index--) 
				{
					argv [index] = argv [index - 1];
				}
				argv [optind++] = string++;
				if (*string == GETOPT_C_OPTION) 
				{
					if (*++string == (char) (0)) 
					{
						break;
					}

#ifdef GETOPTV_VERSION 

					if (strcmp (string, "version") == 0) 
					{
						version ();
						exit (0);
					}

#endif
#ifdef GETOPTV_SUMMARY 

					if (strcmp (string, "help") == 0) 
					{
						putoptv (optv);
						exit (0);
					}

#endif

				}

#ifdef GETOPTV_VERSION 

				if (*string == GETOPT_C_VERSION) 
				{
					version ();
					exit (0);
				}

#endif
#ifdef GETOPTV_SUMMARY 

				if (*string == GETOPT_C_SUMMARY) 
				{
					putoptv (optv);
					exit (0);
				}

#endif

			}
			else 
			{
				string = (char *) (0);
			}
			count++;
		}
	}
	optarg = (char *) (0);
	optopt = (char) (0);
	return (-1);
}


#endif

