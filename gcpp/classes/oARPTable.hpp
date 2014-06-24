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

#ifndef oARPTABLE_HEADER
#define oARPTABLE_HEADER

/*====================================================================*
 *  system header files;
 *--------------------------------------------------------------------*/

#include <stdint.h>

/*====================================================================*
 *  custom header files;
 *--------------------------------------------------------------------*/

#include "ethernet.h"

/*====================================================================*
 *  declare class data types;
 *--------------------------------------------------------------------*/

typedef struct arp_header

{
	uint16_t hardware_type;
	uint16_t protocol_type;
	uint8_t hwaddrlen;
	uint8_t ipaddrlen;
	uint16_t opcode;
	uint8_t source_hwaddr [6];
	uint8_t source_ipaddr [4];
	uint8_t target_hwaddr [6];
	uint8_t target_ipaddr [4];
}

arp_header;
typedef struct arp_packet

{
	struct ethernet_header ethernet_header;
	struct arp_header arp_header;
}

arp_packet;

/*====================================================================*
 *  declare class interface;
 *--------------------------------------------------------------------*/

class ARP

{
public: 
	ARP ();
	~ ARP ();
        void ipin (void);
	void in (void);
	void out ();
	void update (byte * internet_address, byte * ethernet_address);
	void timer ();
	static void PrintARPPacket (void * memory, unsigned extent);
	static void PrintARPHeader (void * memory, unsigned extent);
private:
      bool empty (void * memory, unsigned extent);
};

/*====================================================================*
 *  
 *--------------------------------------------------------------------*/

#endif



