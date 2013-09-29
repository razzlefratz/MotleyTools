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
 *   compiler controls;
 *--------------------------------------------------------------------*/

#define oCOMMENT_PADMARGIN 1

/*====================================================================*
 *   constants;
 *--------------------------------------------------------------------*/

#define oCOMMENT_LENGTH 4096
#define oCOMMENT_WIDTH 68 

#define oCOMMENT_B_DEFAULT (0)
#define oCOMMENT_B_DOUBLE  (1 << 0)
#define oCOMMENT_B_TRIPLE  (1 << 1)
#define oCOMMENT_B_SHORT   (1 << 2)
#define oCOMMENT_B_COMMENT (1 << 3)
#define oCOMMENT_B_DISCARD (1 << 4)
#define oCOMMENT_B_PERMANENT (1 << 5)
#define oCOMMENT_B_PREFACE (1 << 6)
#define oCOMMENT_B_PACKAGE (1 << 7)
#define oCOMMENT_B_RELEASE (1 << 8)
#define oCOMMENT_B_LICENSE (1 << 9)
#define oCOMMENT_B_SPECIAL (1 << 10)

#define oCOMMENT_C_UPPER ('=')
#define oCOMMENT_C_LOWER ('-')

#define oCOMMENT_C_PREFACE '~'
#define oCOMMENT_C_PACKAGE '.'
#define oCOMMENT_C_RELEASE ':'
#define oCOMMENT_C_LICENSE ';'
#define oCOMMENT_C_SPECIAL '!'

#define oCOMMENT_S_PREFACE "preface"
#define oCOMMENT_S_PROJECT "project"
#define oCOMMENT_S_PACKAGE "package"
#define oCOMMENT_S_RELEASE "release"
#define oCOMMENT_S_LICENSE "license"
#define oCOMMENT_S_SPECIAL "special"

#define oCOMMENT_T_PREFACE "Permission to use, copy, modify, and/or distribute this software\n *   for any purpose with or without fee is hereby granted, provided\n *   that the above copyright notice and this permission notice appear\n *   in all copies.\n *\n *   THE SOFTWARE IS PROVIDED \"AS IS\" AND THE AUTHOR DISCLAIMS ALL\n *   WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED\n *   WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL\n *   THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR\n *   CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM\n *   LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,\n *   NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN\n *   CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE."
#define oCOMMENT_T_PACKAGE "Motley Tools by Charles Maier <cmaier@cmassoc.net>."
#define oCOMMENT_T_RELEASE "Copyright (c) 2001-2006 by Charles Maier."
#define oCOMMENT_T_LICENSE "Published under the Internet Software Consortium (ISC) License."
#define oCOMMENT_T_SPECIAL ""

/*====================================================================*
 *   interface declaration
 *--------------------------------------------------------------------*/

class __declspec (dllexport) ocomment: private otext, public oflagword

{
public: 
	ocomment (size_t length);
	ocomment (void);
	virtual ~ ocomment (void);
	signed comment (signed c);
	signed cplus (signed c);
	signed clang (signed c);
	signed preamble (signed c);
	ocomment & preamble (void);
	unsigned char cupper (void) const;
	unsigned char clower (void) const;
	size_t width (void) const;
	ocomment & cupper (unsigned char c);
	ocomment & clower (unsigned char c);
	ocomment & width (size_t width);


	char const * preface (void) const;
	char const * package (void) const;
	char const * release (void) const;
	char const * license (void) const;
	char const * special (void) const;
	ocomment & preface (char const * preface);
	ocomment & package (char const * package);
	ocomment & release (char const * release);
	ocomment & license (char const * license);
	ocomment & special (char const * special);


private: 


	signed message (signed c, char const * string);
	signed breaker (signed c, signed e);
	signed content (signed c);
	ocomment & content (void);
	char * mpreface;
	char * mpackage;
	char * mrelease;
	char * mlicense;
	char * mspecial;

	unsigned char mupper;
	unsigned char mlower;
	size_t mwidth;
	char * mbuffer;
	char * minsert;
	char * moutput;
	size_t mlength;
	size_t mcount;
};

/*====================================================================*
 *   end interface declaration;
 *--------------------------------------------------------------------*/

#endif



