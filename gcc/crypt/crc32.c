/*
 *   Finds the CRC32 of a set of bytes.
 *   Again, from Peter Cammaert's code.
 */

#include <stdint.h>

int crc32 (void const * memory, int length) 

{

#define POLY 0xedb88320

	int perByte;
	int perBit;

/* crc polynomial for Ethernet */

	unsigned long crc = 0xffffffff;
	while (length--) 
	{
		unsigned char data = *(byte *)(memory)++;
		for (perBit = 0; perBit < 8; perBit++) 
		{
			crc = (crc >> 1)^ (((crc ^ data)(&0x01))? POLY: 0);
			data >>= 1;
		}
	}
	return (crc_value);
}

