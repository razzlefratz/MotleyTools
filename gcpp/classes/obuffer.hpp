/*====================================================================*
 *
 *   obuffer.hpp - declaration of obuffer class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oBUFFER_HEADER
#define oBUFFER_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdint.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) obuffer

{
public: 
	obuffer (size_t length);
	obuffer ();
	virtual ~ obuffer ();
	char const * offset () const;
	char const * record () const;
	obuffer & offset (char const * offset);
	obuffer & record (char const * record);
	obuffer & append (signed c);
	obuffer & append (char const * string);
	obuffer & space (signed space);
	obuffer & level (signed level);
	obuffer & flush ();
	obuffer & clear ();
private: 
	char * moffset;
	char * mfinish;
	char * mbuffer;
	size_t mlength;
	size_t mtotal;
	size_t mblock;
};

/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif



