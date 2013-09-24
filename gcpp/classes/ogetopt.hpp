/*====================================================================*
 *
 *   ogetopt.hpp - interface for the ogetopt class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oGETOPT_HEADER
#define oGETOPT_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define oGETOPT_C_OPTIONS ('-')
#define oGETOPT_C_OPERAND (':')
#define oGETOPT_C_ILLEGAL ('?')
#define oGETOPT_C_SUMMARY ('?')
#define oGETOPT_C_VERSION ('!')

/*====================================================================*
 *   object declaration; 
 *--------------------------------------------------------------------*/

class __declspec (dllexport) ogetopt

{
public: 
	ogetopt ();
	ogetopt (const signed opterr);
	virtual ~ ogetopt ();
	signed argc () const;
	char const ** argv () const;
	char * args ();
	signed opterr () const;
	signed optind () const;
	signed optopt () const;
	char const * optarg () const;
	signed operator++ (signed);
	int getopt (int argc, char const * argv [], char const * options);
	ogetopt & putopt (char const * argv []);
	ogetopt & optind (const signed optind);
	ogetopt & opterr (const signed opterr);
private: 
	int margc;
	char const ** margv;
	char * margs;
	char const * moptapp;
	char const * moptarg;
	int moptopt;
	int moptind;
	int mopterr;
	char const * mstring;
	int mcount;
	int mindex;
};

#endif



