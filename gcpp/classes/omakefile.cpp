/*====================================================================*
 *
 *   omakefile.cpp - implementation of the omakefile class;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oMAKEFILE_SOURCE
#define oMAKEFILE_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstdlib>
#include <cstring>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/omakefile.hpp"

#include "../classes/paths.h"
#include "../classes/sizes.h"

/*====================================================================*
 *
 *   char const * compiler() const;
 *
 *   return the mcompiler member string;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * omakefile::compiler () const 

{
	return (this->mcompiler);
}


/*====================================================================*
 *
 *   omakefile & compiler (char const * string);
 *
 *   assign a nes string to the mcompiler member only if the new string
 *   differs from the old string; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

omakefile & omakefile::compiler (char const * string) 

{
	otext::replace (this->mcompiler, string);
	return (* this);
}


omakefile & omakefile::linebreak () 

{
	otext::replace (this->mlinebreak, "\\\n\t");
	return (* this);
}


/*====================================================================*
 *
 *   char const * sourcedir () const;
 *
 *   return the msourcedir member string;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * omakefile::sourcedir () const 

{
	return (this->msourcedir);
}


/*====================================================================*
 *
 *   omakefile & sourcedir (char const * string);
 *
 *   replace the library property string if different from the old one; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

omakefile & omakefile::sourcedir (char const * string) 

{
	otext::replace (this->msourcedir, string);
	return (* this);
}


/*====================================================================*
 *
 *   char const * targetdir () const;
 *
 *   return the mtargetdir member string;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * omakefile::targetdir () const 

{
	return (this->mtargetdir);
}


/*====================================================================*
 *
 *   omakefile & targetdir (char const * string);
 *
 *   replace the library property string if different from the old one; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

omakefile & omakefile::targetdir (char const * string) 

{
	otext::replace (this->mtargetdir, string);
	return (* this);
}


/*====================================================================*
 *
 *   omakefile & projectfile (char const * pathname);
 *
 *   open a file containing a list of target filenames; include 
 *   each target in the project target list if not already present;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

omakefile & omakefile::projectfile (char const * pathname) 

{
	this->stream.open (pathname, std::ifstream::in);
	while (this->stream.getline (this->mbuffer, this->mlength).good ()) 
	{
		char * sp = this->mbuffer;;
		while ((* sp == ' ') && (* sp == '\t')) 
		{
			sp++;
		}
		if ((* sp == (char) (0)) || (* sp == '\n')) 
		{
			continue;
		}
		if ((* sp == '#') || (* sp == ';')) 
		{
			continue;
		}
		this->includefile (sp);
	}
	this->stream.close ();
	return (* this);
}


/*====================================================================*
 *
 *   omakefile & includefile(char const *pathname);
 *
 *   add the pathname argument to the project target list if not 
 *   already present;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

omakefile & omakefile::includefile (char const * pathname) 

{
	if (!list.defined (pathname)) 
	{
		list.insertitem (new oitem (pathname));
	}
	return (* this);
}


/*====================================================================*
 *
 *   omakefile & publish();
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

omakefile & omakefile::publish () 

{
	std::cout << "#!/usr/bin/make -f" << std::endl;
	this->title ("compile constants");
	std::cout << "cc=" << this->mcompiler << std::endl;
	switch (omakefile::getbits (oMAKEFILE_LIBRARY |oMAKEFILE_UTILITY)) 
	{
	case oMAKEFILE_UTILITY:
		std::cout << "src=" << this->msourcedir << std::endl;
		std::cout << "bin=" << this->msourcedir << std::endl;
		break;
	case oMAKEFILE_LIBRARY:
		std::cout << "src=" << this->msourcedir << std::endl;
		std::cout << "bin=" << this->msourcedir << std::endl;
		break;
	default:
		std::cout << "src=" << this->msourcedir << std::endl;
		std::cout << "bin=" << this->mtargetdir << std::endl;
		break;
	}
	std::cout << "ccflags=" << this->mccflags << std::endl;
	std::cout << "ldflags=" << this->mldflags << std::endl;
	this->title ("build instructions");
	std::cout << ".PHONY: compile library scripts manuals install uninstall clean fresh" << std::endl;
	std::cout << "compile:";
	for (size_t index = 0; index < list.count (); index++) 
	{
		std::cout << " " << this->mlinebreak << this->filespec.filespec (list.items (index)->name ()).likename (".o");
	}
	std::cout << std::endl;
	std::cout << "library:" << std::endl;
	std::cout << "scripts:" << std::endl;
	std::cout << "manuals:" << std::endl;
	std::cout << "install:" << std::endl;
	std::cout << "uninstall:" << std::endl;
	std::cout << "clean:" << std::endl;
	std::cout << "\trm -f a.out *.o *~ *.[0-9][0-9][0-9] t t.*" << std::endl;
	std::cout << "fresh: clean compile" << std::endl;
	std::cout << ".cpp.o:" << std::endl;
	std::cout << "\t${cc} ${ccflags} -c ${<}" << std::endl;
	std::cout << ".o:" << std::endl;
	std::cout << "\t${cc} ${ldflags} -o ${@} ${^}" << std::endl;
	this->title ("build instructions");
	for (size_t index = 0; index < list.count (); index++) 
	{
		this->section (list.items (index)->name ());
	}
	return (* this);
}


/*====================================================================*
 *
 *   omakefile & section (char const *filespec);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

omakefile & omakefile::section (char const * filespec) 

{
	this->stream.open (filespec);
	if (this->stream.good ()) 
	{
		this->filespec.filespec (filespec);
		std::cout << this->filespec.likename (".o") << ": " << this->filespec.filename ();
		while (this->stream.getline (this->mbuffer, this->mlength).good ()) 
		{
			if (this->scantext.copy (this->mbuffer).nexttoken ().havetoken ("#")) 
			{
				if (this->scantext.havetoken ("include")) 
				{
					if (this->scantext.havetoken ("\"")) 
					{
						std::cout << " " << this->mlinebreak << this->scantext.scanuntil ("\"").tokentext ();
					}
				}
			}
			this->scantext.clear ();
		}
		std::cout << "\n";
	}
	this->stream.close ();
	return (* this);
}


/*====================================================================*
 *
 *   omakefile ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

omakefile::omakefile () 

{
	this->mlinebreak = new char [1];
	this->mlinebreak [0] = (char)(0);
	this->mcompiler = otext::save ("g++");
	this->msourcedir = otext::save (getenv ("PWD"));
	this->mtargetdir = otext::save (PATH_CMASSOC);
	this->mccflags = otext::save ("-Wall -D_GNU_SOURCE");
	this->mldflags = otext::save ("");
	this->mlength = 0x0400;
	this->mbuffer = new char [this->mlength + 1];
	this->mbuffer [0] = (char) (0);
	this->moutput = new char [this->mlength + 1];
	this->moutput [0] = (char) (0);
	this->width (oSECTION_BARWIDTH);
	return;
}


/*====================================================================*
 *
 *   ~omakefile ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

omakefile::~omakefile () 

{
	delete [] this->mcompiler;
	delete [] this->mlinebreak;
	delete [] this->msourcedir;
	delete [] this->mtargetdir;
	delete [] this->mccflags;
	delete [] this->mldflags;
	delete [] this->mbuffer;
	delete [] this->moutput;
	return;
}


/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif

