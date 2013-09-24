/*====================================================================*
 *
 *   oIPAddress.h - interface for the oIP class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oipaDDRESS_HEADER
#define oipaDDRESS_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

#define OCTETS 4

/*====================================================================*
 *7
 *--------------------------------------------------------------------*/

class __declspec(dllexport) oIPAddress

{
public: 
	oIPAddress ();
	virtual ~ oIPAddress();
	char const * string(unsigned address);
	char const * padded(unsigned address);
	unsigned number(char const * address);
	unsigned inaddr(char const * address);
private: 
	union bits
	{
		unsigned value;
		unsigned char field[OCTETS];
	};
	static bits bitmap;
	static char digits[];
	static char buffer[];
	static unsigned octet;
	static unsigned digit;
	static unsigned value;
	static unsigned width;
};

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif



