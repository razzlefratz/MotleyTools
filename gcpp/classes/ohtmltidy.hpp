/*====================================================================*
 *
 *   ohtmltidy.hpp - interface for the ohtmltidy class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oMARKUP_HEADER
#define oMARKUP_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oHTMLEmptyElements.hpp"
#include "../classes/oflagword.hpp"
#include "../classes/osource.hpp"
#include "../classes/oindent.hpp"
#include "../classes/otext.hpp"

/*====================================================================*
 *   class constants;
 *--------------------------------------------------------------------*/

#define oMARKUP_LOWER (1 << 0)
#define oMARKUP_UPPER (1 << 1)
#define oMARKUP_REPAIR (1 << 2)
#define oMARKUP_INDENT (1 << 3)
#define oMARKUP_FORMAT (1 << 4)

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) ohtmltidy: private otext, private osource, public oindent, public oflagword 

{
public:
	ohtmltidy ();
	virtual ~ ohtmltidy ();
	char quote () const;
	ohtmltidy & quote (signed c);
	char const * string () const;
	char const * element () const;
	char const * attribute () const;
	char const * value () const;
	signed page (signed c);
	signed sgml (signed c);
	signed xhtml (signed c);
	signed xml (signed c) const;
	signed php (signed c) const;
	signed asp (signed c) const;
	signed cdata (signed c) const;
	signed comment (signed c) const;
	signed enquote (signed c, signed e);
	signed dequote (signed c, signed e);
	signed nmtoken (signed c);
	signed unknown (signed c);
	signed feed (signed c) const;
	signed find (signed c) const;
	ohtmltidy & print ();
protected:
	static oHTMLEmptyElements htmlempty;
	char * mstring;
	char * melement;
	char * mattribute;
	char * mvalue;
	char mquote;
private:
	
};

/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif

