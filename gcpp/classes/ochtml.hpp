/*====================================================================*
 *
 *   ochtml.hpp - declaration of ochtml class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCHTML_HEADER
#define oCHTML_HEADER

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#include "../classes/oglossary.hpp"
#include "../classes/ofilespec.hpp"
#include "../classes/oISOGlyph.hpp"
#include "../classes/oSpanElement.hpp"
#include "../classes/oAnchorElement.hpp" 
#include "../classes/owebpage.hpp"
#include "../classes/ocprocwords.hpp"
#include "../classes/ofunctions.hpp"
#include "../classes/oscancode.hpp"

/*====================================================================*
 *   class constants;
 *--------------------------------------------------------------------*/

#define oCHTML_PAGE_STYLESHEET "/styles/clang.css"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) ochtml: public owebpage 

{
public:
	ochtml (char const * stylesheet);
	ochtml ();
	virtual~ ochtml ();
	ochtml & html (char const * pathname);
	ochtml & stylesheet ();
	ochtml & stylesheet (char const * string);
private:
	static char const * resource (char const * filename);
	ochtml & directive ();
	static ofilespec filespec;
	oscancode mfile;
	ofunctions clibword;
	ocprocwords cprocword;
	char * murl;
	oglossary minternal;
	oglossary mexternal;
	oSpanElement mspan;
	oAnchorElement mlink;
	oISOGlyph mglyph;
};


/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif

