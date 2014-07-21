/*====================================================================*
 *   
 *   Copyright (c) 1982-2006 Charles Maier Associates, Ltd.
 *   
 *   Permission to use, copy, modify, and/or distribute this software 
 *   for any purpose with or without fee is hereby granted, provided 
 *   that the above copyright notice and this permission notice appear 
 *   in all copies.
 *   
 *   THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL 
 *   WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED 
 *   WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL  
 *   THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR 
 *   CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM 
 *   LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, 
 *   NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN 
 *   CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *   
 *--------------------------------------------------------------------*/

#ifndef oINTERNETADDRESS_HEADER
#define oINTERNETADDRESS_HEADER

/*====================================================================*
 *  system header files;
 *--------------------------------------------------------------------*/

/*====================================================================*
 *  custom header files;
 *--------------------------------------------------------------------*/

#include "omemory.hpp"

/*====================================================================*
 *  declare class interface;
 *--------------------------------------------------------------------*/

class oInternetAddress

{
public: 
	oInternetAddress ();
	~ oInternetAddress ();
	static const unsigned length;
	oInternetAddress & set (byte);
	oInternetAddress & set (byte, byte, byte, byte);
	oInternetAddress & set (const byte *);
	const byte * binary () const;
	const char * string ();
private: 
	byte * maddress;
};

/*====================================================================*
 *  
 *--------------------------------------------------------------------*/

#endif



