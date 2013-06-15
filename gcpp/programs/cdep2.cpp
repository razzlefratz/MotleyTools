/*====================================================================*
 *
 *   cdep2.cpp - output c language include file dependency list;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <cstdlib>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ogetoptv.hpp"
#include "../classes/oerror.hpp"
#include "../classes/oqueue.hpp"
#include "../classes/odepend.hpp"
#include "../classes/oscantext.hpp"
#include "../classes/ofilespec.hpp"
#include "../classes/opathspec.hpp"
#include "../classes/oflagword.hpp"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../classes/ogetoptv.cpp"
#include "../classes/oputoptv.cpp"
#include "../classes/oversion.cpp"
#include "../classes/oerror.cpp"
#include "../classes/oflagword.cpp"
#include "../classes/ocontext.cpp"
#include "../classes/oscantext.cpp"
#include "../classes/oascii.cpp"
#include "../classes/ochrupr.cpp"
#include "../classes/ochrlwr.cpp"
#include "../classes/ocursor.cpp"
#include "../classes/owildcard.cpp"
#include "../classes/oqueue.cpp"
#include "../classes/odepend.cpp"
#include "../classes/ofilespec.cpp"
#include "../classes/opathspec.cpp"
#include "../classes/ochrtbl.cpp"
#include "../classes/otext.cpp"
#endif

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#define DEPEND_B_CUSTOM (1 << 0)
#define DEPEND_B_SYSTEM (1 << 1)
#define DEPEND_B_INVERT (1 << 2)
#define DEPEND_B_REPORT (1 << 3)
#define DEPEND_B_MAKEFILE (1 << 4)

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

static opathspec pathspec;
static ofilespec filespec;
static oscantext scantext;
static odepend sources ("project");
static char const * folders [] = 

{
	"/usr/include",
	"/usr/local/include",
	"/usr/lib/gcc-lib/i386-linux/2.95.4/include",
	"/usr/lib/gcc-lib/i386-linux/3.0.4/include",
	"/usr/include/c++/3.3",
	(char const*) (0)
};


/*====================================================================*
 *
 *   void relate (char const *one, char const *two, oflagword * flags);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static void relate (char const * one, char const * two, oflagword * flags) 

{
	if (flags->anyset (DEPEND_B_INVERT)) 
	{
		sources.connect (two, one);
	}
	else 
	{
		sources.connect (one, two);
	}
	return;
}


/*====================================================================*
 *
 *   void function (char const *target, size_t length, oflagword * flags);
 *
 *   search the named target file for include files; relate pathnames for
 *   subsequent output;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static void function (char const * target, size_t length, oflagword * flags) 

{
	std::ifstream stream;
	char source [FILENAME_MAX] = "";
	char buffer [length];
	unsigned line;
	stream.open (target, std::ifstream::in);
	if (stream.good ()) 
	{
		filespec.filespec (target);
		for (line = 1; !stream.getline (buffer, length).eof (); line++) 
		{
			scantext.copy (buffer).nexttoken ();
			if (!scantext.havetoken ("#")) 
			{
				continue;
			}
			if (!scantext.havetoken ("include")) 
			{
				continue;
			}
			if (scantext.havetoken ("<")) 
			{
				scantext.scanuntil (">");
				if (flags->anyset (DEPEND_B_SYSTEM)) 
				{
					if (pathspec.invector (source, folders, scantext.tokentext (), false)) 
					{
						relate (target, source, flags);
						continue;
					}
					if (pathspec.invector (source, folders, scantext.tokentext (), true)) 
					{
						relate (target, source, flags);
						continue;
					}
					oerror::print ("can't find <%s> included by %s (%d)", scantext.tokentext (), target, line);
				}
				continue;
			}
			if (scantext.havetoken ("\"")) 
			{
				scantext.scanuntil ("\"");
				if (flags->anyset (DEPEND_B_CUSTOM)) 
				{
					pathspec.makepath (source, filespec.basename (), scantext.tokentext ());
					relate (target, source, flags);
				}
				continue;
			}
		}
		if (line == 1) 
		{
			oerror::print ("target %s is empty.", target);
		}
	}
	stream.close ();
	return;
}


/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	static char const * optv [] = 
	{
		"csmnfI",
		oPUTOPTV_S_FUNNEL,
		"list supporting c language include files on stdout",
		"c\tcustom include files",
		"s\tsystem include files",
		"m\tmakefile template",
		"n\tneed summary",
		"f\tfeed summary",
		"I s\tsearch include folder s",
		(char const *) (0)
	};
	ogetoptv getopt;
	oflagword flags;
	size_t length = FILENAME_MAX;
	signed c;
	while ((c = getopt.getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'n':
			flags.setbits (DEPEND_B_REPORT);
			flags.clearbits (DEPEND_B_INVERT);
			break;
		case 'f':
			flags.setbits (DEPEND_B_REPORT);
			flags.setbits (DEPEND_B_INVERT);
			break;
		case 's':
			flags.setbits (DEPEND_B_SYSTEM);
			break;
		case 'c':
			flags.setbits (DEPEND_B_CUSTOM);
			break;
		case 'm':
			flags.setbits (DEPEND_B_MAKEFILE);
			break;
		default:
			break;
		}
	}
	if (flags.allclear (DEPEND_B_SYSTEM | DEPEND_B_CUSTOM)) 
	{
		oerror::print ("specify a search type!");
		return (1);
	}
	while ((getopt.argc ()) && (* getopt.argv ())) 
	{
		char filename [FILENAME_MAX + 1];
		pathspec.fullpath (filename, * getopt.argv ());
		odepend::nodes.store (filename);
		getopt++;
	}
	while (!odepend::queue.empty ()) 
	{
		odepend::nodes.store ((char *)(odepend::queue.head ()->data ()));
		function ((char *) (odepend::queue.head () ->data ()), length, &flags);
		odepend::queue.remove ();
	}
	if (flags.anyset (DEPEND_B_REPORT)) 
	{
		sources.structure ();
		return (0);
	}
	if (flags.anyset (DEPEND_B_MAKEFILE)) 
	{
		sources.targets ();
		return (0);
	}
	sources.enumerate ();
	std::exit (0);
}


