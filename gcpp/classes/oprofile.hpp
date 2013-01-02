/*====================================================================*
 *
 *   oprofile.hpp - interface for the oprofile class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oPROFILE_HEADER
#define oPROFILE_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <iostream>
#include <fstream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/oswitch.hpp"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oprofile: private oswitch 

{
public:
	oprofile ();
	virtual ~ oprofile ();
	oprofile & write (char const * section);
	oprofile & write (char const * element, char const * content);
	char const *string (char const * profile, char const * section, char const * element, char const * content);
	signed number (char const * profile, char const * section, char const * element, signed value);
	bool enable (char const * profile, char const * section, char const * element, bool state);
private:
	bool compare (char const *string);
	oprofile & newchar ();
	oprofile & newword ();
	oprofile & newline ();
	oprofile & newtext ();
	std::ifstream mstream;
	char * mstring;
	char * mbuffer;
	size_t mrecord;
	size_t mlength;
	size_t moutput;
	size_t mappend;
	signed mbreak;
};


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

