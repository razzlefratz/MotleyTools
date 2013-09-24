/*====================================================================*
 *
 *   tlv.h - nvm file format definitions and declarations;
 *
 *--------------------------------------------------------------------*/

#ifndef TLV_HEADER
#define TLV_HEADER

/*====================================================================*
 *   macros;
 *--------------------------------------------------------------------*/

#define TLVSPAN(node) (sizeof (node) - sizeof ((node)->data) + (node)->size) 
#define TLVDUMP(node) hexdump (&(node)->data, 0, (node)->size, stdout)

/*====================================================================*
 *   variables;
 *--------------------------------------------------------------------*/

#ifndef __GNUC__
#pragma pack (push,1)
#endif

typedef struct __packed TLVNode

{
	uint32_t type;
	uint32_t size;
	uint32_t data;
}

TLVNode;

#ifndef __GNUC__
#pragma pack (pop)
#endif

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#endif



