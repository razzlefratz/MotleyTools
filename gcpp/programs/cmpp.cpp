/*====================================================================*
 *
 *   cmpp.cpp - C Language Macro Preprocessor;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

/*====================================================================*
 *   system header files
 *--------------------------------------------------------------------*/

#include <cstdlib>
#include <iostream>

/*====================================================================*
 *   custom header files
 *--------------------------------------------------------------------*/

#include "../classes/ogetoptv.hpp"
#include "../classes/oputoptv.hpp"
#include "../classes/oerror.hpp"
#include "../classes/omacro.hpp"
#include "../classes/oscantext.hpp"
#include "../classes/oflagword.hpp"
#include "../classes/opathspec.hpp"
#include "../classes/ofindspec.hpp"
#include "../classes/ofilespec.hpp"
#include "../classes/ofileopen.hpp"
#include "../classes/ofindfile.hpp"
#include "../../gcc/chrlib/charset.h"
#include "../../gcc/files/files.h"

/*====================================================================*
 *   custom source files
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../../gcc/files/fopensearch.c"
#include "../classes/ogetoptv.cpp"
#include "../classes/oputoptv.cpp"
#include "../classes/oversion.cpp"
#include "../classes/oerror.cpp"
#include "../classes/osymbol.cpp"
#include "../classes/omacro.cpp"
#include "../classes/oqueue.cpp"
#include "../classes/opathspec.cpp"
#include "../classes/ofilespec.cpp"
#include "../classes/ofileopen.cpp"
#include "../classes/ofindfile.cpp"
#include "../classes/owildcard.cpp"
#include "../classes/oscantext.cpp"
#include "../classes/oflagword.cpp"
#include "../classes/ocursor.cpp"
#include "../classes/oascii.cpp"
#include "../classes/ochrlwr.cpp"
#include "../classes/ochrupr.cpp"
#include "../classes/oscantext.cpp"
#include "../classes/ocontext.cpp"
#include "../classes/ochrtbl.cpp"
#include "../classes/otext.cpp"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define CMPP_S_COMMAND "$"

#define CMPP_B_VERBOSE (1 << 0)
#define CMPP_B_SILENCE (1 << 1)
#define CMPP_B_INCLUDE (1 << 2)
#define CMPP_B_CONTENT (1 << 3)
#define CMPP_B_COMMENT (1 << 4)
#define CMPP_B_DEFAULT (CMPP_B_INCLUDE | CMPP_B_CONTENT | CMPP_B_COMMENT)

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

ofileopen fileopen;
opathspec pathspec;
omacro macro;
oerror error;

/*====================================================================*
 *
 *   void process (char const *pathname, char const * command, oflagword * flags);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static void process (char const * pathname, char const * command, oflagword * flags) 

{
	oscantext source;
	source.read (pathname);
	while (!source.isempty ()) 
	{
		if (source.flush ().scantoken ().istoken (command)) 
		{
			source.scanblank ().flush ().scantoken ();
			if (source.istoken ("include")) 
			{
				char fullpath [FILENAME_MAX] = "";
				char rootname [FILENAME_MAX] = "";
				char filename [FILENAME_MAX] = "";
				pathspec.findpath (pathname, rootname, filename);
				switch (source.scanblank ().character ()) 
				{
				case '\"':
					source.scanbreak ().flush ();
					source.scanuntil ('\"');
					pathspec.makepath (fullpath, rootname, source.tokentext ());
					source.scanbreak ();
					break;
				case '\'':
					source.scanbreak ().flush ();
					source.scanuntil ('\'');
					pathspec.makepath (fullpath, rootname, source.tokentext ());
					source.scanbreak ();
					break;
				case '<':
					source.scanbreak ().flush ();
					source.scanuntil ('>');
					pathspec.makepath (fullpath, rootname, source.tokentext ());
					source.scanbreak ();
					break;
				case '(':
					source.scanbreak ().flush ();
					source.scanuntil (')');
					pathspec.makepath (fullpath, rootname, source.tokentext ());
					source.scanbreak ();
					break;
				case '[':
					source.scanbreak ().flush ();
					source.scanuntil (']');
					pathspec.makepath (fullpath, rootname, source.tokentext ());
					source.scanbreak ();
					break;
				default:
					source.flush ();
					source.scanuntil (gcsSpace);
					pathspec.makepath (fullpath, rootname, source.tokentext ());
					break;
				}
				if (flags->anyset (CMPP_B_INCLUDE)) 
				{
					process ((char const *) (fullpath), command, flags);
				}
				source.scanquote (gcsBreak);
				source.scanwhile (gcsBreak);
			}
			else if (source.istoken ("define")) 
			{
				source.scanblank ().flush ();
				source.scanquote (gcsBreak);
				macro.define (source.tokentext ());
				source.scanwhile (gcsBreak);
			}
			else if (source.istoken ("undef")) 
			{
				source.scanblank ().flush ();
				source.scanquote (gcsBreak);
				macro.revert (source.tokentext ());
				source.scanwhile (gcsBreak);
			}
			else if (source.istoken ("ifdef")) 
			{
				source.scanblank ().flush ();
				source.scanquote (gcsBreak);
				source.scanwhile (gcsBreak);
			}
			else if (source.istoken ("ifndef")) 
			{
				source.scanblank ().flush ();
				source.scanquote (gcsBreak);
				source.scanwhile (gcsBreak);
			}
			else if (source.istoken ("else")) 
			{
				source.scanblank ().flush ();
				source.scanquote (gcsBreak);
				source.scanwhile (gcsBreak);
			}
			else if (source.istoken ("endif")) 
			{
				source.scanblank ().flush ();
				source.scanquote (gcsBreak);
				source.scanwhile (gcsBreak);
			}
			else if (source.istoken ("enumerate")) 
			{
				source.scanblank ();
				source.flush ();
				source.scanquote (gcsBreak);
				macro.enumerate (pathname);
				source.scanwhile (gcsBreak);
			}
			else 
			{
				source.unget ();
			}
			continue;
		}

/*
 * scan C Language comments;
 */

		if (source.isclass ('/')) 
		{
			if (source.havebreak ('*')) 
			{
				source.scanblock ();
				source.scanmatch ();
				if (flags->anyset (CMPP_B_COMMENT)) 
				{
					source.write ();
				}
				continue;
			}
			if (source.havebreak ("/")) 
			{
				source.scanquote ('\n');
				source.scanbreak ('\n');
				if (flags->anyset (CMPP_B_COMMENT)) 
				{
					source.write ();
				}
				continue;
			}
		}
		if (source.isclass ("_A")) 
		{
			if (macro.defined (source.scanident ().tokentext ())) 
			{
				source.scanspace ();
				if (source.havebreak ('(')) 
				{
					source.scangroup (')');
					source.scanbreak (')');
				}
				else 
				{
					source.trimtoken ();
				}
				if (flags->anyset (CMPP_B_VERBOSE)) 
				{
					error.error (0, 0, "%s: expand %s", pathname, source.tokentext ());
				}
				source.unget (macro.expand (source.tokentext ()));
				continue;
			}
		}
		if (flags->anyset (CMPP_B_CONTENT)) 
		{
			source.write ();
		}
	}
	return;
}

/*====================================================================*
 *
 *   int main (int argc, char const * argv []);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv [], char const * envp []) 

{
	static char const * optv [] = 
	{
		"c:dev",
		oPUTOPTV_S_FUNNEL,
		"copy files to stdout and expand macro definitions",
		"c c\tdirective prefix is (c) ['" CMPP_S_COMMAND "']",
		"d\tprint definitions on stderr",
		"e\tprint expansions on stderr",
		"v\tverbose messages",
		(char const *) (0)
	};
	ogetoptv getopt;
	oflagword flags;
	char const * command = CMPP_S_COMMAND;
	signed c;
	while ((c = getopt.getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'c':
			command = getopt.optarg ();
			break;
		case 'd':
			macro.setbits (oMACRO_B_DEFINE);
			break;
		case 'e':
			macro.setbits (oMACRO_B_EXPAND);
			break;
		case 'N':
			flags.setbits (CMPP_B_COMMENT);
			break;
		case 'C':
			flags.setbits (CMPP_B_CONTENT);
			break;
		case 'I':
			flags.setbits (CMPP_B_INCLUDE);
			break;
		case 'q':
			flags.setbits (CMPP_B_SILENCE);
			break;
		case 'v':
			flags.setbits (CMPP_B_VERBOSE);
			break;
		default:
			break;
		}
	}
	if (flags.allclear (CMPP_B_DEFAULT)) 
	{
		flags.setbits (CMPP_B_DEFAULT);
	}
	while (getopt.argc () && * getopt.argv ()) 
	{
		process (* getopt.argv (), command, & flags);
		getopt++;
	}
	std::exit (0);
}

