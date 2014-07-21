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

#ifndef oETHERNET_HEADER
#define oETHERNET_HEADER

/*====================================================================*
 *  system header files;
 *--------------------------------------------------------------------*/

#include <stdint.h>

/*====================================================================*
 *  custom header files;
 *--------------------------------------------------------------------*/

#include "oEthernetAddress.hpp"

/*====================================================================*
 *  define class macros;
 *--------------------------------------------------------------------*/

#define htons(x) (((x) << 8 & 0xFF00) | ((x) >> 8 & 0x00FF))
#define ntohs(x) htons(x)
#define htonl(x) (((x) << 24 & 0xFF000000UL) | \
                  ((x) <<  8 & 0x00FF0000UL) | \
                  ((x) >>  8 & 0x0000FF00UL) | \
                  ((x) >> 24 & 0x000000FFUL))
#define ntohl(x) htonl(x)

#define ETHERTYPE_ARP 0x0806
#define ETHERTYPE_IP  0x0800
#define ETHERTYPE_IP6 0x86dd

/*====================================================================*
 *  declare class data types;
 *--------------------------------------------------------------------*/

typedef struct ethernet_header

{
	byte target_address [6];
	byte source_address [6];
	uint16_t protocol;
}

ethernet_header;
typedef struct ethernet_frame

{
	struct ethernet_header header;
	byte body [1500];
}

ethernet_frame;

/*====================================================================*
 *  declare class interface;
 *--------------------------------------------------------------------*/

class oEthernet

{
public: 
	oEthernet ();
	~ oEthernet ();
	static void PrintFrame (void * memory, unsigned extent);
	static void PrintHeader (void * memory, unsigned extent);
	static char const * ProtocolName (uint16_t protocol);
	static const unsigned header_length;
	oEthernetAddress broadcast;
	oEthernetAddress address;
private: 
};

/*====================================================================*
 *  
 *--------------------------------------------------------------------*/

#endif



