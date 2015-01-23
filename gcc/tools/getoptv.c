/*====================================================================*
 *
 *   int getoptv (int argc, char const * argv[], char const * optv[]);
 *
 *   getoptv.h
 *
 *   this is a posix compliant getopt() function that supports no 
 *   extensions; see the posix website for specification details; 
 *
 *   <http://www.opengroup.org/onlinepubs/007904975/functions/getopt.html>
 *
 *   we implemented this function to ensure that linux and windows
 *   consoles act the same; microsoft c++ would not compile the 
 *   debian version of getopt and so, after trying to fix things, 
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
 *   we declare optarg as "char const *" so that the target cannot
 *   be changed by the application; this is not POSIX compliant so
 *   it will conflict with other getopt variants; getopt.h is often
 *   included with unistd.h which is a common file;
 *
 *   to avoid compile conflicts, define _GETOPT_H on debian systems,
 *   __GETOPT_H__ on cygwin systems and _GETOPT_DEFINED_ on apple
 *   systems.
 *
 *   this version calls virtually no functions and should compile 
 *   on any posix system; 
 *
 *   you may include getoptv.h or declare these variables:
 *
 *    extern char const *optarg;
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
 *    while ((c = getoptv(argc, argv, *optv)) != -1)
 *    {
 *       switch(c)
 *       {
 *          case 'a': // optopt is 'a'; optarg is NULL;
 *          case 'b': // optopt is 'b'; optarg is operand;
 *          case ':': // optopt is option; optarg is NULL; missing operand;
 *          case '?': // optopt is option; optarg is NULL; illegal option; 
 *           default: // optopt is option: optarg is NULL; illegal option; 
 *       }
 *    }
 *
 *    after options and operands are processed, optind points to
 *    the next argv [] string; loop until optind equals argc or 
 *    argv[optind] is NULL; we check both but either will do; 
 *
 *    while ((optind < argc) && (argv [optind]))
 *    {
 *       // do stuff to argv[optind++].
 *    }
 *
 *   alternately, and even better, the following works just fine:
 *
 *    argc -= optind;
 *    argv += optind;
 *    while ((argc) && (*argv))
 *    {
 *       // do stuff to *argv.
 *
 *    }
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef GETOPTV_SOURCE
#define GETOPTV_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../tools/getoptv.h"
#include "../tools/putoptv.h"
#include "../tools/version.h"
#include "../tools/error.h"

char const * program_name = "program";
char * optarg = (char *) (0);
signed optopt = (char) (0);
signed optind = 1;
signed opterr = 1;
signed optmin = 0;
signed getoptv (int argc, char const * argv [], char const * optv [])

{
	static char const * string;
	static char const * option;
	static signed count;
	signed index = 0;

#ifdef GETOPTV_TRACE
#define SPACE "   "
#define ARROW "-->"

	while (index < argc)
	{
		fprintf (stderr, "%sargv[%d]=[%s]\n", (index == optind)? ARROW: SPACE, index, argv [index]);
		index++;
	}
	fprintf (stderr, "%sargv[index]=NULL\n\n", (index == optind)? ARROW: SPACE);

#endif

	if ((optind == 0) || (optind == 1))
	{
		for (program_name = string = * argv; * string; string++)
		{
			if ((* string == '/') || (* string == '\\'))
			{
				program_name = string + 1;
			}
		}
		string = (char *) (0);

#ifdef GETOPTV_DEBUG

		for (option = * optv; * option; option++)
		{
			if (* option == ':')
			{
				continue;
			}
			for (count = PUTOPTV_I_DETAILS; optv [count]; count++)
			{
				if (* option == * optv [count])
				{
					break;
				}
			}
			if (optv [count])
			{
				continue;
			}

#ifdef __GNUC__

			error (0, 0, "option '%c' has no description", * option);

#else

			fprintf (stderr, "%s: option '%c' has no description\n", program_name, * option);

#endif

		}
		for (count = 2; optv [count]; count++)
		{
			for (option = optv [3]; * option; option++)
			{
				if (* option == ':')
				{
					continue;
				}
				if (* option == * optv [count])
				{
					break;
				}
			}
			if (* option)
			{
				continue;
			}

#ifdef __GNUC__

			error (0, 0, "description \"%s\" has no option", optv [count]);

#else

			fprintf (stderr, "%s: description \"%s\" has no option\n", program_name, optv [count]);

#endif

		}

#endif

		if (argc == optmin)
		{
			putoptv (optv);
			exit (0);
		}
		count = optind = 1;
	}
	while ((count < argc) || (string))
	{
		if (string)
		{
			if (* string)
			{
				optarg = (char *) (0);
				optopt = * string++;
				for (option = * optv; * option; option++)
				{
					if (optopt == GETOPTV_C_OPERAND)
					{
						continue;
					}
					if (* option == GETOPTV_C_OPERAND)
					{
						continue;
					}
					if (* option == optopt)
					{
						option++;
						if (* option == GETOPTV_C_IGNORE)
						{
							option++;

#if __GNUC__

							error (0, 0, "option '%c' is deprecated", optopt);

#else

							fprintf (stderr, "%s: option '%c' is deprecated", program_name, optopt);

#endif

							return (optopt);
						}
						if (* option != GETOPTV_C_OPERAND)
						{
							return (optopt);
						}
						if (* string)
						{
							optarg = (char *) (string);
							string = (char *) (0);
							return (optopt);
						}
						if (count < argc)
						{
							optarg = (char *) (argv [count]);
							for (index = count++; index > optind; index--)
							{
								argv [index] = argv [index -1];
							}
							argv [optind++] = optarg;
							return (optopt);
						}
						if (opterr)
						{

#ifdef __GNUC__

							error (1, 0, "option '%c' has no operand", optopt);

#else

							fprintf (stderr, "%s: option '%c' has no operand\n", program_name, optopt);
							exit (1);

#endif

						}
						if (** optv == GETOPTV_C_OPERAND)
						{
							return (GETOPTV_C_OPERAND);
						}
						return (GETOPTV_C_ILLEGAL);
					}
				}
				if (opterr)
				{

#ifdef __GNUC__

					error (1, 0, "option '%c' has no meaning", optopt);

#else

					fprintf (stderr, "%s: option '%c' has no meaning\n", program_name, optopt);
					exit (1);

#endif

				}
				return (GETOPTV_C_ILLEGAL);
			}
			else 
			{
				string = (char *) (0);
			}
		}
		if (count < argc)
		{
			string = argv [count];
			if (* string == GETOPTV_C_OPTION)
			{
				for (index = count; index > optind; index--)
				{
					argv [index] = argv [index -1];
				}
				argv [optind++] = string++;
				if (* string == GETOPTV_C_VERSION)
				{
					version ();
					exit (0);
				}
				if (* string == GETOPTV_C_SUMMARY)
				{
					putoptv (optv);
					exit (0);
				}
				if (* string == GETOPTV_C_OPTION)
				{
					string++;
					if (! strcmp (string, ""))
					{
						optarg = (char *) (0);
						optopt = (char) (0);
						return (-1);
					}
					if (! strcmp (string, "version"))
					{
						version ();
						exit (0);
					}
					if (! strcmp (string, "help"))
					{
						putoptv (optv);
						exit (0);
					}
					optarg = (char *) (string);
					optopt = GETOPTV_C_OPTION;
					return (-1);
				}
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



