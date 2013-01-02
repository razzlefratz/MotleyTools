/*====================================================================*
 *
 *   ogetoptv.hpp - interface for the ogetoptv class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oGETOPTV_HEADER
#define oGETOPTV_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oputoptv.hpp"
#include "../classes/oversion.hpp"

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define oGETOPTV_VERSION 1
#define oGETOPTV_SUMMARY 1

#define oGETOPTV_C_OPTIONS ('-')
#define oGETOPTV_C_OPERAND (':')
#define oGETOPTV_C_ILLEGAL ('?')
#define oGETOPTV_C_VERSION ('!')
#define oGETOPTV_C_SUMMARY ('?')

/*====================================================================*
 *   object declaration; 
 *--------------------------------------------------------------------*/

class __declspec (dllexport) ogetoptv: private oputoptv, private oversion 

{
public:
	ogetoptv ();
	virtual ~ ogetoptv ();
	int argc () const;
	char const ** argv () const;
	char const * args ();
	signed optind () const;
	signed opterr () const;
	signed optmin () const;
	signed optopt () const;
	char const *optarg () const;
	signed operator++ (signed);
	int getoptv (int argc, char const * argv [], char const * optv []);
	ogetoptv & optind (const signed);
	ogetoptv & opterr (const signed);
	ogetoptv & optmin (const signed);
private:
	char const * moption;
	char const * mstring;
	int margc;
	char const ** margv;
	char * margs;
	char const * moptarg;
	int mopterr;
	int moptind;
	int moptmin;
	int moptopt;
	int mcount;
	int mindex;
};


#endif

