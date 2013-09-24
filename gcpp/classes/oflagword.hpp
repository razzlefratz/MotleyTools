/*====================================================================*
 *
 *   oflagword.hpp - interface for the oflagword class;
 *
 *   bitmapped flagword manager; this class can be inherited by other
 *   classes that need a flagword; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oFLAGWORD_HEADER
#define oFLAGWORD_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec(dllexport) oflagword

{
public: 
	oflagword ();
	oflagword (unsigned);
	virtual ~ oflagword();
	unsigned state() const;
	unsigned getword() const;
	unsigned getbits(unsigned mask) const;
	oflagword & state(unsigned word);
	oflagword & setword(unsigned mask);
	oflagword & setbits(unsigned mask);
	oflagword & clearbits(unsigned mask);
	bool anyset(unsigned mask) const;
	bool allset(unsigned mask) const;
	bool anyclear(unsigned mask) const;
	bool allclear(unsigned mask) const;
private: 
	unsigned mbits;
};

/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif



