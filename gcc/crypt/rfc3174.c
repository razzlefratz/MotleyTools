/*====================================================================*
 *
 *  crypt.c
 *
 *  Description:
 *      This file implements the Secure Hashing Algorithm 1 as
 *      defined in FIPS PUB 180-1 published April 17, 1995.
 *
 *      The SHA-1, produces a 160-bit message digest for a given
 *      data stream.  It should take about 2**n steps to find a
 *      message with the same digest as a given message and
 *      2**(n/2) to find any two messages with the same digest,
 *      when n is the digest size in bits.  Therefore, this
 *      algorithm can serve as a means of providing a
 *      "fingerprint" for a message.
 *
 *  Portability Issues:
 *      SHA-1 is defined in terms of 32-bit "words".  This code
 *      uses <stdint.h> (included via "crypt.h" to define 32 and 8
 *      bit unsigned integer types.  If your C compiler does not
 *      support 32 bit unsigned integers, this code is not
 *      appropriate.
 *
 *  Caveats:
 *      SHA-1 is designed to work with messages less than 2^64 bits
 *      long.  Although SHA-1 allows a message digest to be generated
 *      for messages of any number of bits less than 2^64, this
 *      implementation only works with messages with a length that is
 *      a multiple of the size of an 8-bit character.
 *
 *--------------------------------------------------------------------*/

#ifndef SHA1_SOURCE
#define SHA1_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "rfc3174.h"

/*====================================================================*
 *  Define the SHA1 circular left shift macro
 *--------------------------------------------------------------------*/

#define SHA1CircularShift(bits,word) (((word)<<(bits))|((word)>>(32-(bits))))

/*====================================================================*
 *
 *   void SHA1ProcessMessageBlock (SHA1Context *context);
 *
 *  Description:
 *      This function will process the next 512 bits of the message
 *      stored in the Message_Block array.
 *
 *  Parameters:
 *      None.
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *   
 *      Many of the variable names in this code, especially the
 *      single character names, were used because those were the
 *      names used in the publication.
 *
 *
 *--------------------------------------------------------------------*/

static void SHA1ProcessMessageBlock (SHA1Context *context) 

{
	const uint32_t K [] = 
	{
		0x5A827999,
		0x6ED9EBA1,
		0x8F1BBCDC,
		0xCA62C1D6
	};
	uint32_t temp;
	uint32_t W [80];
	uint32_t A;
	uint32_t B;
	uint32_t C;
	uint32_t D;
	uint32_t E;
	int t;
	for (t = 0; t < 16; t++) 
	{
		W [t] = 0;
		W [t] |= context->Message_Block [t * 4 + 0] << 24;
		W [t] |= context->Message_Block [t * 4 + 1] << 16;
		W [t] |= context->Message_Block [t * 4 + 2] << 8;
		W [t] |= context->Message_Block [t * 4 + 3];
	}
	for (t = 16; t < 80; t++) 
	{
		W [t] = SHA1CircularShift (1, W [t-3] ^ W [t-8] ^ W [t-14] ^ W [t-16]);
	}
	A = context->Intermediate_Hash [0];
	B = context->Intermediate_Hash [1];
	C = context->Intermediate_Hash [2];
	D = context->Intermediate_Hash [3];
	E = context->Intermediate_Hash [4];
	for (t = 0; t < 20; t++) 
	{
		temp = SHA1CircularShift (5, A) + ((B & C) | ((~B) & D)) + E + W [t] + K [0];
		E = D;
		D = C;
		C = SHA1CircularShift (30, B);
		B = A;
		A = temp;
	}
	for (t = 20; t < 40; t++) 
	{
		temp = SHA1CircularShift (5, A) + (B ^ C ^ D) + E + W [t] + K [1];
		E = D;
		D = C;
		C = SHA1CircularShift (30, B);
		B = A;
		A = temp;
	}
	for (t = 40; t < 60; t++) 
	{
		temp = SHA1CircularShift (5, A) + ((B & C) | (B & D) | (C & D)) + E + W [t] + K [2];
		E = D;
		D = C;
		C = SHA1CircularShift (30, B);
		B = A;
		A = temp;
	}
	for (t = 60; t < 80; t++) 
	{
		temp = SHA1CircularShift (5, A) + (B ^ C ^ D) + E + W [t] + K [3];
		E = D;
		D = C;
		C = SHA1CircularShift (30, B);
		B = A;
		A = temp;
	}
	context->Intermediate_Hash [0] += A;
	context->Intermediate_Hash [1] += B;
	context->Intermediate_Hash [2] += C;
	context->Intermediate_Hash [3] += D;
	context->Intermediate_Hash [4] += E;
	context->Message_Block_Index = 0;
	return;
}


/*====================================================================*
 * 
 *   void SHA1PadMessage (SHA1Context *context);
 *
 *  Description:
 *      According to the standard, the message must be padded to an even
 *      512 bits.  The first padding bit must be a '1'.  The last 64
 *      bits represent the length of the original message.  All bits in
 *      between should be 0.  This function will pad the message
 *      according to those rules by filling the Message_Block array
 *      accordingly.  It will also call the ProcessMessageBlock function
 *      provided appropriately.  When it returns, it can be assumed that
 *      the message digest has been computed.
 *
 *  Parameters:
 *      context: [in/out]
 *          The context to pad
 *      ProcessMessageBlock: [in]
 *          The appropriate SHA*ProcessMessageBlock function
 *  Returns:
 *      Nothing.
 *
 *  Check to see if the current message block is too small to hold
 *  the initial padding bits and length.  If so, we will pad the
 *  block, process it, and then continue padding into a second
 *  block.
 *--------------------------------------------------------------------*/

static void SHA1PadMessage (SHA1Context *context) 

{
	if (context->Message_Block_Index > 55) 
	{
		context->Message_Block [context->Message_Block_Index++] = 0x80;
		while (context->Message_Block_Index < SHA1_MSG_MAX) 
		{
			context->Message_Block [context->Message_Block_Index++] = 0;
		}
		SHA1ProcessMessageBlock (context);
		while (context->Message_Block_Index < 56) 
		{
			context->Message_Block [context->Message_Block_Index++] = 0;
		}
	}
	else 
	{
		context->Message_Block [context->Message_Block_Index++] = 0x80;
		while (context->Message_Block_Index < 56) 
		{
			context->Message_Block [context->Message_Block_Index++] = 0;
		}
	}
	context->Message_Block [56] = context->Length_High >> 24;
	context->Message_Block [57] = context->Length_High >> 16;
	context->Message_Block [58] = context->Length_High >> 8;
	context->Message_Block [59] = context->Length_High;
	context->Message_Block [60] = context->Length_Low >> 24;
	context->Message_Block [61] = context->Length_Low >> 16;
	context->Message_Block [62] = context->Length_Low >> 8;
	context->Message_Block [63] = context->Length_Low;
	SHA1ProcessMessageBlock (context);
	return;
}


/*====================================================================*
 *  
 *   int SHA1Reset (SHA1Context *context);
 *
 *  Description:
 *      This function will initialize the SHA1Context in preparation
 *      for computing a new SHA1 message digest.
 *
 *  Parameters:
 *      context: [in/out]
 *          The context to reset.
 *
 *  Returns:
 *      sha Error Code.
 *
 *--------------------------------------------------------------------*/

int SHA1Reset (SHA1Context *context) 

{
	if (!context) 
	{
		return (shaNull);
	}
	context->Length_Low = 0;
	context->Length_High = 0;
	context->Message_Block_Index = 0;
	context->Intermediate_Hash [0] = 0x67452301;
	context->Intermediate_Hash [1] = 0xEFCDAB89;
	context->Intermediate_Hash [2] = 0x98BADCFE;
	context->Intermediate_Hash [3] = 0x10325476;
	context->Intermediate_Hash [4] = 0xC3D2E1F0;
	context->Corrupted = 0;
	context->Computed = 0;
	return (shaSuccess);
}


/*====================================================================*
 *  
 *   int SHA1Result (SHA1Context *context, byte Message_Digest [SHA1HashSize]);
 *
 *  Description:
 *      This function will return the 160-bit message digest into the
 *      Message_Digest array  provided by the caller.
 *      NOTE: The first octet of hash is stored in the 0th element,
 *            the last octet of hash in the 19th element.
 *
 *  Parameters:
 *      context: [in/out]
 *          The context to use to calculate the SHA-1 hash.
 *      Message_Digest: [out]
 *          Where the digest is returned.
 *
 *  Returns:
 *      sha Error Code.
 *
 *--------------------------------------------------------------------*/

int SHA1Result (SHA1Context *context, byte Message_Digest [SHA1HashSize]) 

{
	int i;
	if (!context || !Message_Digest) 
	{
		return (shaNull);
	}
	if (context->Corrupted) 
	{
		return (context->Corrupted);
	}
	if (!context->Computed) 
	{
		SHA1PadMessage (context);
		for (i = 0; i < SHA1_MSG_MAX; i++) 
		{
			context->Message_Block [i] = 0;
		}
		context->Length_Low = 0;
		context->Length_High = 0;
		context->Computed = 1;
	}
	for (i = 0; i < SHA1HashSize; ++i) 
	{
		Message_Digest [i] = context->Intermediate_Hash [i >> 2] >> 8 * (3 - (i & 0x03));
	}
	return (shaSuccess);
}


/*====================================================================*
 *  
 *   int SHA1Input (SHA1Context *context, const byte *message_array, unsigned length);
 *
 *  Description:
 *      This function accepts an array of octets as the next portion
 *      of the message.
 *
 *  Parameters:
 *      context: [in/out]
 *          The SHA context to update
 *      message_array: [in]
 *          An array of characters representing the next portion of
 *          the message.
 *      length: [in]
 *          The length of the message in message_array
 *
 *  Returns:
 *      sha Error Code.
 *
 *--------------------------------------------------------------------*/

int SHA1Input (SHA1Context *context, const byte *message_array, unsigned length) 

{
	if (!length) 
	{
		return (shaSuccess);
	}
	if (!context || !message_array) 
	{
		return (shaNull);
	}
	if (context->Computed) 
	{
		context->Corrupted = shaStateError;
		return (shaStateError);
	}
	if (context->Corrupted) 
	{
		return (context->Corrupted);
	}
	while (length-- && !context->Corrupted) 
	{
		context->Message_Block [context->Message_Block_Index++] = (*message_array & 0xFF);
		context->Length_Low += 8;
		if (context->Length_Low == 0) 
		{
			context->Length_High++;
			if (context->Length_High == 0) 
			{
				context->Corrupted = 1;
			}
		}
		if (context->Message_Block_Index == SHA1_MSG_MAX) 
		{
			SHA1ProcessMessageBlock (context);
		}
		message_array++;
	}
	return (shaSuccess);
}


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif 

