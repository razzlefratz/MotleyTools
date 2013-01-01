/*
 * sha256.c - Implementation of the Secure Hash Algorithm-256 (SHA-256).
 *
 * Implemented from the description on the NIST Web site:
 *		http://csrc.nist.gov/cryptval/shs.html
 *
 * Copyright (C) 2002  Southern Storm Software, Pty Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "il_crypt.h"
#include "il_system.h"

#ifdef	__cplusplus

extern "C" 

{

#endif

/*
 * Some helper macros for processing 32-bit values, while
 * being careful about 32-bit vs 64-bit system differences.
 */

#if SIZE_T_SPEC_LONG > 4

#define	TRUNCLONG(x)	((x) & IL_MAX_UINT32)

#define	ROTATE(x,n)		(TRUNCLONG(((x) >> (n))) | ((x) << (32 - (n))))

#define	SHIFT(x,n)		(TRUNCLONG(((x) >> (n))))
#else

#define	TRUNCLONG(x)	(x)

#define	ROTATE(x,n)		(((x) >> (n)) | ((x) << (32 - (n))))

#define	SHIFT(x,n)		((x) >> (n))
#endif

/*
 * Helper macros used by the SHA-256 computation.
 */

#define	CH(x,y,z)		(((x) & (y)) ^ (TRUNCLONG(~(x)) & (z)))
#define	MAJ(x,y,z)		(((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define	SUM0(x)			(ROTATE((x), 2) ^ ROTATE((x), 13) ^ ROTATE((x), 22))
#define	SUM1(x)			(ROTATE((x), 6) ^ ROTATE((x), 11) ^ ROTATE((x), 25))
#define	RHO0(x)			(ROTATE((x), 7) ^ ROTATE((x), 18) ^ SHIFT((x), 3))
#define	RHO1(x)			(ROTATE((x), 17) ^ ROTATE((x), 19) ^ SHIFT((x), 10))

/*
 * Constants used in each of the SHA-256 rounds.
 */

	static ILUInt32 const K [64] = 
	{
		0x428a2f98,
		0x71374491,
		0xb5c0fbcf,
		0xe9b5dba5,
		0x3956c25b,
		0x59f111f1,
		0x923f82a4,
		0xab1c5ed5,
		0xd807aa98,
		0x12835b01,
		0x243185be,
		0x550c7dc3,
		0x72be5d74,
		0x80deb1fe,
		0x9bdc06a7,
		0xc19bf174,
		0xe49b69c1,
		0xefbe4786,
		0x0fc19dc6,
		0x240ca1cc,
		0x2de92c6f,
		0x4a7484aa,
		0x5cb0a9dc,
		0x76f988da,
		0x983e5152,
		0xa831c66d,
		0xb00327c8,
		0xbf597fc7,
		0xc6e00bf3,
		0xd5a79147,
		0x06ca6351,
		0x14292967,
		0x27b70a85,
		0x2e1b2138,
		0x4d2c6dfc,
		0x53380d13,
		0x650a7354,
		0x766a0abb,
		0x81c2c92e,
		0x92722c85,
		0xa2bfe8a1,
		0xa81a664b,
		0xc24b8b70,
		0xc76c51a3,
		0xd192e819,
		0xd6990624,
		0xf40e3585,
		0x106aa070,
		0x19a4c116,
		0x1e376c08,
		0x2748774c,
		0x34b0bcb5,
		0x391c0cb3,
		0x4ed8aa4a,
		0x5b9cca4f,
		0x682e6ff3,
		0x748f82ee,
		0x78a5636f,
		0x84c87814,
		0x8cc70208,
		0x90befffa,
		0xa4506ceb,
		0xbef9a3f7,
		0xc67178f2
	};
	void ILSHA256Init (ILSHA256Context *sha) 
	{
		sha->inputLen = 0;
		sha->A = 0x6a09e667;
		sha->B = 0xbb67ae85;
		sha->C = 0x3c6ef372;
		sha->D = 0xa54ff53a;
		sha->E = 0x510e527f;
		sha->F = 0x9b05688c;
		sha->G = 0x1f83d9ab;
		sha->H = 0x5be0cd19;
		sha->totalLen = 0;
	}

/*
 * Process a single block of input using the hash algorithm.
 */

	static void ProcessBlock (ILSHA256Context *sha, const unsigned char *block) 
	{
		ILUInt32 W [64];
		ILUInt32 a,
		b,
		c,
		d,
		e,
		f,
		g,
		h;
		ILUInt32 temp,
		temp2;
		int t;

/* Unpack the block into 64 32-bit words */

		for (t = 0; t < 16; ++t) 
		{
			W [t] = (((ILUInt32)(block [t * 4 + 0])) << 24) | (((ILUInt32)(block [t * 4 + 1])) << 16) | (((ILUInt32)(block [t * 4 + 2])) << 8) | ((ILUInt32)(block [t * 4 + 3]));
		}
		for (t = 16; t < 64; ++t) 
		{
			W [t] = TRUNCLONG (RHO1 (W [t - 2]) + W [t - 7] + RHO0 (W [t - 15]) + W [t - 16]);
		}

/* Load the SHA-256 state into local variables */

		a = sha->A;
		b = sha->B;
		c = sha->C;
		d = sha->D;
		e = sha->E;
		f = sha->F;
		g = sha->G;
		h = sha->H;

/* Perform 64 rounds of hash computations */

		for (t = 0; t < 64; ++t) 
		{
			temp = TRUNCLONG (h + SUM1 (e) + CH (e, f, g) + K [t] + W [t]);
			temp2 = TRUNCLONG (SUM0 (a) + MAJ (a, b, c));
			h = g;
			g = f;
			f = e;
			e = TRUNCLONG (d + temp);
			d = c;
			c = b;
			b = a;
			a = TRUNCLONG (temp + temp2);
		}

/* Combine the previous SHA-256 state with the new state */

		sha->A = TRUNCLONG (sha->A + a);
		sha->B = TRUNCLONG (sha->B + b);
		sha->C = TRUNCLONG (sha->C + c);
		sha->D = TRUNCLONG (sha->D + d);
		sha->E = TRUNCLONG (sha->E + e);
		sha->F = TRUNCLONG (sha->F + f);
		sha->G = TRUNCLONG (sha->G + g);
		sha->H = TRUNCLONG (sha->H + h);

/* Clear the temporary state */

		ILMemZero (W, sizeof (ILUInt32) * 64);
		a = b = c = d = e = f = g = h = temp = temp2 = 0;
	}
	void ILSHA256Data (ILSHA256Context *sha, void const *buffer, unsigned long len) 
	{
		unsigned long templen;

/* Add to the total length of the input stream */

		sha->totalLen += (ILUInt64)len;

/* Copy the blocks into the input buffer and process them */

		while (len > 0) 
		{
			if (!(sha->inputLen) && len >= 64) 
			{

/* Short cut: no point copying the data twice */

				ProcessBlock (sha, (const unsigned char *)buffer);
				buffer = (void const *)(((const unsigned char *)buffer) + 64);
				len -= 64;
			}
			else 
			{
				templen = len;
				if (templen > (64 - sha->inputLen)) 
				{
					templen = 64 - sha->inputLen;
				}
				ILMemCpy (sha->input + sha->inputLen, buffer, templen);
				if ((sha->inputLen += templen) >= 64) 
				{
					ProcessBlock (sha, sha->input);
					sha->inputLen = 0;
				}
				buffer = (void const *)(((const unsigned char *)buffer) + templen);
				len -= templen;
			}
		}
	}

/*
 * Write a 32-bit big-endian long value to a buffer.
 */

	static void WriteLong (unsigned char *buf, ILUInt32 value) 
	{
		buf [0] = (unsigned char)(value >> 24);
		buf [1] = (unsigned char)(value >> 16);
		buf [2] = (unsigned char)(value >> 8);
		buf [3] = (unsigned char)value;
	}
	void ILSHA256Finalize (ILSHA256Context *sha, unsigned char hash [IL_SHA256_HASH_SIZE]) 
	{
		ILUInt64 totalBits;

/* Compute the final hash if necessary */

		if (hash) 
		{

/* Pad the input data to a multiple of 512 bits */

			if (sha->inputLen >= 56) 
			{

/* Need two blocks worth of padding */

				sha->input [(sha->inputLen)++] = (unsigned char)0x80;
				while (sha->inputLen < 64) 
				{
					sha->input [(sha->inputLen)++] = (unsigned char)0x00;
				}
				ProcessBlock (sha, sha->input);
				sha->inputLen = 0;
			}
			else 
			{

/* Need one block worth of padding */

				sha->input [(sha->inputLen)++] = (unsigned char)0x80;
			}
			while (sha->inputLen < 56) 
			{
				sha->input [(sha->inputLen)++] = (unsigned char)0x00;
			}
			totalBits = (sha->totalLen << 3);
			WriteLong (sha->input + 56, (ILUInt32)(totalBits >> 32));
			WriteLong (sha->input + 60, (ILUInt32)totalBits);
			ProcessBlock (sha, sha->input);

/* Write the final hash value to the supplied buffer */

			WriteLong (hash, sha->A);
			WriteLong (hash + 4, sha->B);
			WriteLong (hash + 8, sha->C);
			WriteLong (hash + 12, sha->D);
			WriteLong (hash + 16, sha->E);
			WriteLong (hash + 20, sha->F);
			WriteLong (hash + 24, sha->G);
			WriteLong (hash + 28, sha->H);
		}

/* Fill the entire context structure with zeros to blank it */

		ILMemZero (sha, sizeof (ILSHA256Context));
	}

#ifdef TEST_SHA256

#include <stdio.h>

/*
 * Define the test vectors and the expected answers.
 */

	typedef struct 
	{
		char const *value;
		unsigned char expected [32];
	}
	SHATestVector;
	static SHATestVector vector1 = 
	{
		"abc",
		{
			0xba,
			0x78,
			0x16,
			0xbf,
			0x8f,
			0x01,
			0xcf,
			0xea,
			0x41,
			0x41,
			0x40,
			0xde,
			0x5d,
			0xae,
			0x22,
			0x23,
			0xb0,
			0x03,
			0x61,
			0xa3,
			0x96,
			0x17,
			0x7a,
			0x9c,
			0xb4,
			0x10,
			0xff,
			0x61,
			0xf2,
			0x00,
			0x15,
			0xad
		}
	};
	static SHATestVector vector2 = 
	{
		"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
		{
			0x24,
			0x8d,
			0x6a,
			0x61,
			0xd2,
			0x06,
			0x38,
			0xb8,
			0xe5,
			0xc0,
			0x26,
			0x93,
			0x0c,
			0x3e,
			0x60,
			0x39,
			0xa3,
			0x3c,
			0xe4,
			0x59,
			0x64,
			0xff,
			0x21,
			0x67,
			0xf6,
			0xec,
			0xed,
			0xd4,
			0x19,
			0xdb,
			0x06,
			0xc1
		}
	};

/*
 * Print a 32-byte hash value.
 */

	static void PrintHash (unsigned char *hash) 
	{
		printf ("%02X%02X %02X%02X %02X%02X %02X%02X " "%02X%02X %02X%02X %02X%02X %02X%02X " "%02X%02X %02X%02X %02X%02X %02X%02X " "%02X%02X %02X%02X %02X%02X %02X%02X\n", hash [0], hash [1], hash [2], hash [3], hash [4], hash [5], hash [6], hash [7], hash [8], hash [9], hash [10], hash [11], hash [12], hash [13], hash [14], hash [15], hash [16], hash [17], hash [18], hash [19], hash [20], hash [21], hash [22], hash [23], hash [24], hash [25], hash [26], hash [27], hash [28], hash [29], hash [30], hash [31]);
	}

/*
 * Process a test vector.
 */

	static void ProcessVector (SHATestVector *vector) 
	{
		ILSHA256Context sha;
		unsigned char hash [32];

/* Compute the hash */

		ILSHA256Init (&sha);
		ILSHA256Data (&sha, vector->value, strlen (vector->value));
		ILSHA256Finalize (&sha, hash);

/* Report the results */

		printf ("Value    = %s\n", vector->value);
		printf ("Expected = ");
		PrintHash (vector->expected);
		printf ("Actual   = ");
		PrintHash (hash);
		if (ILMemCmp (vector->expected, hash, 32) != 0) 
		{
			printf ("*** test failed ***\n");
		}
		printf ("\n");
	}
	int main (int argc, char *argv []) 
	{
		printf ("\n");
		ProcessVector (&vector1);
		ProcessVector (&vector2);
		return (0);
	}

#endif /* TEST_SHA256 */

#ifdef	__cplusplus

};


#endif

