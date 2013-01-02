/*====================================================================*
 *
 *   octype.cpp - implementation of the octype class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCTYPE_SOURCE
#define oCTYPE_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <climits>
#include <cstdio>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/octype.hpp"

/*====================================================================*
 *   private constants;
 *--------------------------------------------------------------------*/

#define CTYPE_B_NTYPE (0) 
#define CTYPE_B_CNTRL (1 << 0) 
#define CTYPE_B_SPACE (1 << 1) 
#define CTYPE_B_UPPER (1 << 2) 
#define CTYPE_B_LOWER (1 << 3) 
#define CTYPE_B_DIGIT (1 << 4) 
#define CTYPE_B_HEX   (1 << 5) 
#define CTYPE_B_PUNCT (1 << 6) 
#define CTYPE_B_IDENT (1 << 7) 
#define CTYPE_B_ARITH (1 << 8) 

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

const unsigned short octype::mtable [UCHAR_MAX+1] = 

{

/* 000 000 00 NUL */

	CTYPE_B_CNTRL,

/* 001 001 01 SOH */

	CTYPE_B_CNTRL,

/* 002 002 02 STX */

	CTYPE_B_CNTRL,

/* 003 003 03 ETX */

	CTYPE_B_CNTRL,

/* 004 004 04 EOT */

	CTYPE_B_CNTRL,

/* 005 005 05 ENQ */

	CTYPE_B_CNTRL,

/* 006 006 06 ACK */

	CTYPE_B_CNTRL,

/* 007 007 07 BEL */

	CTYPE_B_CNTRL,

/* 008 010 08 BS  */

	CTYPE_B_CNTRL,

/* 009 011 09 HT  */

	CTYPE_B_CNTRL | CTYPE_B_SPACE,

/* 010 012 0A LF  */

	CTYPE_B_CNTRL | CTYPE_B_SPACE,

/* 011 013 0B VT  */

	CTYPE_B_CNTRL | CTYPE_B_SPACE,

/* 012 014 0C FF  */

	CTYPE_B_CNTRL | CTYPE_B_SPACE,

/* 013 015 0D CR  */

	CTYPE_B_CNTRL | CTYPE_B_SPACE,

/* 014 016 0E SO  */

	CTYPE_B_CNTRL,

/* 015 017 0F SI  */

	CTYPE_B_CNTRL,

/* 016 020 10 DLE */

	CTYPE_B_CNTRL,

/* 017 021 11 DC1 */

	CTYPE_B_CNTRL,

/* 018 022 12 DC2 */

	CTYPE_B_CNTRL,

/* 019 023 13 DC3 */

	CTYPE_B_CNTRL,

/* 020 024 14 DC4 */

	CTYPE_B_CNTRL,

/* 021 025 15 NAK */

	CTYPE_B_CNTRL,

/* 022 026 16 SYN */

	CTYPE_B_CNTRL,

/* 023 027 17 ETB */

	CTYPE_B_CNTRL,

/* 024 030 18 CAN */

	CTYPE_B_CNTRL,

/* 025 031 19 EM  */

	CTYPE_B_CNTRL,

/* 026 032 1A SUB */

	CTYPE_B_CNTRL,

/* 027 033 1B ESC */

	CTYPE_B_CNTRL,

/* 028 034 1C FS  */

	CTYPE_B_CNTRL,

/* 029 035 1D GS  */

	CTYPE_B_CNTRL,

/* 030 036 1E RS  */

	CTYPE_B_CNTRL,

/* 031 037 1F US  */

	CTYPE_B_CNTRL,

/* 032 040 20 [ ] */

	CTYPE_B_SPACE,

/* 033 041 21 [!] */

	CTYPE_B_PUNCT,

/* 034 042 22 ["] */

	CTYPE_B_PUNCT,

/* 035 043 23 [#] */

	CTYPE_B_PUNCT,

/* 036 044 24 [$] */

	CTYPE_B_PUNCT | CTYPE_B_IDENT,

/* 037 045 25 [%] */

	CTYPE_B_PUNCT,

/* 038 046 26 [&] */

	CTYPE_B_PUNCT,

/* 039 047 27 ['] */

	CTYPE_B_PUNCT,

/* 040 050 28 [(] */

	CTYPE_B_PUNCT,

/* 041 051 29 [)] */

	CTYPE_B_PUNCT,

/* 042 052 2A [*] */

	CTYPE_B_PUNCT,

/* 043 053 2B [+] */

	CTYPE_B_PUNCT,

/* 044 054 2C [,] */

	CTYPE_B_PUNCT,

/* 045 055 2D [-] */

	CTYPE_B_PUNCT,

/* 046 056 2E [.] */

	CTYPE_B_PUNCT,

/* 047 057 2F [/] */

	CTYPE_B_PUNCT,

/* 048 060 30 [0] */

	CTYPE_B_DIGIT | CTYPE_B_IDENT | CTYPE_B_HEX,

/* 049 061 31 [1] */

	CTYPE_B_DIGIT | CTYPE_B_IDENT | CTYPE_B_HEX,

/* 050 062 32 [2] */

	CTYPE_B_DIGIT | CTYPE_B_IDENT | CTYPE_B_HEX,

/* 051 063 33 [3] */

	CTYPE_B_DIGIT | CTYPE_B_IDENT | CTYPE_B_HEX,

/* 052 064 34 [4] */

	CTYPE_B_DIGIT | CTYPE_B_IDENT | CTYPE_B_HEX,

/* 053 065 35 [5] */

	CTYPE_B_DIGIT | CTYPE_B_IDENT | CTYPE_B_HEX,

/* 054 066 36 [6] */

	CTYPE_B_DIGIT | CTYPE_B_IDENT | CTYPE_B_HEX,

/* 055 067 37 [7] */

	CTYPE_B_DIGIT | CTYPE_B_IDENT | CTYPE_B_HEX,

/* 056 070 38 [8] */

	CTYPE_B_DIGIT | CTYPE_B_IDENT | CTYPE_B_HEX,

/* 057 071 39 [9] */

	CTYPE_B_DIGIT | CTYPE_B_IDENT | CTYPE_B_HEX,

/* 058 072 3A [:] */

	CTYPE_B_PUNCT,

/* 059 073 3B [;] */

	CTYPE_B_PUNCT,

/* 060 074 3C [<] */

	CTYPE_B_PUNCT,

/* 061 075 3D [=] */

	CTYPE_B_PUNCT,

/* 062 076 3E [>] */

	CTYPE_B_PUNCT,

/* 063 077 3F [?] */

	CTYPE_B_PUNCT,

/* 064 100 40 [@] */

	CTYPE_B_PUNCT,

/* 065 101 41 [A] */

	CTYPE_B_UPPER | CTYPE_B_IDENT | CTYPE_B_HEX,

/* 066 102 42 [B] */

	CTYPE_B_UPPER | CTYPE_B_IDENT | CTYPE_B_HEX,

/* 067 103 43 [C] */

	CTYPE_B_UPPER | CTYPE_B_IDENT | CTYPE_B_HEX,

/* 068 104 44 [D] */

	CTYPE_B_UPPER | CTYPE_B_IDENT | CTYPE_B_HEX,

/* 069 105 45 [E] */

	CTYPE_B_UPPER | CTYPE_B_IDENT | CTYPE_B_HEX,

/* 070 106 46 [F] */

	CTYPE_B_UPPER | CTYPE_B_IDENT | CTYPE_B_HEX,

/* 071 107 47 [G] */

	CTYPE_B_UPPER | CTYPE_B_IDENT,

/* 072 110 48 [H] */

	CTYPE_B_UPPER | CTYPE_B_IDENT,

/* 073 111 49 [I] */

	CTYPE_B_UPPER | CTYPE_B_IDENT,

/* 074 112 4A [J] */

	CTYPE_B_UPPER | CTYPE_B_IDENT,

/* 075 113 4B [K] */

	CTYPE_B_UPPER | CTYPE_B_IDENT,

/* 076 114 4C [L] */

	CTYPE_B_UPPER | CTYPE_B_IDENT,

/* 077 115 4D [M] */

	CTYPE_B_UPPER | CTYPE_B_IDENT,

/* 078 116 4E [N] */

	CTYPE_B_UPPER | CTYPE_B_IDENT,

/* 079 117 4F [O] */

	CTYPE_B_UPPER | CTYPE_B_IDENT,

/* 080 120 50 [P] */

	CTYPE_B_UPPER | CTYPE_B_IDENT,

/* 081 121 51 [Q] */

	CTYPE_B_UPPER | CTYPE_B_IDENT,

/* 082 122 52 [R] */

	CTYPE_B_UPPER | CTYPE_B_IDENT,

/* 083 123 53 [S] */

	CTYPE_B_UPPER | CTYPE_B_IDENT,

/* 084 124 54 [T] */

	CTYPE_B_UPPER | CTYPE_B_IDENT,

/* 085 125 55 [U] */

	CTYPE_B_UPPER | CTYPE_B_IDENT,

/* 086 126 56 [V] */

	CTYPE_B_UPPER | CTYPE_B_IDENT,

/* 087 127 57 [W] */

	CTYPE_B_UPPER | CTYPE_B_IDENT,

/* 088 130 58 [X] */

	CTYPE_B_UPPER | CTYPE_B_IDENT,

/* 089 131 59 [Y] */

	CTYPE_B_UPPER | CTYPE_B_IDENT,

/* 090 132 5A [Z] */

	CTYPE_B_UPPER | CTYPE_B_IDENT,

/* 091 133 5B [[] */

	CTYPE_B_PUNCT,

/* 092 134 5C [\] */

	CTYPE_B_PUNCT,

/* 093 135 5D []] */

	CTYPE_B_PUNCT,

/* 094 136 5E [^] */

	CTYPE_B_PUNCT,

/* 095 137 5F [_] */

	CTYPE_B_PUNCT | CTYPE_B_IDENT,

/* 096 140 60 [`] */

	CTYPE_B_PUNCT,

/* 097 141 61 [a] */

	CTYPE_B_LOWER | CTYPE_B_IDENT | CTYPE_B_HEX,

/* 098 142 62 [b] */

	CTYPE_B_LOWER | CTYPE_B_IDENT | CTYPE_B_HEX,

/* 099 143 63 [c] */

	CTYPE_B_LOWER | CTYPE_B_IDENT | CTYPE_B_HEX,

/* 100 144 64 [d] */

	CTYPE_B_LOWER | CTYPE_B_IDENT | CTYPE_B_HEX,

/* 101 145 65 [e] */

	CTYPE_B_LOWER | CTYPE_B_IDENT | CTYPE_B_HEX,

/* 102 146 66 [f] */

	CTYPE_B_LOWER | CTYPE_B_IDENT | CTYPE_B_HEX,

/* 103 147 67 [g] */

	CTYPE_B_LOWER | CTYPE_B_IDENT,

/* 104 150 68 [h] */

	CTYPE_B_LOWER | CTYPE_B_IDENT,

/* 105 151 69 [i] */

	CTYPE_B_LOWER | CTYPE_B_IDENT,

/* 106 152 6A [j] */

	CTYPE_B_LOWER | CTYPE_B_IDENT,

/* 107 153 6B [k] */

	CTYPE_B_LOWER | CTYPE_B_IDENT,

/* 108 154 6C [l] */

	CTYPE_B_LOWER | CTYPE_B_IDENT,

/* 109 155 6D [m] */

	CTYPE_B_LOWER | CTYPE_B_IDENT,

/* 110 156 6E [n] */

	CTYPE_B_LOWER | CTYPE_B_IDENT,

/* 111 157 6F [o] */

	CTYPE_B_LOWER | CTYPE_B_IDENT,

/* 112 160 70 [p] */

	CTYPE_B_LOWER | CTYPE_B_IDENT,

/* 113 161 71 [q] */

	CTYPE_B_LOWER | CTYPE_B_IDENT,

/* 114 162 72 [r] */

	CTYPE_B_LOWER | CTYPE_B_IDENT,

/* 115 163 73 [s] */

	CTYPE_B_LOWER | CTYPE_B_IDENT,

/* 116 164 74 [t] */

	CTYPE_B_LOWER | CTYPE_B_IDENT,

/* 117 165 75 [u] */

	CTYPE_B_LOWER | CTYPE_B_IDENT,

/* 118 166 76 [v] */

	CTYPE_B_LOWER | CTYPE_B_IDENT,

/* 119 167 77 [w] */

	CTYPE_B_LOWER | CTYPE_B_IDENT,

/* 120 170 78 [x] */

	CTYPE_B_LOWER | CTYPE_B_IDENT,

/* 121 171 79 [y] */

	CTYPE_B_LOWER | CTYPE_B_IDENT,

/* 122 172 7A [z] */

	CTYPE_B_LOWER | CTYPE_B_IDENT,

/* 123 173 7B [{] */

	CTYPE_B_PUNCT,

/* 124 174 7C [|] */

	CTYPE_B_PUNCT,

/* 125 175 7D [}] */

	CTYPE_B_PUNCT,

/* 126 176 7E [~] */

	CTYPE_B_PUNCT,

/* 127 177 7F DEL */

	CTYPE_B_CNTRL,

/* 128 200 80 [Ä] */

	CTYPE_B_NTYPE,

/* 129 201 81 [Å] */

	CTYPE_B_NTYPE,

/* 130 202 82 [Ç] */

	CTYPE_B_NTYPE,

/* 131 203 83 [É] */

	CTYPE_B_NTYPE,

/* 132 204 84 [Ñ] */

	CTYPE_B_NTYPE,

/* 133 205 85 [Ö] */

	CTYPE_B_NTYPE,

/* 134 206 86 [Ü] */

	CTYPE_B_NTYPE,

/* 135 207 87 [á] */

	CTYPE_B_NTYPE,

/* 136 210 88 [à] */

	CTYPE_B_NTYPE,

/* 137 211 89 [â] */

	CTYPE_B_NTYPE,

/* 138 212 8A [ä] */

	CTYPE_B_NTYPE,

/* 139 213 8B [ã] */

	CTYPE_B_NTYPE,

/* 140 214 8C [å] */

	CTYPE_B_NTYPE,

/* 141 215 8D [ç] */

	CTYPE_B_NTYPE,

/* 142 216 8E [é] */

	CTYPE_B_NTYPE,

/* 143 217 8F [è] */

	CTYPE_B_NTYPE,

/* 144 220 90 [ê] */

	CTYPE_B_NTYPE,

/* 145 221 91 [ë] */

	CTYPE_B_NTYPE,

/* 146 222 92 [í] */

	CTYPE_B_NTYPE,

/* 147 223 93 [ì] */

	CTYPE_B_NTYPE,

/* 148 224 94 [î] */

	CTYPE_B_NTYPE,

/* 149 225 95 [ï] */

	CTYPE_B_NTYPE,

/* 150 226 96 [ñ] */

	CTYPE_B_NTYPE,

/* 151 227 97 [ó] */

	CTYPE_B_NTYPE,

/* 152 230 98 [ò] */

	CTYPE_B_NTYPE,

/* 153 231 99 [ô] */

	CTYPE_B_NTYPE,

/* 154 232 9A [ö] */

	CTYPE_B_NTYPE,

/* 155 233 9B [õ] */

	CTYPE_B_NTYPE,

/* 156 234 9C [ú] */

	CTYPE_B_NTYPE,

/* 157 235 9D [ù] */

	CTYPE_B_NTYPE,

/* 158 236 9E [û] */

	CTYPE_B_NTYPE,

/* 159 237 9F [ü] */

	CTYPE_B_NTYPE,

/* 160 240 A0 [†] */

	CTYPE_B_NTYPE,

/* 161 241 A1 [°] */

	CTYPE_B_NTYPE,

/* 162 242 A2 [¢] */

	CTYPE_B_NTYPE,

/* 163 243 A3 [£] */

	CTYPE_B_NTYPE,

/* 164 244 A4 [§] */

	CTYPE_B_NTYPE,

/* 165 245 A5 [•] */

	CTYPE_B_NTYPE,

/* 166 246 A6 [¶] */

	CTYPE_B_NTYPE,

/* 167 247 A7 [ß] */

	CTYPE_B_NTYPE,

/* 168 250 A8 [®] */

	CTYPE_B_NTYPE,

/* 169 251 A9 [©] */

	CTYPE_B_NTYPE,

/* 170 252 AA [™] */

	CTYPE_B_NTYPE,

/* 171 253 AB [´] */

	CTYPE_B_NTYPE,

/* 172 254 AC [¨] */

	CTYPE_B_NTYPE,

/* 173 255 AD [≠] */

	CTYPE_B_NTYPE,

/* 174 256 AE [Æ] */

	CTYPE_B_NTYPE,

/* 175 257 AF [Ø] */

	CTYPE_B_NTYPE,

/* 176 260 B0 [∞] */

	CTYPE_B_NTYPE,

/* 177 261 B1 [±] */

	CTYPE_B_NTYPE,

/* 178 262 B2 [≤] */

	CTYPE_B_NTYPE,

/* 179 263 B3 [≥] */

	CTYPE_B_NTYPE,

/* 180 264 B4 [¥] */

	CTYPE_B_NTYPE,

/* 181 265 B5 [µ] */

	CTYPE_B_NTYPE,

/* 182 266 B6 [∂] */

	CTYPE_B_NTYPE,

/* 183 267 B7 [∑] */

	CTYPE_B_NTYPE,

/* 184 270 B8 [∏] */

	CTYPE_B_NTYPE,

/* 185 271 B9 [π] */

	CTYPE_B_NTYPE,

/* 186 272 BA [∫] */

	CTYPE_B_NTYPE,

/* 187 273 BB [ª] */

	CTYPE_B_NTYPE,

/* 188 274 BC [º] */

	CTYPE_B_NTYPE,

/* 189 275 BD [Ω] */

	CTYPE_B_NTYPE,

/* 190 276 BE [æ] */

	CTYPE_B_NTYPE,

/* 191 277 BF [ø] */

	CTYPE_B_NTYPE,

/* 192 300 C0 [¿] */

	CTYPE_B_NTYPE,

/* 193 301 C1 [¡] */

	CTYPE_B_NTYPE,

/* 194 302 C2 [¬] */

	CTYPE_B_NTYPE,

/* 195 303 C3 [√] */

	CTYPE_B_NTYPE,

/* 196 304 C4 [ƒ] */

	CTYPE_B_NTYPE,

/* 197 305 C5 [≈] */

	CTYPE_B_NTYPE,

/* 198 306 C6 [∆] */

	CTYPE_B_NTYPE,

/* 199 307 C7 [«] */

	CTYPE_B_NTYPE,

/* 200 310 C8 [»] */

	CTYPE_B_NTYPE,

/* 201 311 C9 […] */

	CTYPE_B_NTYPE,

/* 202 312 CA [ ] */

	CTYPE_B_NTYPE,

/* 203 313 CB [À] */

	CTYPE_B_NTYPE,

/* 204 314 CC [Ã] */

	CTYPE_B_NTYPE,

/* 205 315 CD [Õ] */

	CTYPE_B_NTYPE,

/* 206 316 CE [Œ] */

	CTYPE_B_NTYPE,

/* 207 317 CF [œ] */

	CTYPE_B_NTYPE,

/* 208 320 D0 [–] */

	CTYPE_B_NTYPE,

/* 209 321 D1 [—] */

	CTYPE_B_NTYPE,

/* 210 322 D2 [“] */

	CTYPE_B_NTYPE,

/* 211 323 D3 [”] */

	CTYPE_B_NTYPE,

/* 212 324 D4 [‘] */

	CTYPE_B_NTYPE,

/* 213 325 D5 [’] */

	CTYPE_B_NTYPE,

/* 214 326 D6 [÷] */

	CTYPE_B_NTYPE,

/* 215 327 D7 [◊] */

	CTYPE_B_NTYPE,

/* 216 330 D8 [ÿ] */

	CTYPE_B_NTYPE,

/* 217 331 D9 [Ÿ] */

	CTYPE_B_NTYPE,

/* 218 332 DA [⁄] */

	CTYPE_B_NTYPE,

/* 219 333 DB [€] */

	CTYPE_B_NTYPE,

/* 220 334 DC [‹] */

	CTYPE_B_NTYPE,

/* 221 335 DD [›] */

	CTYPE_B_NTYPE,

/* 222 336 DE [ﬁ] */

	CTYPE_B_NTYPE,

/* 223 337 DF [ﬂ] */

	CTYPE_B_NTYPE,

/* 224 340 E0 [‡] */

	CTYPE_B_NTYPE,

/* 225 341 E1 [·] */

	CTYPE_B_NTYPE,

/* 226 342 E2 [‚] */

	CTYPE_B_NTYPE,

/* 227 343 E3 [„] */

	CTYPE_B_NTYPE,

/* 228 344 E4 [‰] */

	CTYPE_B_NTYPE,

/* 229 345 E5 [Â] */

	CTYPE_B_NTYPE,

/* 230 346 E6 [Ê] */

	CTYPE_B_NTYPE,

/* 231 347 E7 [Á] */

	CTYPE_B_NTYPE,

/* 232 350 E8 [Ë] */

	CTYPE_B_NTYPE,

/* 233 351 E9 [È] */

	CTYPE_B_NTYPE,

/* 234 352 EA [Í] */

	CTYPE_B_NTYPE,

/* 235 353 EB [Î] */

	CTYPE_B_NTYPE,

/* 236 354 EC [Ï] */

	CTYPE_B_NTYPE,

/* 237 355 ED [Ì] */

	CTYPE_B_NTYPE,

/* 238 356 EE [Ó] */

	CTYPE_B_NTYPE,

/* 239 357 EF [Ô] */

	CTYPE_B_NTYPE,

/* 240 360 F0 [] */

	CTYPE_B_NTYPE,

/* 241 361 F1 [Ò] */

	CTYPE_B_NTYPE,

/* 242 362 F2 [Ú] */

	CTYPE_B_NTYPE,

/* 243 363 F3 [Û] */

	CTYPE_B_NTYPE,

/* 244 364 F4 [Ù] */

	CTYPE_B_NTYPE,

/* 245 365 F5 [ı] */

	CTYPE_B_NTYPE,

/* 246 366 F6 [ˆ] */

	CTYPE_B_NTYPE,

/* 247 367 F7 [˜] */

	CTYPE_B_NTYPE,

/* 248 370 F8 [¯] */

	CTYPE_B_NTYPE,

/* 249 371 F9 [˘] */

	CTYPE_B_NTYPE,

/* 250 372 FA [˙] */

	CTYPE_B_NTYPE,

/* 251 373 FB [˚] */

	CTYPE_B_NTYPE,

/* 252 374 FC [¸] */

	CTYPE_B_NTYPE,

/* 253 375 FD [˝] */

	CTYPE_B_NTYPE,

/* 254 376 FE [˛] */

	CTYPE_B_NTYPE,

/* 255 377 FF [ˇ] */

	CTYPE_B_NTYPE
};


/*====================================================================*
 *
 *   bool isascii (signed c);
 *
 *
 *--------------------------------------------------------------------*/

bool octype::isascii (signed c) 

{
	return (c < 0x80);
}


/*====================================================================*
 *
 *   bool iscntrl (signed c);
 *
 *
 *--------------------------------------------------------------------*/

bool octype::iscntrl (signed c) 

{
	return ((octype::mtable [c & UCHAR_MAX] & (CTYPE_B_CNTRL)) != 0);
}


/*====================================================================*
 *
 *   bool isupper (signed c); 
 *
 *
 *--------------------------------------------------------------------*/

bool octype::isupper (signed c) 

{
	return (octype::mtable [c & UCHAR_MAX] & CTYPE_B_UPPER);
}


/*====================================================================*
 *
 *   bool islower (signed c);
 *
 *--------------------------------------------------------------------*/

bool octype::islower (signed c) 

{
	return (octype::mtable [c & UCHAR_MAX] & CTYPE_B_LOWER);
}


/*====================================================================*
 *
 *   bool isalpha (signed c);
 *
 *--------------------------------------------------------------------*/

bool octype::isalpha (signed c) 

{
	return (octype::mtable [c & UCHAR_MAX] & (CTYPE_B_LOWER | CTYPE_B_UPPER));
}


/*====================================================================*
 *
 *   bool isdigit (signed c);
 *
 *--------------------------------------------------------------------*/

bool octype::isdigit (signed c) 

{
	return (octype::mtable [c & UCHAR_MAX] & CTYPE_B_DIGIT);
}


/*====================================================================*
 *
 *   bool isxdigit (signed c);
 *
 *--------------------------------------------------------------------*/

bool octype::isxdigit (signed c) 

{
	return (octype::mtable [c & UCHAR_MAX] & CTYPE_B_HEX);
}


/*====================================================================*
 *
 *   bool isalnum (signed c);
 *
 *--------------------------------------------------------------------*/

bool octype::isalnum (signed c) 

{
	return (octype::mtable [c & UCHAR_MAX] & (CTYPE_B_UPPER | CTYPE_B_LOWER | CTYPE_B_DIGIT));
}


/*====================================================================*
 *
 *   bool isspace (signed c);
 *
 *--------------------------------------------------------------------*/

bool octype::isspace (signed c) 

{
	return (octype::mtable [c & UCHAR_MAX] & CTYPE_B_SPACE);
}


/*====================================================================*
 *
 *   bool ispunct (signed c);
 *
 *--------------------------------------------------------------------*/

bool octype::ispunct (signed c) 

{
	return (octype::mtable [c & UCHAR_MAX] & CTYPE_B_PUNCT);
}


/*====================================================================*
 *
 *   bool isgraph (signed c);
 *
 *--------------------------------------------------------------------*/

bool octype::isgraph (signed c) 

{
	return (octype::mtable [c & UCHAR_MAX] & (CTYPE_B_UPPER | CTYPE_B_LOWER | CTYPE_B_DIGIT | CTYPE_B_PUNCT));
}


/*====================================================================*
 *
 *   bool isprint (signed c);
 *
 *--------------------------------------------------------------------*/

bool octype::isprint (signed c) 

{
	return ((octype::mtable [c & UCHAR_MAX] & (CTYPE_B_CNTRL)) == 0);
}


/*====================================================================*
 *
 *   bool isident (signed c);
 *
 *--------------------------------------------------------------------*/

bool octype::isident (signed c) 

{
	return (octype::mtable [c & UCHAR_MAX] & CTYPE_B_IDENT);
}


/*====================================================================*
 *
 *   bool nmtoken (signed c);
 *
 *--------------------------------------------------------------------*/

bool octype::nmtoken (signed c) 

{
	return (octype::isalnum (c) || (c == '_') || (c == '-') || (c == '.') || (c == ':'));
}


/*====================================================================*
 *
 *   bool isquote (signed c);
 *
 *--------------------------------------------------------------------*/

bool octype::isquote (signed c) 

{
	return ((c == '\'') || (c == '\"'));
}


/*====================================================================*
 *
 *   bool isblank (signed c);
 *
 *--------------------------------------------------------------------*/

bool octype::isblank (signed c) 

{
	return ((c == ' ') || (c == '\t'));
}


/*====================================================================*
 *
 *   bool isbreak (signed c);
 *
 *--------------------------------------------------------------------*/

bool octype::isbreak (signed c) 

{
	return ((c == '\0') || (c == '\n') || (c == EOF));
}


/*====================================================================*
 *
 *   bool nobreak (signed c);
 *
 *--------------------------------------------------------------------*/

bool octype::nobreak (signed c) 

{
	return ((c != '\0') && (c != '\n') && (c != EOF));
}


/*====================================================================*
 *
 *   bool toupper (signed c);
 *
 *--------------------------------------------------------------------*/

signed octype::toupper (signed c) 

{
	if (octype::islower (c)) 
	{
		return (c - ('a' - 'A'));
	}
	return (c);
}


/*====================================================================*
 *
 *   bool tolower (signed c);
 *
 *--------------------------------------------------------------------*/

signed octype::tolower (signed c) 

{
	if (octype::isupper (c)) 
	{
		return (c + ('a' - 'A'));
	}
	return (c);
}


/*====================================================================*
 *
 *   bool toascii (signed c);
 *
 *--------------------------------------------------------------------*/

signed octype::toascii (signed c) 

{
	return (c & 0x007F);
}


/*====================================================================*
 *
 *   bool tocntrl (signed c);
 *
 *--------------------------------------------------------------------*/

signed octype::tocntrl (signed c) 

{
	return (c & 0x001F);
}


/*====================================================================*
 *
 *   signed todigit (signed c);
 *
 *--------------------------------------------------------------------*/

signed octype::todigit (signed c) 

{
	if ((c >= '0') && (c <= '9')) 
	{
		return (c - '0');
	}
	if ((c >= 'A') && (c <= 'Z')) 
	{
		return (c - 'A' + 10);
	}
	if ((c >= 'a') && (c <= 'z')) 
	{
		return (c - 'a' + 10);
	}
	return (-1);
}


/*====================================================================*
 *
 *   octype();
 *
 *--------------------------------------------------------------------*/

octype::octype () 

{
	return;
}


/*====================================================================*
 *
 *   ~octype();
 *
 *--------------------------------------------------------------------*/

octype::~octype () 

{
	return;
}


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

