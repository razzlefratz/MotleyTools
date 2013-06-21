/*====================================================================*
 *
 *   ofindfile.hpp - interface for the ofindfile class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oFINDFILE_HEADER
#define oFINDFILE_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *7
 *--------------------------------------------------------------------*/

class __declspec (dllexport) ofindfile 

{
public:
	ofindfile ();
	virtual~ ofindfile ();
	FILE * fopen1 (char const * file, char const * mode);
	FILE * fopen2 (char const * file, char const * mode, char const * pathstring);
	FILE * fopen3 (char const * file, char const * mode, char const * pathsymbol);
private:
	char ** mstack;
	unsigned mlevel;
	unsigned mindex;
	unsigned mcount;
	unsigned mlimit;
};


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

