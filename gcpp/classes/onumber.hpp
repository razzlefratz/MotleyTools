/*====================================================================*
 *
 *   onumber.hpp - onumber class declaration;
 *
 *   convert common specification strings to numeric values; these
 *   methods are designed for command line argument parsing an may
 *   not return on conversion failure; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oNUMBER_HEADER
#define oNUMBER_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/types.h"

/*====================================================================*
 *   numeric converson sizes and limits;
 *--------------------------------------------------------------------*/

#define BIN_RADIX 2
#define OCT_RADIX 8
#define DEC_RADIX 10
#define HEX_RADIX 16
#define MIN_RADIX 2
#define MAX_RADIX 36

#define BIN_OCTET 8
#define DEC_OCTET 3
#define OCT_OCTET 3
#define HEX_OCTET 2

#define IPv4_SIZE 4
#define IPv6_SIZE 16

/*====================================================================*
 *   numeric string extenders;
 *--------------------------------------------------------------------*/

#define BIN_EXTENDER '-'
#define DEC_EXTENDER '.'
#define HEX_EXTENDER ':'
#define CHR_EXTENDER '.'

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#define isodd(n)  (((n)&(1)) != 0)
#define iseven(n) (((n)&(1)) == 0)

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) onumber 

{
public:
	onumber ();
	virtual~ onumber ();
	static huge_t basespec (char const * string, unsigned base, unsigned size);
	static huge_t uintspec (char const * string, huge_t minimum, huge_t maximum);
	static size_t ipv4spec (char const * string, void * memory);
	static size_t ipv6spec (char const * string, void * memory);
	static void * ipv4encode (char const * string, void * memory);
	static void * ipv6encode (char const * string, void * memory);
private:
	static signed todigit (signed c);
};


/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif

