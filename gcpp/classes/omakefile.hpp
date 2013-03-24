/*====================================================================*
 *
 *   omakefile.hpp - interface for the omakefile class;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oMAKEFILE_HEADER
#define oMAKEFILE_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <fstream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/olist.hpp"
#include "../classes/oitem.hpp"
#include "../classes/osection.hpp"
#include "../classes/oscantext.hpp"
#include "../classes/ofilespec.hpp"
#include "../classes/oflagword.hpp"
#include "../classes/otext.hpp"

/*====================================================================*
 *   class constants; 
 *--------------------------------------------------------------------*/

#define oMAKEFILE_LIBRARY (1 << 0)
#define oMAKEFILE_UTILITY (1 << 1)

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) omakefile: private otext, private osection, public oflagword

{
public:
	omakefile ();
	virtual ~ omakefile ();
	char const * compiler () const;
	char const * project () const;
	char const * sourcedir () const;
	char const * targetdir () const;
	omakefile & compiler (char const *string);
	omakefile & linebreak ();
	omakefile & project (char const *string);
	omakefile & sourcedir (char const *string);
	omakefile & targetdir (char const *string);
	omakefile & publish ();
	omakefile & section (char const *filename);
	omakefile & projectfile (char const *filename);
	omakefile & includefile (char const *filename);
private:
	oscantext scantext;
	ofilespec filespec;
	std::ifstream stream;
	olist list;
	char *mcompiler;
	char *msourcedir;
	char *mtargetdir;
	char *mccflags;
	char *mldflags;
	char *mlinebreak;
	size_t mlength;
	size_t mline;
	char *mbuffer;
	char *moutput;
};


/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif

