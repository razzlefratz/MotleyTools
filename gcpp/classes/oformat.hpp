/*====================================================================*
 *
 *   oformat.hpp - interface for the oformat class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oFORMAT_HEADER
#define oFORMAT_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

class __declspec(dllexport) oformat

{
public: 
	oformat ();
	virtual ~ oformat();
	unsigned offset() const;
	unsigned indent() const;
	unsigned margin() const;
	unsigned length() const;
	unsigned column() const;
	oformat & status();
	oformat & offset(unsigned column);
	oformat & indent(unsigned column);
	oformat & margin(unsigned column);
	oformat & length(unsigned column);
	oformat & print(char const * string);
	oformat & space(unsigned count);
	oformat & flush(unsigned count);
	oformat & table(unsigned count);
	oformat & shift(unsigned count);
	oformat & align();
private: 
	char * mbuffer;
	unsigned mlength;
	unsigned mcolumn;
	unsigned moffset;
	unsigned mindent;
	unsigned mmargin;
	unsigned mrecord;
};

/*====================================================================*
 *   end class declaration;
 *--------------------------------------------------------------------*/

#endif



