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

#ifndef oINTERNET_HEADER
#define oINTERNET_HEADER

/*====================================================================*
 *  system header files;
 *--------------------------------------------------------------------*/

/*====================================================================*
 *  custom header files;
 *--------------------------------------------------------------------*/

#include "oInternetAddress.hpp"

/*====================================================================*
 *  declare class data types;
 *--------------------------------------------------------------------*/

typedef struct internet_header

{
	byte version;
        byte tos;
	uint16_t total_length;
	uint16_t identification;
	uint16_t frag_offset;
	byte TTL;
	byte protocol;
	uint16_t checksum;
	byte target_address [4];
	byte source_address [4];
}

internet_header;
typedef struct internet_packet

{
	struct internet_header internet_header;
	byte body [1476];
}

internet_packet;

/*====================================================================*
 *  declare class interface;
 *--------------------------------------------------------------------*/

class oInternet

{
public: 
	oInternet ();
	~ oInternet ();
	bool onsubnet (const byte * address1, const byte * address2, const byte * netmask);
	static const unsigned header_length;
	static void PrintPacket (void * memory, unsigned extent) ;
	static void PrintHeader (void * memory, unsigned extent);
	static char const * ProtocolName (byte protocol);
	oInternetAddress broadcast;
        oInternetAddress address;
	oInternetAddress netmask;
	oInternetAddress gateway;
private: 
};

/*====================================================================*
 *  
 *--------------------------------------------------------------------*/

#endif



