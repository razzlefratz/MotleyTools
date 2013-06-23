/*====================================================================*
 *
 *   endian.h - integer byte order declarations and definitions;
 *
 *   this header is included to support recent moves to expand and
 *   standardize endian conversion functions on Linux, FreeBSD and 
 *   NetBSD; Linux has implemented the following functions but OSX
 *   and Microsoft have not yet done so;
 *
 *   These functions are similar to network byteorder functions.
 *   For example, be32toh() is identical to ntohl().
 *   
 *   #define _BSD_SOURCE
 *   #include <endian.h>
 *   
 *   uint16_t htobe16(uint16_t x);
 *   uint16_t htole16(uint16_t x);
 *   uint16_t be16toh(uint16_t x);
 *   uint16_t le16toh(uint16_t x);
 *   
 *   uint32_t htobe32(uint32_t x);
 *   uint32_t htole32(uint32_t x);
 *   uint32_t be32toh(uint32_t x);
 *   uint32_t le32toh(uint32_t x);
 *   
 *   uint64_t htobe64(uint64_t x);
 *   uint64_t htole64(uint64_t x);
 *   uint64_t be64toh(uint64_t x);
 *   uint64_t le64toh(uint64_t x);
 *   
 *   The advantage of network byteorder functions is that they are 
 *   available on all Unix systems but they were meant for network
 *   applications and lack little-endian and 64-bit variants;
 *
 *.  Motley Tools by Charles Maier; cmaier@cmassoc.net;
 *:  Published 2005 by Charles Maier Associates for internal use;
 *;  Released under GNU General Public License v2 and later;
 *
 *--------------------------------------------------------------------*/

#ifndef ENDIAN_HEADER
#define ENDIAN_HEADER

/*====================================================================*
 *   endian conversion functions (deprecated);
 *--------------------------------------------------------------------*/

#if 0
#if __BYTE_ORDER == __LITTLE_ENDIAN
# 	define INTOHH(x) (x)
# 	define INTOHL(x) (x)
# 	define INTOHS(x) (x)
# 	define IHTONH(x) (x)
# 	define IHTONL(x) (x)
# 	define IHTONS(x) (x)
#elif __BYTE_ORDER == __BIG_ENDIAN
#  	define INTOHH(x) __bswap_64 (x)
#  	define INTOHL(x) __bswap_32 (x)
#  	define INTOHS(x) __bswap_16 (x)
#  	define IHTONH(x) __bswap_64 (x)
#  	define IHTONL(x) __bswap_32 (x)
#  	define IHTONS(x) __bswap_16 (x)
#else
#error "Undefined host byte order."
#endif
#endif

/*====================================================================*
 *   endian conversion functions;
 *--------------------------------------------------------------------*/

#if __BYTE_ORDER == __LITTLE_ENDIAN
#	define BE16TOH(x) __bswap_16(x)
#	define BE32TOH(x) __bswap_32(x)
#	define BE64TOH(x) __bswap_64(x)
#	define HTOBE16(x) __bswap_16(x)
#	define HTOBE32(x) __bswap_32(x)
#	define HTOBE64(x) __bswap_64(x)
#	define LE16TOH(x) (x)
#	define LE32TOH(x) (x)
#	define LE64TOH(x) (x)
#	define HTOLE16(x) (x)
#	define HTOLE32(x) (x)
#	define HTOLE64(x) (x)
#elif __BYTE_ORDER == __BIG_ENDIAN
#	define BE16TOH(x) (x)
#	define BE32TOH(x) (x)
#	define BE64TOH(x) (x)
#	define HTOBE16(x) (x)
#	define HTOBE32(x) (x)
#	define HTOBE64(x) (x)
#	define LE16TOH(x) __bswap_16(x)
#	define LE32TOH(x) __bswap_32(x)
#	define LE64TOH(x) __bswap_64(x)
#	define HTOLE16(x) __bswap_16(x)
#	define HTOLE32(x) __bswap_32(x)
#	define HTOLE64(x) __bswap_64(x)
#else
#error "Undefined host byte order."
#endif

/*====================================================================*
 *  endian conversion functions;
 *--------------------------------------------------------------------*/

#endif

