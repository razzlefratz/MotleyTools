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
#define oCOMMENT_EXTENDBAR 1
#define oCOMMENT_CUSTOMIZE 1

/*====================================================================*
 *   constants; 
 *--------------------------------------------------------------------*/

#define oCOMMENT_LENGTH 4096
#define oCOMMENT_WIDTH 68 

#define oCOMMENT_B_DEFAULT (0)
#define oCOMMENT_B_DOUBLE  (1 << 0)
#define oCOMMENT_B_TRIPLE  (1 << 1)
#define oCOMMENT_B_SHORT   (1 << 2)
#define oCOMMENT_B_DISCARD (1 << 3)
#define oCOMMENT_B_PERMANENT (1 << 4)
#define oCOMMENT_B_PREFACE (1 << 5)
#define oCOMMENT_B_PACKAGE (1 << 6)
#define oCOMMENT_B_RELEASE (1 << 7)
#define oCOMMENT_B_LICENSE (1 << 8)
#define oCOMMENT_B_SPECIAL (1 << 9)

#define oCOMMENT_C_PREFACE ('~')
#define oCOMMENT_C_PACKAGE ('.')
#define oCOMMENT_C_RELEASE (':')
#define oCOMMENT_C_LICENSE (';')
#define oCOMMENT_C_SPECIAL ('!')

#define oCOMMENT_C_UPPER ('=')
#define oCOMMENT_C_LOWER ('-')

#define oCOMMENT_S_PREFACE "preface"
#define oCOMMENT_S_PACKAGE "package"
#define oCOMMENT_S_RELEASE "release"
#define oCOMMENT_S_LICENSE "license"
#define oCOMMENT_S_SPECIAL "special"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

class __declspec (dllexport) ocomment: public oflagword, private otext 

{
public:
	ocomment (size_t length);
	ocomment ();
	virtual ~ ocomment ();
	signed comment (signed c);
	signed cplus (signed c);
	signed clang (signed c);

#if oCOMMENT_EXTENDBAR

	unsigned char cupper () const;
	unsigned char clower () const;
	size_t width () const;
	ocomment & cupper (unsigned char c);
	ocomment & clower (unsigned char c);
	ocomment & width (size_t width);

#endif

#if oCOMMENT_CUSTOMIZE

	char const * preface () const;
	char const * package () const;
	char const * release () const;
	char const * license () const;
	char const * special () const;
	ocomment & preface (char const * preface);
	ocomment & package (char const * package);
	ocomment & release (char const * release);
	ocomment & license (char const * license);
	ocomment & special (char const * special);

#endif

private:

#if oCOMMENT_CUSTOMIZE

	signed message (signed c, char const *string);
	char * mpreface;
	char * mpackage;
	char * mrelease;
	char * mlicense;
	char * mspecial;

#endif

#if oCOMMENT_EXTENDBAR

	unsigned char mupper;
	unsigned char mlower;
	size_t mwidth;

#endif

	char *mbuffer;
	char *mstring;
	char *moutput;
	size_t mlength;
	size_t mcount;
};


/*====================================================================*
 *   end signederface definition;
 *--------------------------------------------------------------------*/

#endif

