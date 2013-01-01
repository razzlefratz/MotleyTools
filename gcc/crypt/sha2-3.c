
00016 

#include "includes.h"

00017 00018 

#include "common.h"

00019 

#include "sha256.h"

00020 

#include "crypto.h"

00021 00022 00033 void hmac_sha256_vector (const u8 *key, size_t key_len, size_t num_elem, 00034 const u8 *addr [], const size_t *len, u8 *mac) 00035 

{
	00036 unsigned char k_pad [64];

/* padding - key XORd with ipad/opad */

	00037 unsigned char tk [20];
	00038 const u8 *_addr [6];
	00039 size_t _len [6],
	i;
	00040 00041 if (num_elem &gt; 5) 
	{
		00042 /*
00043                  * Fixed limit on the number of fragments to avoid having to
00044                  * allocate memory (which could fail).
00045                  */ 00046 return;
		00047
	}
	00048 00049 /* if key is longer than 64 bytes reset it to key = SHA256(key) */ 00050 if (key_len &gt; 64) 
	{
		00051 sha256_vector (1, &amp; key, &amp; key_len, tk);
		00052 key = tk;
		00053 key_len = 32;
		00054
	}
	00055 00056 /* the HMAC_SHA256 transform looks like:
00057          *
00058          * SHA256(K XOR opad, SHA256(K XOR ipad, text))
00059          *
00060          * where K is an n byte key
00061          * ipad is the byte 0x36 repeated 64 times
00062          * opad is the byte 0x5c repeated 64 times
00063          * and text is the data being protected */ 00064 00065 /* start out by storing key in ipad */ 00066 memset (k_pad, 0, sizeof (k_pad));
	00067 memcpy (k_pad, key, key_len);
	00068 /* XOR key with ipad values */ 00069 for (i = 0; i &lt; 64; i++) 00070 k_pad [i] ^= 0x36;
	00071 00072 /* perform inner SHA256 */ 00073 _addr [0] = k_pad;
	00074 _len [0] = 64;
	00075 for (i = 0; i &lt; num_elem; i++) 
	{
		00076 _addr [i + 1] = addr [i];
		00077 _len [i + 1] = len [i];
		00078
	}
	00079 sha256_vector (1 + num_elem, _addr, _len, mac);
	00080 00081 memset (k_pad, 0, sizeof (k_pad));
	00082 memcpy (k_pad, key, key_len);
	00083 /* XOR key with opad values */ 00084 for (i = 0; i &lt; 64; i++) 00085 k_pad [i] ^= 0x5c;
	00086 00087 /* perform outer SHA256 */ 00088 _addr [0] = k_pad;
	00089 _len [0] = 64;
	00090 _addr [1] = mac;
	00091 _len [1] = SHA256_MAC_LEN;
	00092 sha256_vector (2, _addr, _len, mac);
	00093
}

00094 00095 00105 void hmac_sha256 (const u8 *key, size_t key_len, const u8 *data, 00106 size_t data_len, u8 *mac) 00107 

{
	00108 hmac_sha256_vector (key, key_len, 1, &amp; data, &amp; data_len, mac);
	00109
}

00110 00111 00126 void sha256_prf (const u8 *key, size_t key_len, char const *label, 00127 const u8 *data, size_t data_len, u8 *buf, size_t buf_len) 00128 

{
	00129 u16 counter = 0;
	00130 size_t pos,
	plen;
	00131 u8 hash [SHA256_MAC_LEN];
	00132 const u8 *addr [3];
	00133 size_t len [3];
	00134 u8 counter_le [2];
	00135 00136 addr [0] = counter_le;
	00137 len [0] = 2;
	00138 addr [1] = (u8 *) label;
	00139 len [1] = strlen (label) + 1;
	00140 addr [2] = data;
	00141 len [2] = data_len;
	00142 00143 pos = 0;
	00144 while (pos &lt; buf_len) 
	{
		00145 plen = buf_len - pos;
		00146 WPA_PUT_LE16 (counter_le, counter);
		00147 if (plen &gt; = SHA256_MAC_LEN) 
		{
			00148 hmac_sha256_vector (key, key_len, 3, addr, len, 00149 &amp; buf [pos]);
			00150 pos += SHA256_MAC_LEN;
			00151
		}
		else 
		{
			00152 hmac_sha256_vector (key, key_len, 3, addr, len, hash);
			00153 memcpy (&amp; buf [pos], hash, plen);
			00154 break;
			00155
		}
		00156 counter++;
		00157
	}
	00158
}

00159 00160 00161 

#ifdef INTERNAL_SHA256

00162 00163 struct sha256_state 

{
	00164 u64 length;
	00165 u32 state [8],
	curlen;
	00166 u8 buf [64];
	00167
};

00168 00169 static void sha256_init (struct sha256_state *md);
00170 static int sha256_process (struct sha256_state *md, const unsigned char *in, 00171 unsigned long inlen);
00172 static int sha256_done (struct sha256_state *md, unsigned char *out);
00173 00174 00183 void sha256_vector (size_t num_elem, const u8 *addr [], const size_t *len, 00184 u8 *mac) 00185 

{
	00186 struct sha256_state ctx;
	00187 size_t i;
	00188 00189 sha256_init (&amp; ctx);
	00190 for (i = 0; i &lt; num_elem; i++) 00191 sha256_process (&amp; ctx, addr [i], len [i]);
	00192 sha256_done (&amp; ctx, mac);
	00193
}

00194 00195 00196 /* ===== start - public domain SHA256 implementation ===== */ 00197 00198 /* This is based on SHA256 implementation in LibTomCrypt that was released into
00199  * public domain by Tom St Denis. */ 00200 00201 /* the K array */ 00202 static const unsigned long K [64] = 

{
	00203 0x428a2f98UL,
	0x71374491UL,
	0xb5c0fbcfUL,
	0xe9b5dba5UL,
	0x3956c25bUL,
	00204 0x59f111f1UL,
	0x923f82a4UL,
	0xab1c5ed5UL,
	0xd807aa98UL,
	0x12835b01UL,
	00205 0x243185beUL,
	0x550c7dc3UL,
	0x72be5d74UL,
	0x80deb1feUL,
	0x9bdc06a7UL,
	00206 0xc19bf174UL,
	0xe49b69c1UL,
	0xefbe4786UL,
	0x0fc19dc6UL,
	0x240ca1ccUL,
	00207 0x2de92c6fUL,
	0x4a7484aaUL,
	0x5cb0a9dcUL,
	0x76f988daUL,
	0x983e5152UL,
	00208 0xa831c66dUL,
	0xb00327c8UL,
	0xbf597fc7UL,
	0xc6e00bf3UL,
	0xd5a79147UL,
	00209 0x06ca6351UL,
	0x14292967UL,
	0x27b70a85UL,
	0x2e1b2138UL,
	0x4d2c6dfcUL,
	00210 0x53380d13UL,
	0x650a7354UL,
	0x766a0abbUL,
	0x81c2c92eUL,
	0x92722c85UL,
	00211 0xa2bfe8a1UL,
	0xa81a664bUL,
	0xc24b8b70UL,
	0xc76c51a3UL,
	0xd192e819UL,
	00212 0xd6990624UL,
	0xf40e3585UL,
	0x106aa070UL,
	0x19a4c116UL,
	0x1e376c08UL,
	00213 0x2748774cUL,
	0x34b0bcb5UL,
	0x391c0cb3UL,
	0x4ed8aa4aUL,
	0x5b9cca4fUL,
	00214 0x682e6ff3UL,
	0x748f82eeUL,
	0x78a5636fUL,
	0x84c87814UL,
	0x8cc70208UL,
	00215 0x90befffaUL,
	0xa4506cebUL,
	0xbef9a3f7UL,
	0xc67178f2UL 00216
};

00217 00218 00219 /* Various logical functions */ 00220 

#define RORc(x, y) \
00221 ( ((((unsigned long) (x) &amp; 0xFFFFFFFFUL) &gt;&gt; (unsigned long) ((y) &amp; 31)) | \
00222    ((unsigned long) (x) &lt;&lt; (unsigned long) (32 - ((y) &amp; 31)))) &amp; 0xFFFFFFFFUL)

00223 

#define Ch(x,y,z)       (z ^ (x &amp; (y ^ z)))

00224 

#define Maj(x,y,z)      (((x | y) &amp; z) | (x &amp; y)) 

00225 

#define S(x, n)         RORc((x), (n))

00226 

#define R(x, n)         (((x)&amp;0xFFFFFFFFUL)&gt;&gt;(n))

00227 

#define Sigma0(x)       (S(x, 2) ^ S(x, 13) ^ S(x, 22))

00228 

#define Sigma1(x)       (S(x, 6) ^ S(x, 11) ^ S(x, 25))

00229 

#define Gamma0(x)       (S(x, 7) ^ S(x, 18) ^ R(x, 3))

00230 

#define Gamma1(x)       (S(x, 17) ^ S(x, 19) ^ R(x, 10))

00231 

#ifndef MIN

00232 

#define MIN(x, y) (((x) &lt; (y)) ? (x) : (y))

00233 

#endif

00234 00235 /* compress 512-bits */ 00236 static int sha256_compress (struct sha256_state *md, unsigned char *buf) 00237 

{
	00238 u32 S [8],
	W [64],
	t0,
	t1;
	00239 u32 t;
	00240 int i;
	00241 00242 /* copy state into S */ 00243 for (i = 0; i &lt; 8; i++) 
	{
		00244 S [i] = md-&gt;
		state [i];
		00245
	}
	00246 00247 /* copy the state into 512-bits into W[0..15] */ 00248 for (i = 0; i &lt; 16; i++) 00249 W [i] = WPA_GET_BE32 (buf + (4 * i));
	00250 00251 /* fill W[16..63] */ 00252 for (i = 16; i &lt; 64; i++) 
	{
		00253 W [i] = Gamma1 (W [i - 2]) + W [i - 7] + Gamma0 (W [i - 15]) + 00254 W [i - 16];
		00255
	}
	00256 00257 /* Compress */ 00258 

#define RND(a,b,c,d,e,f,g,h,i)                          \
00259         t0 = h + Sigma1(e) + Ch(e, f, g) + K[i] + W[i]; \
00260         t1 = Sigma0(a) + Maj(a, b, c);                  \
00261         d += t0;                                        \
00262         h  = t0 + t1;

	00263 00264 for (i = 0; i &lt; 64; ++i) 
	{
		00265 RND (S [0], S [1], S [2], S [3], S [4], S [5], S [6], S [7], i);
		00266 t = S [7];
		S [7] = S [6];
		S [6] = S [5];
		S [5] = S [4];
		00267 S [4] = S [3];
		S [3] = S [2];
		S [2] = S [1];
		S [1] = S [0];
		S [0] = t;
		00268
	}
	00269 00270 /* feedback */ 00271 for (i = 0; i &lt; 8; i++) 
	{
		00272 md-&gt;
		state [i] = md-&gt;
		state [i] + S [i];
		00273
	}
	00274 return 0;
	00275
}

00276 00277 00278 /* Initialize the hash state */ 00279 static void sha256_init (struct sha256_state *md) 00280 

{
	00281 md-&gt;
	curlen = 0;
	00282 md-&gt;
	length = 0;
	00283 md-&gt;
	state [0] = 0x6A09E667UL;
	00284 md-&gt;
	state [1] = 0xBB67AE85UL;
	00285 md-&gt;
	state [2] = 0x3C6EF372UL;
	00286 md-&gt;
	state [3] = 0xA54FF53AUL;
	00287 md-&gt;
	state [4] = 0x510E527FUL;
	00288 md-&gt;
	state [5] = 0x9B05688CUL;
	00289 md-&gt;
	state [6] = 0x1F83D9ABUL;
	00290 md-&gt;
	state [7] = 0x5BE0CD19UL;
	00291
}

00292 00300 static int sha256_process (struct sha256_state *md, const unsigned char *in, 00301 unsigned long inlen) 00302 

{
	00303 unsigned long n;
	00304 

#define block_size 64

	00305 00306 if (md-&gt; curlen &gt; sizeof (md-&gt; buf)) 00307 return -1;
	00308 00309 while (inlen &gt; 0) 
	{
		00310 if (md-&gt; curlen == 0 &amp; &amp; inlen &gt; = block_size) 
		{
			00311 if (sha256_compress (md, (unsigned char *) in) &lt; 0) 00312 return -1;
			00313 md-&gt;
			length += block_size * 8;
			00314 in += block_size;
			00315 inlen -= block_size;
			00316
		}
		else 
		{
			00317 n = MIN (inlen, (block_size - md-&gt; curlen));
			00318 memcpy (md-&gt; buf + md-&gt; curlen, in, n);
			00319 md-&gt;
			curlen += n;
			00320 in += n;
			00321 inlen -= n;
			00322 if (md-&gt; curlen == block_size) 
			{
				00323 if (sha256_compress (md, md-&gt; buf) &lt; 0) 00324 return -1;
				00325 md-&gt;
				length += 8 * block_size;
				00326 md-&gt;
				curlen = 0;
				00327
			}
			00328
		}
		00329
	}
	00330 00331 return 0;
	00332
}

00333 00334 00341 static int sha256_done (struct sha256_state *md, unsigned char *out) 00342 

{
	00343 int i;
	00344 00345 if (md-&gt; curlen &gt; = sizeof (md-&gt; buf)) 00346 return -1;
	00347 00348 /* increase the length of the message */ 00349 md-&gt;
	length += md-&gt;
	curlen * 8;
	00350 00351 /* append the '1' bit */ 00352 md-&gt;
	buf [md-&gt; curlen++] = (unsigned char) 0x80;
	00353 00354 /* if the length is currently above 56 bytes we append zeros
00355          * then compress.  Then we can fall back to padding zeros and length
00356          * encoding like normal.
00357          */ 00358 if (md-&gt; curlen &gt; 56) 
	{
		00359 while (md-&gt; curlen &lt; 64) 
		{
			00360 md-&gt;
			buf [md-&gt; curlen++] = (unsigned char) 0;
			00361
		}
		00362 sha256_compress (md, md-&gt; buf);
		00363 md-&gt;
		curlen = 0;
		00364
	}
	00365 00366 /* pad upto 56 bytes of zeroes */ 00367 while (md-&gt; curlen &lt; 56) 
	{
		00368 md-&gt;
		buf [md-&gt; curlen++] = (unsigned char) 0;
		00369
	}
	00370 00371 /* store length */ 00372 WPA_PUT_BE64 (md-&gt; buf + 56, md-&gt; length);
	00373 sha256_compress (md, md-&gt; buf);
	00374 00375 /* copy output */ 00376 for (i = 0; i &lt; 8; i++) 00377 WPA_PUT_BE32 (out + (4 * i), md-&gt; state [i]);
	00378 00379 return 0;
	00380
}

00381 00382 /* ===== end - public domain SHA256 implementation ===== */ 00383 00384 

#endif /* INTERNAL_SHA256 */

00385 
