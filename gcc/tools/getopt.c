/*====================================================================*
 *
 *   int getopt (int argc, char *argv[], char const *options);
 *
 *   this is a posix compliant getopt() function that supports no 
 *   extensions; see the posix website for specification details; 
 *
 *   <http://www.opengroup.org/onlinepubs/007904975/functions/getopt.html>
 *
 *   we implemented this function to ensure that linux and windows
 *   console programs act the same; microsoft c++ would not compile 
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

#ifndef GETOPT_SOURCE
#define GETOPT_SOURCE

#if defined (__linux__)
#define _GETOPT_H
#elif  defined (__APPLE__)
#define _GETOPT_H_
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../tools/getopt.h"
#include "../tools/version.h"
#include "../tools/error.h"

char const *program_name = "";
char *optarg = (char *) (0);
signed optopt = (char) (0);
signed optind = 1;
signed opterr = 1;
signed getopt (int argc, char *argv [], char const *options) 

{
	static char *string;
	static unsigned count;
	unsigned index;
	if ((optind == 0) || (optind == 1)) 
	{
		for (program_name = string = argv [0]; *string != (char) (0); string++) 
		{
			if (*string == '/') 
			{
				program_name = string + 1;
			}
		}
		string = (char *) (0);
		count = optind = 1;
	}
	while ((count < argc) || (string != (char *) (0))) 
	{
		if (string) 
		{
			if (*string) 
			{
				char const *option;
				optarg = (char *) (0);
				optopt = *string++;
				for (option = options; *option != (char) (0); option++) 
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
						if (*option == GETOPTV_C_IGNORE) 
						{
							option++;

#if __GNUC__

							error (0, 0, "option '%c' is deprecated", optopt);

#else

							fprintf (stderr, "%s: option '%c' is deprecated", program_name, optopt);

#endif

							return (optopt);
						}
						if (*++option != GETOPT_C_OPERAND) 
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

							fprintf (stderr, "%s: option '%c' needs an operand.\n", program_name, optopt);
							exit (1);

#endif

						}
						if (*options == GETOPT_C_OPERAND) 
						{
							return (GETOPT_C_OPERAND);
						}
						return (GETOPT_C_ILLEGAL);
					}
				}
				if (opterr > 0) 
				{

#ifdef __GNUC__

					error (1, 0, "option '%c' has no meanin.g", optopt);

#else

					fprintf (stderr, "%s: option '%c' has no meaning\n", program_name, optopt);
					exit (1);

#endif

				}
				return (GETOPT_C_ILLEGAL);
			}
			else 
			{
				string = (char *) (0);
			}
		}
		if (count < argc) 
		{
			string = argv [count];
			if (*string == GETOPT_C_OPTION) 
			{
				for (index = count; index > optind; index--) 
				{
					argv [index] = argv [index - 1];
				}
				argv [optind++] = string++;

#if 0
#ifdef GETOPT_VERSION

				if (*string == GETOPT_C_VERSION) 
				{
					version ();
					exit (0);
				}

#endif
#ifdef GETOPT_SUMMARY

				if (*string == GETOPT_C_SUMMARY) 
				{
					exit (0);
				}

#endif
#endif

				if (*string == GETOPT_C_OPTION) 
				{
					if (*++string == (char)(0)) 
					{
						break;
					}
					else if (strcmp (string, "version") == 0) 
					{
						version ();
						exit (0);
					}
					else if (strcmp (string, "help") == 0) 
					{
						exit (0);
					}
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

