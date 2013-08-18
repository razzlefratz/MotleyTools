/*====================================================================*
 *
 *   oascii.cpp - oascii class definition;
 *
 *   character classification and conversion; this is a customized
 *   and customizable implementation of the standard ctype macros
 *   and library functions;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oASCII_SOURCE
#define oASCII_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstdio>
#include <climits>
#include <cstring>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oascii.hpp"

/*====================================================================*
 *   private constants;
 *--------------------------------------------------------------------*/

#define oASCII_NTYPE (0) 
#define oASCII_CNTRL (1 << 0) 
#define oASCII_SPACE (1 << 1) 
#define oASCII_UPPER (1 << 2) 
#define oASCII_LOWER (1 << 3) 
#define oASCII_DIGIT (1 << 4) 
#define oASCII_XDIGIT (1 << 5) 
#define oASCII_PUNCT (1 << 6) 
#define oASCII_QUOTE (1 << 7) 
#define oASCII_UNARY (1 << 8) 
#define oASCII_ARITH (1 << 9) 
#define oASCII_LOGIC (1 << 10) 
#define oASCII_EQUAL (1 << 11) 
#define oASCII_COMMA (1 << 12) 
#define oASCII_BLOCK (1 << 13) 
#define oASCII_IDENT (1 << 14) 
#define oASCII_TOKEN (1 << 15) 
#define oASCII_BEGIN (1 << 16) 
#define oASCII_CLOSE (1 << 17) 
#define oASCII_MONEY (1 << 18) 
#define oASCII_POWER (1 << 19) 
#define oASCII_FRACT (1 << 20) 

/*====================================================================*
 *   private variables;
 *--------------------------------------------------------------------*/

char const * oascii::cbits [] = 

{ 
	"cntrl", 
	"space", 
	"upper", 
	"lower", 
	"digit", 
	"xdigit", 
	"punct", 
	"quote", 
	"unary", 
	"arith", 
	"logic", 
	"equal", 
	"comma", 
	"block",
	"ident", 
	"token", 
	"begin", 
	"close", 
	"money", 
	"power", 
	"fract"
}; 

const unsigned oascii::ctype [UCHAR_MAX + 1] = 

{ 

/* 000 000 00 NUL */

	oASCII_CNTRL, 

/* 001 001 01 SOH */

	oASCII_CNTRL, 

/* 002 002 02 STX */

	oASCII_CNTRL, 

/* 003 003 03 ETX */

	oASCII_CNTRL, 

/* 004 004 04 EOT */

	oASCII_CNTRL, 

/* 005 005 05 ENQ */

	oASCII_CNTRL, 

/* 006 006 06 ACK */

	oASCII_CNTRL, 

/* 007 007 07 BEL */

	oASCII_CNTRL, 

/* 008 010 08 BS  */

	oASCII_CNTRL, 

/* 009 011 09 HT  */

	oASCII_CNTRL | oASCII_SPACE, 

/* 010 012 0A LF  */

	oASCII_CNTRL | oASCII_SPACE, 

/* 011 013 0B VT  */

	oASCII_CNTRL | oASCII_SPACE, 

/* 012 014 0C FF  */

	oASCII_CNTRL | oASCII_SPACE, 

/* 013 015 0D CR  */

	oASCII_CNTRL | oASCII_SPACE, 

/* 014 016 0E SO  */

	oASCII_CNTRL, 

/* 015 017 0F SI  */

	oASCII_CNTRL, 

/* 016 020 10 DLE */

	oASCII_CNTRL, 

/* 017 021 11 DC1 */

	oASCII_CNTRL, 

/* 018 022 12 DC2 */

	oASCII_CNTRL, 

/* 019 023 13 DC3 */

	oASCII_CNTRL, 

/* 020 024 14 DC4 */

	oASCII_CNTRL, 

/* 021 025 15 NAK */

	oASCII_CNTRL, 

/* 022 026 16 SYN */

	oASCII_CNTRL, 

/* 023 027 17 ETB */

	oASCII_CNTRL, 

/* 024 030 18 CAN */

	oASCII_CNTRL, 

/* 025 031 19 EM  */

	oASCII_CNTRL, 

/* 026 032 1A SUB */

	oASCII_CNTRL, 

/* 027 033 1B ESC */

	oASCII_CNTRL, 

/* 028 034 1C FS  */

	oASCII_CNTRL, 

/* 029 035 1D GS  */

	oASCII_CNTRL, 

/* 030 036 1E RS  */

	oASCII_CNTRL, 

/* 031 037 1F US  */

	oASCII_CNTRL, 

/* 032 040 20 [ ] */

	oASCII_SPACE, 

/* 033 041 21 [!] */

	oASCII_PUNCT | oASCII_UNARY | oASCII_EQUAL, 

/* 034 042 22 ["] */

	oASCII_PUNCT | oASCII_QUOTE, 

/* 035 043 23 [#] */

	oASCII_PUNCT | oASCII_BLOCK, 

/* 036 044 24 [$] */

	oASCII_PUNCT | oASCII_IDENT | oASCII_MONEY, 

/* 037 045 25 [%] */

	oASCII_PUNCT | oASCII_ARITH, 

/* 038 046 26 [&] */

	oASCII_PUNCT | oASCII_UNARY | oASCII_LOGIC, 

/* 039 047 27 ['] */

	oASCII_PUNCT | oASCII_QUOTE, 

/* 040 050 28 [(] */

	oASCII_PUNCT | oASCII_BEGIN, 

/* 041 051 29 [)] */

	oASCII_PUNCT | oASCII_CLOSE, 

/* 042 052 2A [*] */

	oASCII_PUNCT | oASCII_UNARY | oASCII_ARITH, 

/* 043 053 2B [+] */

	oASCII_PUNCT | oASCII_UNARY | oASCII_ARITH, 

/* 044 054 2C [,] */

	oASCII_PUNCT | oASCII_COMMA | oASCII_BLOCK, 

/* 045 055 2D [-] */

	oASCII_PUNCT | oASCII_UNARY | oASCII_ARITH | oASCII_TOKEN, 

/* 046 056 2E [.] */

	oASCII_PUNCT | oASCII_TOKEN, 

/* 047 057 2F [/] */

	oASCII_PUNCT | oASCII_ARITH, 

/* 048 060 30 [0] */

	oASCII_DIGIT | oASCII_TOKEN | oASCII_IDENT | oASCII_XDIGIT, 

/* 049 061 31 [1] */

	oASCII_DIGIT | oASCII_TOKEN | oASCII_IDENT | oASCII_XDIGIT, 

/* 050 062 32 [2] */

	oASCII_DIGIT | oASCII_TOKEN | oASCII_IDENT | oASCII_XDIGIT, 

/* 051 063 33 [3] */

	oASCII_DIGIT | oASCII_TOKEN | oASCII_IDENT | oASCII_XDIGIT, 

/* 052 064 34 [4] */

	oASCII_DIGIT | oASCII_TOKEN | oASCII_IDENT | oASCII_XDIGIT, 

/* 053 065 35 [5] */

	oASCII_DIGIT | oASCII_TOKEN | oASCII_IDENT | oASCII_XDIGIT, 

/* 054 066 36 [6] */

	oASCII_DIGIT | oASCII_TOKEN | oASCII_IDENT | oASCII_XDIGIT, 

/* 055 067 37 [7] */

	oASCII_DIGIT | oASCII_TOKEN | oASCII_IDENT | oASCII_XDIGIT, 

/* 056 070 38 [8] */

	oASCII_DIGIT | oASCII_TOKEN | oASCII_IDENT | oASCII_XDIGIT, 

/* 057 071 39 [9] */

	oASCII_DIGIT | oASCII_TOKEN | oASCII_IDENT | oASCII_XDIGIT, 

/* 058 072 3A [:] */

	oASCII_PUNCT | oASCII_TOKEN | oASCII_COMMA, 

/* 059 073 3B [;] */

	oASCII_PUNCT | oASCII_COMMA | oASCII_BLOCK, 

/* 060 074 3C [<] */

	oASCII_PUNCT | oASCII_EQUAL, 

/* 061 075 3D [=] */

	oASCII_PUNCT | oASCII_EQUAL, 

/* 062 076 3E [>] */

	oASCII_PUNCT | oASCII_EQUAL, 

/* 063 077 3F [?] */

	oASCII_PUNCT | oASCII_COMMA, 

/* 064 100 40 [@] */

	oASCII_PUNCT, 

/* 065 101 41 [A] */

	oASCII_UPPER | oASCII_TOKEN | oASCII_IDENT | oASCII_XDIGIT, 

/* 066 102 42 [B] */

	oASCII_UPPER | oASCII_TOKEN | oASCII_IDENT | oASCII_XDIGIT, 

/* 067 103 43 [C] */

	oASCII_UPPER | oASCII_TOKEN | oASCII_IDENT | oASCII_XDIGIT, 

/* 068 104 44 [D] */

	oASCII_UPPER | oASCII_TOKEN | oASCII_IDENT | oASCII_XDIGIT, 

/* 069 105 45 [E] */

	oASCII_UPPER | oASCII_TOKEN | oASCII_IDENT | oASCII_XDIGIT, 

/* 070 106 46 [F] */

	oASCII_UPPER | oASCII_TOKEN | oASCII_IDENT | oASCII_XDIGIT, 

/* 071 107 47 [G] */

	oASCII_UPPER | oASCII_TOKEN | oASCII_IDENT, 

/* 072 110 48 [H] */

	oASCII_UPPER | oASCII_TOKEN | oASCII_IDENT, 

/* 073 111 49 [I] */

	oASCII_UPPER | oASCII_TOKEN | oASCII_IDENT, 

/* 074 112 4A [J] */

	oASCII_UPPER | oASCII_TOKEN | oASCII_IDENT, 

/* 075 113 4B [K] */

	oASCII_UPPER | oASCII_TOKEN | oASCII_IDENT, 

/* 076 114 4C [L] */

	oASCII_UPPER | oASCII_TOKEN | oASCII_IDENT, 

/* 077 115 4D [M] */

	oASCII_UPPER | oASCII_TOKEN | oASCII_IDENT, 

/* 078 116 4E [N] */

	oASCII_UPPER | oASCII_TOKEN | oASCII_IDENT, 

/* 079 117 4F [O] */

	oASCII_UPPER | oASCII_TOKEN | oASCII_IDENT, 

/* 080 120 50 [P] */

	oASCII_UPPER | oASCII_TOKEN | oASCII_IDENT, 

/* 081 121 51 [Q] */

	oASCII_UPPER | oASCII_TOKEN | oASCII_IDENT, 

/* 082 122 52 [R] */

	oASCII_UPPER | oASCII_TOKEN | oASCII_IDENT, 

/* 083 123 53 [S] */

	oASCII_UPPER | oASCII_TOKEN | oASCII_IDENT, 

/* 084 124 54 [T] */

	oASCII_UPPER | oASCII_TOKEN | oASCII_IDENT, 

/* 085 125 55 [U] */

	oASCII_UPPER | oASCII_TOKEN | oASCII_IDENT, 

/* 086 126 56 [V] */

	oASCII_UPPER | oASCII_TOKEN | oASCII_IDENT, 

/* 087 127 57 [W] */

	oASCII_UPPER | oASCII_TOKEN | oASCII_IDENT, 

/* 088 130 58 [X] */

	oASCII_UPPER | oASCII_TOKEN | oASCII_IDENT, 

/* 089 131 59 [Y] */

	oASCII_UPPER | oASCII_TOKEN | oASCII_IDENT, 

/* 090 132 5A [Z] */

	oASCII_UPPER | oASCII_TOKEN | oASCII_IDENT, 

/* 091 133 5B [[] */

	oASCII_PUNCT | oASCII_BEGIN, 

/* 092 134 5C [\] */

	oASCII_PUNCT, 

/* 093 135 5D []] */

	oASCII_PUNCT | oASCII_CLOSE, 

/* 094 136 5E [^] */

	oASCII_PUNCT | oASCII_LOGIC, 

/* 095 137 5F [_] */

	oASCII_PUNCT | oASCII_TOKEN | oASCII_IDENT, 

/* 096 140 60 [`] */

	oASCII_PUNCT, 

/* 097 141 61 [a] */

	oASCII_LOWER | oASCII_TOKEN | oASCII_IDENT | oASCII_XDIGIT, 

/* 098 142 62 [b] */

	oASCII_LOWER | oASCII_TOKEN | oASCII_IDENT | oASCII_XDIGIT, 

/* 099 143 63 [c] */

	oASCII_LOWER | oASCII_TOKEN | oASCII_IDENT | oASCII_XDIGIT, 

/* 100 144 64 [d] */

	oASCII_LOWER | oASCII_TOKEN | oASCII_IDENT | oASCII_XDIGIT, 

/* 101 145 65 [e] */

	oASCII_LOWER | oASCII_TOKEN | oASCII_IDENT | oASCII_XDIGIT, 

/* 102 146 66 [f] */

	oASCII_LOWER | oASCII_TOKEN | oASCII_IDENT | oASCII_XDIGIT, 

/* 103 147 67 [g] */

	oASCII_LOWER | oASCII_TOKEN | oASCII_IDENT, 

/* 104 150 68 [h] */

	oASCII_LOWER | oASCII_TOKEN | oASCII_IDENT, 

/* 105 151 69 [i] */

	oASCII_LOWER | oASCII_TOKEN | oASCII_IDENT, 

/* 106 152 6A [j] */

	oASCII_LOWER | oASCII_TOKEN | oASCII_IDENT, 

/* 107 153 6B [k] */

	oASCII_LOWER | oASCII_TOKEN | oASCII_IDENT, 

/* 108 154 6C [l] */

	oASCII_LOWER | oASCII_TOKEN | oASCII_IDENT, 

/* 109 155 6D [m] */

	oASCII_LOWER | oASCII_TOKEN | oASCII_IDENT, 

/* 110 156 6E [n] */

	oASCII_LOWER | oASCII_TOKEN | oASCII_IDENT, 

/* 111 157 6F [o] */

	oASCII_LOWER | oASCII_TOKEN | oASCII_IDENT, 

/* 112 160 70 [p] */

	oASCII_LOWER | oASCII_TOKEN | oASCII_IDENT, 

/* 113 161 71 [q] */

	oASCII_LOWER | oASCII_TOKEN | oASCII_IDENT, 

/* 114 162 72 [r] */

	oASCII_LOWER | oASCII_TOKEN | oASCII_IDENT, 

/* 115 163 73 [s] */

	oASCII_LOWER | oASCII_TOKEN | oASCII_IDENT, 

/* 116 164 74 [t] */

	oASCII_LOWER | oASCII_TOKEN | oASCII_IDENT, 

/* 117 165 75 [u] */

	oASCII_LOWER | oASCII_TOKEN | oASCII_IDENT, 

/* 118 166 76 [v] */

	oASCII_LOWER | oASCII_TOKEN | oASCII_IDENT, 

/* 119 167 77 [w] */

	oASCII_LOWER | oASCII_TOKEN | oASCII_IDENT, 

/* 120 170 78 [x] */

	oASCII_LOWER | oASCII_TOKEN | oASCII_IDENT, 

/* 121 171 79 [y] */

	oASCII_LOWER | oASCII_TOKEN | oASCII_IDENT, 

/* 122 172 7A [z] */

	oASCII_LOWER | oASCII_TOKEN | oASCII_IDENT, 

/* 123 173 7B [{] */

	oASCII_PUNCT | oASCII_BEGIN | oASCII_BLOCK, 

/* 124 174 7C [|] */

	oASCII_PUNCT | oASCII_LOGIC, 

/* 125 175 7D [}] */

	oASCII_PUNCT | oASCII_CLOSE | oASCII_BLOCK, 

/* 126 176 7E [~] */

	oASCII_PUNCT | oASCII_UNARY | oASCII_LOGIC, 

/* 127 177 7F DEL */

	oASCII_CNTRL, 

/* 128 200 80 [Ä] */

	oASCII_NTYPE, 

/* 129 201 81 [Å] */

	oASCII_NTYPE, 

/* 130 202 82 [Ç] */

	oASCII_NTYPE, 

/* 131 203 83 [É] */

	oASCII_NTYPE, 

/* 132 204 84 [Ñ] */

	oASCII_NTYPE, 

/* 133 205 85 [Ö] */

	oASCII_NTYPE, 

/* 134 206 86 [Ü] */

	oASCII_NTYPE, 

/* 135 207 87 [á] */

	oASCII_NTYPE, 

/* 136 210 88 [à] */

	oASCII_NTYPE, 

/* 137 211 89 [â] */

	oASCII_NTYPE, 

/* 138 212 8A [ä] */

	oASCII_NTYPE, 

/* 139 213 8B [ã] */

	oASCII_NTYPE, 

/* 140 214 8C [å] */

	oASCII_NTYPE, 

/* 141 215 8D [ç] */

	oASCII_NTYPE, 

/* 142 216 8E [é] */

	oASCII_NTYPE, 

/* 143 217 8F [è] */

	oASCII_NTYPE, 

/* 144 220 90 [ê] */

	oASCII_NTYPE, 

/* 145 221 91 [ë] */

	oASCII_NTYPE, 

/* 146 222 92 [í] */

	oASCII_NTYPE, 

/* 147 223 93 [ì] */

	oASCII_NTYPE, 

/* 148 224 94 [î] */

	oASCII_NTYPE, 

/* 149 225 95 [ï] */

	oASCII_NTYPE, 

/* 150 226 96 [ñ] */

	oASCII_NTYPE, 

/* 151 227 97 [ó] */

	oASCII_NTYPE, 

/* 152 230 98 [ò] */

	oASCII_NTYPE, 

/* 153 231 99 [ô] */

	oASCII_NTYPE, 

/* 154 232 9A [ö] */

	oASCII_NTYPE, 

/* 155 233 9B [õ] */

	oASCII_NTYPE, 

/* 156 234 9C [ú] */

	oASCII_NTYPE, 

/* 157 235 9D [ù] */

	oASCII_NTYPE, 

/* 158 236 9E [û] */

	oASCII_NTYPE, 

/* 159 237 9F [ü] */

	oASCII_NTYPE, 

/* 160 240 A0 [†] */

	oASCII_SPACE, 

/* 161 241 A1 [°] */

	oASCII_PUNCT, 

/* 162 242 A2 [¢] */

	oASCII_MONEY, 

/* 163 243 A3 [£] */

	oASCII_MONEY, 

/* 164 244 A4 [§] */

	oASCII_MONEY, 

/* 165 245 A5 [•] */

	oASCII_MONEY, 

/* 166 246 A6 [¶] */

	oASCII_PUNCT, 

/* 167 247 A7 [ß] */

	oASCII_PUNCT, 

/* 168 250 A8 [®] */

	oASCII_PUNCT, 

/* 169 251 A9 [©] */

	oASCII_PUNCT, 

/* 170 252 AA [™] */

	oASCII_PUNCT, 

/* 171 253 AB [´] */

	oASCII_PUNCT, 

/* 172 254 AC [¨] */

	oASCII_PUNCT, 

/* 173 255 AD [≠] */

	oASCII_PUNCT, 

/* 174 256 AE [Æ] */

	oASCII_PUNCT, 

/* 175 257 AF [Ø] */

	oASCII_PUNCT, 

/* 176 260 B0 [∞] */

	oASCII_PUNCT, 

/* 177 261 B1 [±] */

	oASCII_PUNCT, 

/* 178 262 B2 [≤] */

	oASCII_POWER, 

/* 179 263 B3 [≥] */

	oASCII_POWER, 

/* 180 264 B4 [¥] */

	oASCII_PUNCT, 

/* 181 265 B5 [µ] */

	oASCII_LOWER, 

/* 182 266 B6 [∂] */

	oASCII_PUNCT, 

/* 183 267 B7 [∑] */

	oASCII_PUNCT, 

/* 184 270 B8 [∏] */

	oASCII_PUNCT, 

/* 185 271 B9 [π] */

	oASCII_POWER, 

/* 186 272 BA [∫] */

	oASCII_PUNCT, 

/* 187 273 BB [ª] */

	oASCII_PUNCT, 

/* 188 274 BC [º] */

	oASCII_FRACT, 

/* 189 275 BD [Ω] */

	oASCII_FRACT, 

/* 190 276 BE [æ] */

	oASCII_FRACT, 

/* 191 277 BF [ø] */

	oASCII_PUNCT, 

/* 192 300 C0 [¿] */

	oASCII_UPPER, 

/* 193 301 C1 [¡] */

	oASCII_UPPER, 

/* 194 302 C2 [¬] */

	oASCII_UPPER, 

/* 195 303 C3 [√] */

	oASCII_UPPER, 

/* 196 304 C4 [ƒ] */

	oASCII_UPPER, 

/* 197 305 C5 [≈] */

	oASCII_UPPER, 

/* 198 306 C6 [∆] */

	oASCII_UPPER, 

/* 199 307 C7 [«] */

	oASCII_UPPER, 

/* 200 310 C8 [»] */

	oASCII_UPPER, 

/* 201 311 C9 […] */

	oASCII_UPPER, 

/* 202 312 CA [ ] */

	oASCII_UPPER, 

/* 203 313 CB [À] */

	oASCII_UPPER, 

/* 204 314 CC [Ã] */

	oASCII_UPPER, 

/* 205 315 CD [Õ] */

	oASCII_UPPER, 

/* 206 316 CE [Œ] */

	oASCII_UPPER, 

/* 207 317 CF [œ] */

	oASCII_UPPER, 

/* 208 320 D0 [–] */

	oASCII_UPPER, 

/* 209 321 D1 [—] */

	oASCII_UPPER, 

/* 210 322 D2 [“] */

	oASCII_UPPER, 

/* 211 323 D3 [”] */

	oASCII_UPPER, 

/* 212 324 D4 [‘] */

	oASCII_UPPER, 

/* 213 325 D5 [’] */

	oASCII_UPPER, 

/* 214 326 D6 [÷] */

	oASCII_UPPER, 

/* 215 327 D7 [◊] */

	oASCII_ARITH, 

/* 216 330 D8 [ÿ] */

	oASCII_UPPER, 

/* 217 331 D9 [Ÿ] */

	oASCII_UPPER, 

/* 218 332 DA [⁄] */

	oASCII_UPPER, 

/* 219 333 DB [€] */

	oASCII_UPPER, 

/* 220 334 DC [‹] */

	oASCII_UPPER, 

/* 221 335 DD [›] */

	oASCII_UPPER, 

/* 222 336 DE [ﬁ] */

	oASCII_LOWER, 

/* 223 337 DF [ﬂ] */

	oASCII_LOWER, 

/* 224 340 E0 [‡] */

	oASCII_LOWER, 

/* 225 341 E1 [·] */

	oASCII_LOWER, 

/* 226 342 E2 [‚] */

	oASCII_LOWER, 

/* 227 343 E3 [„] */

	oASCII_LOWER, 

/* 228 344 E4 [‰] */

	oASCII_LOWER, 

/* 229 345 E5 [Â] */

	oASCII_LOWER, 

/* 230 346 E6 [Ê] */

	oASCII_LOWER, 

/* 231 347 E7 [Á] */

	oASCII_LOWER, 

/* 232 350 E8 [Ë] */

	oASCII_LOWER, 

/* 233 351 E9 [È] */

	oASCII_LOWER, 

/* 234 352 EA [Í] */

	oASCII_LOWER, 

/* 235 353 EB [Î] */

	oASCII_LOWER, 

/* 236 354 EC [Ï] */

	oASCII_LOWER, 

/* 237 355 ED [Ì] */

	oASCII_LOWER, 

/* 238 356 EE [Ó] */

	oASCII_LOWER, 

/* 239 357 EF [Ô] */

	oASCII_LOWER, 

/* 240 360 F0 [] */

	oASCII_LOWER, 

/* 241 361 F1 [Ò] */

	oASCII_LOWER, 

/* 242 362 F2 [Ú] */

	oASCII_LOWER, 

/* 243 363 F3 [Û] */

	oASCII_LOWER, 

/* 244 364 F4 [Ù] */

	oASCII_LOWER, 

/* 245 365 F5 [ı] */

	oASCII_LOWER, 

/* 246 366 F6 [ˆ] */

	oASCII_LOWER, 

/* 247 367 F7 [˜] */

	oASCII_ARITH, 

/* 248 370 F8 [¯] */

	oASCII_LOWER, 

/* 249 371 F9 [˘] */

	oASCII_LOWER, 

/* 250 372 FA [˙] */

	oASCII_LOWER, 

/* 251 373 FB [˚] */

	oASCII_LOWER, 

/* 252 374 FC [¸] */

	oASCII_LOWER, 

/* 253 375 FD [˝] */

	oASCII_LOWER, 

/* 254 376 FE [˛] */

	oASCII_LOWER, 

/* 255 377 FF [ˇ] */

	oASCII_LOWER, 
}; 

/*====================================================================*
 *
 *   unsigned ctypemask (char const * ctypename) const;
 *
 *--------------------------------------------------------------------*/

unsigned oascii::ctypemask (char const * ctypename) const 

{ 
	unsigned bit = 0; 
	while (bit < SIZEOF (oascii::cbits)) 
	{ 
		if (!std::strcmp (ctypename, oascii::cbits [bit])) 
		{ 
			return (1 << bit); 
		} 
	} 
	return (0); 
} 

/*====================================================================*
 *
 *   bool isascii (signed c);
 *
 *--------------------------------------------------------------------*/

#ifndef WIN32

bool oascii::isascii (signed c) 

{ 
	return (c < 0x80); 
} 

#endif

/*====================================================================*
 *
 *   bool iscntrl (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::iscntrl (signed c) 

{ 
	return (oascii::isctype (c, (oASCII_CNTRL))); 
} 

/*====================================================================*
 *
 *   bool isupper (signed c); 
 *
 *--------------------------------------------------------------------*/

bool oascii::isupper (signed c) 

{ 
	return (oascii::isctype (c, (oASCII_UPPER))); 
} 

/*====================================================================*
 *
 *   bool islower (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::islower (signed c) 

{ 
	return (oascii::isctype (c, (oASCII_LOWER))); 
} 

/*====================================================================*
 *
 *   bool isalpha (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::isalpha (signed c) 

{ 
	return (oascii::isctype (c, (oASCII_LOWER | oASCII_UPPER))); 
} 

/*====================================================================*
 *
 *   bool isalnum (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::isalnum (signed c) 

{ 
	return (oascii::isctype (c, (oASCII_UPPER | oASCII_LOWER | oASCII_DIGIT))); 
} 

/*====================================================================*
 *
 *   bool isdigit (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::isdigit (signed c) 

{ 
	return (oascii::isctype (c, (oASCII_DIGIT))); 
} 

/*====================================================================*
 *
 *   bool isxdigit (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::isxdigit (signed c) 

{ 
	return (oascii::isctype (c, (oASCII_XDIGIT))); 
} 

/*====================================================================*
 *
 *   bool ispunct (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::ispunct (signed c) 

{ 
	return (oascii::isctype (c, (oASCII_PUNCT))); 
} 

/*====================================================================*
 *
 *   bool isspace (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::isspace (signed c) 

{ 
	return (oascii::isctype (c, (oASCII_SPACE))); 
} 

/*====================================================================*
 *
 *   bool isgraph (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::isgraph (signed c) 

{ 
	return (oascii::isctype (c, (oASCII_UPPER | oASCII_LOWER | oASCII_DIGIT | oASCII_PUNCT))); 
} 

/*====================================================================*
 *
 *   bool isprint (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::isprint (signed c) 

{ 
	return (!oascii::isctype (c, (oASCII_CNTRL))); 
} 

/*====================================================================*
 *
 *   bool isident (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::isident (signed c) 

{ 
	return (oascii::isctype (c, (oASCII_IDENT))); 
} 

/*====================================================================*
 *
 *   bool isquote (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::isquote (signed c) 

{ 
	return (oascii::isctype (c, (oASCII_QUOTE))); 
} 

/*====================================================================*
 *
 *   bool isunary (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::isunary (signed c) 

{ 
	return (oascii::isctype (c, (oASCII_UNARY))); 
} 

/*====================================================================*
 *
 *   bool isarith (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::isarith (signed c) 

{ 
	return (oascii::isctype (c, (oASCII_ARITH))); 
} 

/*====================================================================*
 *
 *   bool isequal (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::isequal (signed c) 

{ 
	return (oascii::isctype (c, (oASCII_EQUAL))); 
} 

/*====================================================================*
 *
 *   bool islogic (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::islogic (signed c) 

{ 
	return (oascii::isctype (c, (oASCII_LOGIC))); 
} 

/*====================================================================*
 *
 *   bool isgroup (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::isgroup (signed c) 

{ 
	return (oascii::isctype (c, (oASCII_BEGIN | oASCII_CLOSE))); 
} 

/*====================================================================*
 *
 *   bool isbegin (signed c);
 *
 *   begin characters start a group like a conditional espression, an
 *   argument list, an array element or a program code block;
 *
 *--------------------------------------------------------------------*/

bool oascii::isbegin (signed c) 

{ 
	return (oascii::isctype (c, (oASCII_BEGIN))); 
} 

/*====================================================================*
 *
 *   bool isclose (signed c);
 *
 *   begin characters end a group like a conditional espression, an
 *   argument list, an array element or a program code block;
 *
 *--------------------------------------------------------------------*/

bool oascii::isclose (signed c) 

{ 
	return (oascii::isctype (c, (oASCII_CLOSE))); 
} 

/*====================================================================*
 *
 *   bool iscomma (signed c);
 *
 *   comma characters separate list items or terminate expressions;
 *
 *--------------------------------------------------------------------*/

bool oascii::iscomma (signed c) 

{ 
	return (oascii::isctype (c, (oASCII_COMMA))); 
} 

/*====================================================================*
 *
 *   bool ismoney (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::ismoney (signed c) 

{ 
	return (oascii::isctype (c, (oASCII_MONEY))); 
} 

/*====================================================================*
 *
 *   bool isfract (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::isfract (signed c) 

{ 
	return (oascii::isctype (c, (oASCII_FRACT))); 
} 

/*====================================================================*
 *
 *   bool ispower (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::ispower (signed c) 

{ 
	return (oascii::isctype (c, (oASCII_POWER))); 
} 

/*====================================================================*
 *
 *   bool nmtoken (signed c);
 *
 *   nmtoken is a w3c standard identifier;
 *
 *--------------------------------------------------------------------*/

bool oascii::nmtoken (signed c) 

{ 
	return (oascii::isctype (c, (oASCII_TOKEN))); 
} 

/*====================================================================*
 *
 *   bool isblock (signed c);
 *
 *   block characters begin or end a C Language code block;
 *
 *--------------------------------------------------------------------*/

bool oascii::isblock (signed c) 

{ 
	return (oascii::isctype (c, (oASCII_BLOCK))); 
} 

/*====================================================================*
 *
 *   bool isblank (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::isblank (signed c) 

{ 
	return ((c == ' ') || (c == '\t')); 
} 

/*====================================================================*
 *
 *   bool ismatch (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::ismatch (signed c, signed o) 

{ 
	return (oascii::toupper (c) == oascii::toupper (o)); 
} 

/*====================================================================*
 *
 *   bool isbreak (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::isbreak (signed c) 

{ 
	return ((c == '\0') || (c == '\n') || (c == - 1)); 
} 

/*====================================================================*
 *
 *   bool isbreak (signed c, signed o);
 *
 *--------------------------------------------------------------------*/

bool oascii::isbreak (signed c, signed o) 

{ 
	return ((c == o) || (c == '\0') || (c == '\n') || (c == - 1)); 
} 

/*====================================================================*
 *
 *   bool nobreak (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::nobreak (signed c) 

{ 
	return ((c != '\0') && (c != '\n') && (c != - 1)); 
} 

/*====================================================================*
 *
 *   bool nobreak (signed c, signed o);
 *
 *--------------------------------------------------------------------*/

bool oascii::nobreak (signed c, signed o) 

{ 
	return ((c != o) && (c != '\0') && (c != '\n') && (c != - 1)); 
} 

/*====================================================================*
 *
 *   bool toascii (signed c);
 *
 *--------------------------------------------------------------------*/

#ifndef WIN32

signed oascii::toascii (signed c) 

{ 
	return (c & 0x007F); 
} 

#endif

/*====================================================================*
 *
 *   bool tocntrl (signed c);
 *
 *--------------------------------------------------------------------*/

signed oascii::tocntrl (signed c) 

{ 
	return (c & 0x001F); 
} 

/*====================================================================*
 *
 *   bool toupper (signed c);
 *
 *--------------------------------------------------------------------*/

signed oascii::toupper (signed c) 

{ 
	if (oascii::islower (c)) 
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

signed oascii::tolower (signed c) 

{ 
	if (oascii::isupper (c)) 
	{ 
		return (c + ('a' - 'A')); 
	} 
	return (c); 
} 

/*====================================================================*
 *
 *   signed todigit (signed c);
 *
 *   convert an SCII character digit to an integer;
 *
 *--------------------------------------------------------------------*/

signed oascii::todigit (signed c) 

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
	return (- 1); 
} 

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

char const * oascii::cname [] = 

{ 
	"nul", 
	"soh", 
	"stx", 
	"etx", 
	"eot", 
	"enq", 
	"ack", 
	"bel", 
	"bs", 
	"ht", 
	"lf", 
	"vt", 
	"ff", 
	"cr", 
	"so", 
	"si", 
	"dle", 
	"dc1", 
	"dc2", 
	"dc3", 
	"dc4", 
	"nak", 
	"syn", 
	"etb", 
	"can", 
	"em", 
	"sub", 
	"esc", 
	"fs", 
	"gs", 
	"rs", 
	"us", 
	"sp", 
	"!", 
	"\"", 
	"#", 
	"$", 
	"%", 
	"&", 
	"\'", 
	"(", 
	")", 
	"*", 
	"+", 
	",", 
	"-", 
	".", 
	"/", 
	"0", 
	"1", 
	"2", 
	"3", 
	"4", 
	"5", 
	"6", 
	"7", 
	"8", 
	"9", 
	":", 
	";", 
	"<", 
	"=", 
	">", 
	"?", 
	"@", 
	"A", 
	"B", 
	"C", 
	"D", 
	"E", 
	"F", 
	"G", 
	"H", 
	"I", 
	"J", 
	"K", 
	"L", 
	"M", 
	"N", 
	"O", 
	"P", 
	"Q", 
	"R", 
	"S", 
	"T", 
	"U", 
	"V", 
	"W", 
	"X", 
	"Y", 
	"Z", 
	"[", 
	"\\", 
	"]", 
	"^", 
	"_", 
	"`", 
	"a", 
	"b", 
	"c", 
	"d", 
	"e", 
	"f", 
	"g", 
	"h", 
	"i", 
	"j", 
	"k", 
	"l", 
	"m", 
	"n", 
	"o", 
	"p", 
	"q", 
	"r", 
	"s", 
	"t", 
	"u", 
	"v", 
	"w", 
	"x", 
	"y", 
	"z", 
	"{", 
	"|", 
	"}", 
	"~", 
	"del", 
	"Ä", 
	"Å", 
	"Ç", 
	"É", 
	"Ñ", 
	"Ö", 
	"Ü", 
	"á", 
	"à", 
	"â", 
	"ä", 
	"ã", 
	"å", 
	"ç", 
	"é", 
	"è", 
	"ê", 
	"ë", 
	"í", 
	"ì", 
	"î", 
	"ï", 
	"ñ", 
	"ó", 
	"ò", 
	"ô", 
	"ö", 
	"õ", 
	"ú", 
	"ù", 
	"û", 
	"ü", 
	"†", 
	"°", 
	"¢", 
	"£", 
	"§", 
	"•", 
	"¶", 
	"ß", 
	"®", 
	"©", 
	"™", 
	"´", 
	"¨", 
	"≠", 
	"Æ", 
	"Ø", 
	"∞", 
	"±", 
	"≤", 
	"≥", 
	"¥", 
	"µ", 
	"∂", 
	"∑", 
	"∏", 
	"π", 
	"∫", 
	"ª", 
	"º", 
	"Ω", 
	"æ", 
	"ø", 
	"¿", 
	"¡", 
	"¬", 
	"√", 
	"ƒ", 
	"≈", 
	"∆", 
	"«", 
	"»", 
	"…", 
	" ", 
	"À", 
	"Ã", 
	"Õ", 
	"Œ", 
	"œ", 
	"–", 
	"—", 
	"“", 
	"”", 
	"‘", 
	"’", 
	"÷", 
	"◊", 
	"ÿ", 
	"Ÿ", 
	"⁄", 
	"€", 
	"‹", 
	"›", 
	"ﬁ", 
	"ﬂ", 
	"‡", 
	"·", 
	"‚", 
	"„", 
	"‰", 
	"Â", 
	"Ê", 
	"Á", 
	"Ë", 
	"È", 
	"Í", 
	"Î", 
	"Ï", 
	"Ì", 
	"Ó", 
	"Ô", 
	"", 
	"Ò", 
	"Ú", 
	"Û", 
	"Ù", 
	"ı", 
	"ˆ", 
	"˜", 
	"¯", 
	"˘", 
	"˙", 
	"˚", 
	"¸", 
	"˝", 
	"˛", 
	"ˇ"
}; 

/*====================================================================*
 *
 *   void enumerate () const;
 *
 *--------------------------------------------------------------------*/

void oascii::enumerate () const 

{ 
	for (unsigned bit = 0; bit < SIZEOF (oascii::cbits); bit++) 
	{ 
		std::cout << oascii::cbits [bit] << " "; 
		for (signed c = 0; c <= SCHAR_MAX; c++) 
		{ 
			if (oascii::ctype [c] & (1 << bit)) 
			{ 
				std::cout << " " << oascii::cname [c]; 
			} 
		} 
		std::cout << std::endl; 
	} 
	std::cout << std::endl; 
	return; 
} 

/*====================================================================*
 *
 *   void matrix () const;
 *
 *   print character classification matrix on stdout where output is
 *   suitable for input to program matrix; wrap characters in quotes
 *   so that program matrix will detect and handle escape sequences; 
 *   replace selected characters with ISO glpyh names for HTML use;
 *
 *--------------------------------------------------------------------*/

void oascii::matrix () const 

{ 
	std::cout << "ascii"; 
	for (unsigned bit = 0; bit < SIZEOF (oascii::cbits); bit++) 
	{ 
		std::cout << " " << oascii::cbits [bit]; 
	} 
	std::cout << ";" << std::endl; 
	for (signed c = 0; c <= SCHAR_MAX; c++) 
	{ 
		if (c == '\\') 
		{ 
			std::cout << "\"\\\\\""; 
		} 
		else if (c == '&') 
		{ 
			std::cout << "\"&amp;\""; 
		} 
		else if (c == '<') 
		{ 
			std::cout << "\"&lt;\""; 
		} 
		else if (c == '>') 
		{ 
			std::cout << "\"&gt;\""; 
		} 
		else if (c == '\'') 
		{ 
			std::cout << "\"&apos;\""; 
		} 
		else if (c == '\"') 
		{ 
			std::cout << "\"&quot;\""; 
		} 
		else 
		{ 
			std::cout << "\"" << oascii::cname [c] << "\""; 
		} 
		for (unsigned bit = 0; bit < SIZEOF (cbits); bit++) 
		{ 
			if (oascii::ctype [c] & (1 << bit)) 
			{ 
				std::cout << " " << oascii::cbits [bit]; 
			} 
		} 
		std::cout << ";" << std::endl; 
	} 
	return; 
} 

/*====================================================================*
 *
 *   bool isctype (signed c, unsigned mask)
 *
 *
 *--------------------------------------------------------------------*/

bool oascii::isctype (signed c, unsigned mask) 

{ 
	return ((oascii::ctype [c & 0x007F] & (mask))); 
} 

/*====================================================================*
 *
 *   oascii();
 *
 *
 *--------------------------------------------------------------------*/

oascii::oascii () 

{ 
	return; 
} 

/*====================================================================*
 *
 *   ~oascii();
 *
 *
 *--------------------------------------------------------------------*/

oascii::~ oascii () 

{ 
	return; 
} 

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif


