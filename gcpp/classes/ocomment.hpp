/*====================================================================*
 *
 *   ocomment.hpp - declaration of ocomment class.
 *
 *.  Motley Tools by Charles Maier <cmaier@cmassoc.net>;
 *:  Copyright 2001-2006 by Charles Maier Associates;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCOMMENT_HEADER
#define oCOMMENT_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/oflagword.hpp"
#include "../classes/otext.hpp"

/*====================================================================*
 *   constants;
 *--------------------------------------------------------------------*/

#define oCOMMENT_LENGTH 4096
#define oCOMMENT_WIDTH 68 
#define oCOMMENT_SPACE 3

#define oCOMMENT_B_DEFAULT (0)
#define oCOMMENT_B_DOUBLE  (1 << 0)
#define oCOMMENT_B_TRIPLE  (1 << 1)
#define oCOMMENT_B_SHORT   (1 << 2)
#define oCOMMENT_B_COMMENT (1 << 3)
#define oCOMMENT_B_FOREVER (1 << 4)
#define oCOMMENT_B_DISCARD (1 << 5)
#define oCOMMENT_B_PACKAGE (1 << 6)
#define oCOMMENT_B_RELEASE (1 << 7)
#define oCOMMENT_B_PUBLISH (1 << 8)
#define oCOMMENT_B_LICENSE (1 << 9)

#define oCOMMENT_C_SLASH '/'
#define oCOMMENT_C_BURST '*'
#define oCOMMENT_C_UPPER '='
#define oCOMMENT_C_LOWER '-'
#define oCOMMENT_C_PACKAGE '.'
#define oCOMMENT_C_RELEASE ':'
#define oCOMMENT_C_PUBLISH ';'
#define oCOMMENT_C_LICENSE '~'

#define oCOMMENT_S_PACKAGE "package"
#define oCOMMENT_S_RELEASE "release"
#define oCOMMENT_S_PUBLISH "publish"
#define oCOMMENT_S_LICENSE "license"

#define oCOMMENT_T_PACKAGE "Motley Tools by Charles Maier <cmaier@cmassoc.net>"
#define oCOMMENT_T_RELEASE "Copyright (c) 2001-2006 by Charles Maier"
#define oCOMMENT_T_PUBLISH "Published under the Internet Software Consortium (ISC) License"
#define oCOMMENT_T_LICENSE "Permission to use, copy, modify, and/or distribute this software\n *   for any purpose with or without fee is hereby granted, provided\n *   that the above copyright notice and this permission notice appear\n *   in all copies.\n *\n *   THE SOFTWARE IS PROVIDED \"AS IS\" AND THE AUTHOR DISCLAIMS ALL\n *   WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED\n *   WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL\n *   THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR\n *   CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM\n *   LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,\n *   NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN\n *   CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE."

/*====================================================================*
 *   interface declaration
 *--------------------------------------------------------------------*/

class __declspec (dllexport) ocomment: private otext, public oflagword

{
public: 
	ocomment (void);
	virtual ~ ocomment (void);
	signed comment (signed c);
	signed cplus (signed c);
	signed clang (signed c);
	ocomment & preamble (void);
	unsigned width (void) const;
	unsigned align (void) const;
	ocomment & width (unsigned width);
	ocomment & align (unsigned space);
	char const * package (void) const;
	char const * release (void) const;
	char const * publish (void) const;
	char const * license (void) const;
	ocomment & package (char const * package);
	ocomment & release (char const * release);
	ocomment & publish (char const * publish);
	ocomment & license (char const * license);
private: 
	signed breaker (signed c) const;
	signed content (signed c) const;
	signed message (signed c, char const * string) const;
	char * mpackage;
	char * mrelease;
	char * mpublish;
	char * mlicense;
	unsigned mwidth;
	unsigned malign;
};

/*====================================================================*
 *   end interface declaration;
 *--------------------------------------------------------------------*/

#endif

