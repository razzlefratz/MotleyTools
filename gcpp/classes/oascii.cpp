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
#define oASCII_HEX   (1 << 5) 
#define oASCII_PUNCT (1 << 6) 
#define oASCII_QUOTE (1 << 7) 
#define oASCII_ARITH (1 << 8) 
#define oASCII_LOGIC (1 << 9) 
#define oASCII_EQUAL (1 << 10) 
#define oASCII_COMMA (1 << 11) 
#define oASCII_TOKEN (1 << 12) 
#define oASCII_IDENT (1 << 13) 
#define oASCII_BEGIN (1 << 14) 
#define oASCII_CLOSE (1 << 15) 

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

char const * oascii::mbits [] = 

{ 
	"cntrl", 
	"space", 
	"upper", 
	"lower", 
	"digit", 
	"hex", 
	"punct", 
	"quote", 
	"arith", 
	"logic", 
	"equal", 
	"comma", 
	"token", 
	"ident", 
	"begin", 
	"close"
}; 

const unsigned short oascii::cmask [] = 

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

	oASCII_PUNCT | oASCII_EQUAL, 

/* 034 042 22 ["] */

	oASCII_PUNCT | oASCII_QUOTE, 

/* 035 043 23 [#] */

	oASCII_PUNCT, 

/* 036 044 24 [$] */

	oASCII_PUNCT | oASCII_IDENT, 

/* 037 045 25 [%] */

	oASCII_PUNCT | oASCII_ARITH, 

/* 038 046 26 [&] */

	oASCII_PUNCT | oASCII_LOGIC, 

/* 039 047 27 ['] */

	oASCII_PUNCT | oASCII_QUOTE, 

/* 040 050 28 [(] */

	oASCII_PUNCT | oASCII_BEGIN, 

/* 041 051 29 [)] */

	oASCII_PUNCT | oASCII_CLOSE, 

/* 042 052 2A [*] */

	oASCII_PUNCT | oASCII_ARITH, 

/* 043 053 2B [+] */

	oASCII_PUNCT | oASCII_ARITH, 

/* 044 054 2C [,] */

	oASCII_PUNCT | oASCII_COMMA, 

/* 045 055 2D [-] */

	oASCII_PUNCT | oASCII_ARITH | oASCII_TOKEN, 

/* 046 056 2E [.] */

	oASCII_PUNCT | oASCII_TOKEN, 

/* 047 057 2F [/] */

	oASCII_PUNCT | oASCII_ARITH, 

/* 048 060 30 [0] */

	oASCII_DIGIT | oASCII_TOKEN | oASCII_IDENT | oASCII_HEX, 

/* 049 061 31 [1] */

	oASCII_DIGIT | oASCII_TOKEN | oASCII_IDENT | oASCII_HEX, 

/* 050 062 32 [2] */

	oASCII_DIGIT | oASCII_TOKEN | oASCII_IDENT | oASCII_HEX, 

/* 051 063 33 [3] */

	oASCII_DIGIT | oASCII_TOKEN | oASCII_IDENT | oASCII_HEX, 

/* 052 064 34 [4] */

	oASCII_DIGIT | oASCII_TOKEN | oASCII_IDENT | oASCII_HEX, 

/* 053 065 35 [5] */

	oASCII_DIGIT | oASCII_TOKEN | oASCII_IDENT | oASCII_HEX, 

/* 054 066 36 [6] */

	oASCII_DIGIT | oASCII_TOKEN | oASCII_IDENT | oASCII_HEX, 

/* 055 067 37 [7] */

	oASCII_DIGIT | oASCII_TOKEN | oASCII_IDENT | oASCII_HEX, 

/* 056 070 38 [8] */

	oASCII_DIGIT | oASCII_TOKEN | oASCII_IDENT | oASCII_HEX, 

/* 057 071 39 [9] */

	oASCII_DIGIT | oASCII_TOKEN | oASCII_IDENT | oASCII_HEX, 

/* 058 072 3A [:] */

	oASCII_PUNCT | oASCII_TOKEN | oASCII_COMMA, 

/* 059 073 3B [;] */

	oASCII_PUNCT | oASCII_COMMA, 

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

	oASCII_UPPER | oASCII_TOKEN | oASCII_IDENT | oASCII_HEX, 

/* 066 102 42 [B] */

	oASCII_UPPER | oASCII_TOKEN | oASCII_IDENT | oASCII_HEX, 

/* 067 103 43 [C] */

	oASCII_UPPER | oASCII_TOKEN | oASCII_IDENT | oASCII_HEX, 

/* 068 104 44 [D] */

	oASCII_UPPER | oASCII_TOKEN | oASCII_IDENT | oASCII_HEX, 

/* 069 105 45 [E] */

	oASCII_UPPER | oASCII_TOKEN | oASCII_IDENT | oASCII_HEX, 

/* 070 106 46 [F] */

	oASCII_UPPER | oASCII_TOKEN | oASCII_IDENT | oASCII_HEX, 

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

	oASCII_LOWER | oASCII_TOKEN | oASCII_IDENT | oASCII_HEX, 

/* 098 142 62 [b] */

	oASCII_LOWER | oASCII_TOKEN | oASCII_IDENT | oASCII_HEX, 

/* 099 143 63 [c] */

	oASCII_LOWER | oASCII_TOKEN | oASCII_IDENT | oASCII_HEX, 

/* 100 144 64 [d] */

	oASCII_LOWER | oASCII_TOKEN | oASCII_IDENT | oASCII_HEX, 

/* 101 145 65 [e] */

	oASCII_LOWER | oASCII_TOKEN | oASCII_IDENT | oASCII_HEX, 

/* 102 146 66 [f] */

	oASCII_LOWER | oASCII_TOKEN | oASCII_IDENT | oASCII_HEX, 

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

	oASCII_PUNCT | oASCII_BEGIN, 

/* 124 174 7C [|] */

	oASCII_PUNCT | oASCII_LOGIC, 

/* 125 175 7D [}] */

	oASCII_PUNCT | oASCII_CLOSE, 

/* 126 176 7E [~] */

	oASCII_PUNCT | oASCII_LOGIC, 

/* 127 177 7F DEL */

	oASCII_CNTRL, 

/* 128 200 80 [�] */

	oASCII_NTYPE, 

/* 129 201 81 [�] */

	oASCII_NTYPE, 

/* 130 202 82 [�] */

	oASCII_NTYPE, 

/* 131 203 83 [�] */

	oASCII_NTYPE, 

/* 132 204 84 [�] */

	oASCII_NTYPE, 

/* 133 205 85 [�] */

	oASCII_NTYPE, 

/* 134 206 86 [�] */

	oASCII_NTYPE, 

/* 135 207 87 [�] */

	oASCII_NTYPE, 

/* 136 210 88 [�] */

	oASCII_NTYPE, 

/* 137 211 89 [�] */

	oASCII_NTYPE, 

/* 138 212 8A [�] */

	oASCII_NTYPE, 

/* 139 213 8B [�] */

	oASCII_NTYPE, 

/* 140 214 8C [�] */

	oASCII_NTYPE, 

/* 141 215 8D [�] */

	oASCII_NTYPE, 

/* 142 216 8E [�] */

	oASCII_NTYPE, 

/* 143 217 8F [�] */

	oASCII_NTYPE, 

/* 144 220 90 [�] */

	oASCII_NTYPE, 

/* 145 221 91 [�] */

	oASCII_NTYPE, 

/* 146 222 92 [�] */

	oASCII_NTYPE, 

/* 147 223 93 [�] */

	oASCII_NTYPE, 

/* 148 224 94 [�] */

	oASCII_NTYPE, 

/* 149 225 95 [�] */

	oASCII_NTYPE, 

/* 150 226 96 [�] */

	oASCII_NTYPE, 

/* 151 227 97 [�] */

	oASCII_NTYPE, 

/* 152 230 98 [�] */

	oASCII_NTYPE, 

/* 153 231 99 [�] */

	oASCII_NTYPE, 

/* 154 232 9A [�] */

	oASCII_NTYPE, 

/* 155 233 9B [�] */

	oASCII_NTYPE, 

/* 156 234 9C [�] */

	oASCII_NTYPE, 

/* 157 235 9D [�] */

	oASCII_NTYPE, 

/* 158 236 9E [�] */

	oASCII_NTYPE, 

/* 159 237 9F [�] */

	oASCII_NTYPE, 

/* 160 240 A0 [�] */

	oASCII_NTYPE, 

/* 161 241 A1 [�] */

	oASCII_NTYPE, 

/* 162 242 A2 [�] */

	oASCII_NTYPE, 

/* 163 243 A3 [�] */

	oASCII_NTYPE, 

/* 164 244 A4 [�] */

	oASCII_NTYPE, 

/* 165 245 A5 [�] */

	oASCII_NTYPE, 

/* 166 246 A6 [�] */

	oASCII_NTYPE, 

/* 167 247 A7 [�] */

	oASCII_NTYPE, 

/* 168 250 A8 [�] */

	oASCII_NTYPE, 

/* 169 251 A9 [�] */

	oASCII_NTYPE, 

/* 170 252 AA [�] */

	oASCII_NTYPE, 

/* 171 253 AB [�] */

	oASCII_NTYPE, 

/* 172 254 AC [�] */

	oASCII_NTYPE, 

/* 173 255 AD [�] */

	oASCII_NTYPE, 

/* 174 256 AE [�] */

	oASCII_NTYPE, 

/* 175 257 AF [�] */

	oASCII_NTYPE, 

/* 176 260 B0 [�] */

	oASCII_NTYPE, 

/* 177 261 B1 [�] */

	oASCII_NTYPE, 

/* 178 262 B2 [�] */

	oASCII_NTYPE, 

/* 179 263 B3 [�] */

	oASCII_NTYPE, 

/* 180 264 B4 [�] */

	oASCII_NTYPE, 

/* 181 265 B5 [�] */

	oASCII_NTYPE, 

/* 182 266 B6 [�] */

	oASCII_NTYPE, 

/* 183 267 B7 [�] */

	oASCII_NTYPE, 

/* 184 270 B8 [�] */

	oASCII_NTYPE, 

/* 185 271 B9 [�] */

	oASCII_NTYPE, 

/* 186 272 BA [�] */

	oASCII_NTYPE, 

/* 187 273 BB [�] */

	oASCII_NTYPE, 

/* 188 274 BC [�] */

	oASCII_NTYPE, 

/* 189 275 BD [�] */

	oASCII_NTYPE, 

/* 190 276 BE [�] */

	oASCII_NTYPE, 

/* 191 277 BF [�] */

	oASCII_NTYPE, 

/* 192 300 C0 [�] */

	oASCII_NTYPE, 

/* 193 301 C1 [�] */

	oASCII_NTYPE, 

/* 194 302 C2 [�] */

	oASCII_NTYPE, 

/* 195 303 C3 [�] */

	oASCII_NTYPE, 

/* 196 304 C4 [�] */

	oASCII_NTYPE, 

/* 197 305 C5 [�] */

	oASCII_NTYPE, 

/* 198 306 C6 [�] */

	oASCII_NTYPE, 

/* 199 307 C7 [�] */

	oASCII_NTYPE, 

/* 200 310 C8 [�] */

	oASCII_NTYPE, 

/* 201 311 C9 [�] */

	oASCII_NTYPE, 

/* 202 312 CA [�] */

	oASCII_NTYPE, 

/* 203 313 CB [�] */

	oASCII_NTYPE, 

/* 204 314 CC [�] */

	oASCII_NTYPE, 

/* 205 315 CD [�] */

	oASCII_NTYPE, 

/* 206 316 CE [�] */

	oASCII_NTYPE, 

/* 207 317 CF [�] */

	oASCII_NTYPE, 

/* 208 320 D0 [�] */

	oASCII_NTYPE, 

/* 209 321 D1 [�] */

	oASCII_NTYPE, 

/* 210 322 D2 [�] */

	oASCII_NTYPE, 

/* 211 323 D3 [�] */

	oASCII_NTYPE, 

/* 212 324 D4 [�] */

	oASCII_NTYPE, 

/* 213 325 D5 [�] */

	oASCII_NTYPE, 

/* 214 326 D6 [�] */

	oASCII_NTYPE, 

/* 215 327 D7 [�] */

	oASCII_NTYPE, 

/* 216 330 D8 [�] */

	oASCII_NTYPE, 

/* 217 331 D9 [�] */

	oASCII_NTYPE, 

/* 218 332 DA [�] */

	oASCII_NTYPE, 

/* 219 333 DB [�] */

	oASCII_NTYPE, 

/* 220 334 DC [�] */

	oASCII_NTYPE, 

/* 221 335 DD [�] */

	oASCII_NTYPE, 

/* 222 336 DE [�] */

	oASCII_NTYPE, 

/* 223 337 DF [�] */

	oASCII_NTYPE, 

/* 224 340 E0 [�] */

	oASCII_NTYPE, 

/* 225 341 E1 [�] */

	oASCII_NTYPE, 

/* 226 342 E2 [�] */

	oASCII_NTYPE, 

/* 227 343 E3 [�] */

	oASCII_NTYPE, 

/* 228 344 E4 [�] */

	oASCII_NTYPE, 

/* 229 345 E5 [�] */

	oASCII_NTYPE, 

/* 230 346 E6 [�] */

	oASCII_NTYPE, 

/* 231 347 E7 [�] */

	oASCII_NTYPE, 

/* 232 350 E8 [�] */

	oASCII_NTYPE, 

/* 233 351 E9 [�] */

	oASCII_NTYPE, 

/* 234 352 EA [�] */

	oASCII_NTYPE, 

/* 235 353 EB [�] */

	oASCII_NTYPE, 

/* 236 354 EC [�] */

	oASCII_NTYPE, 

/* 237 355 ED [�] */

	oASCII_NTYPE, 

/* 238 356 EE [�] */

	oASCII_NTYPE, 

/* 239 357 EF [�] */

	oASCII_NTYPE, 

/* 240 360 F0 [�] */

	oASCII_NTYPE, 

/* 241 361 F1 [�] */

	oASCII_NTYPE, 

/* 242 362 F2 [�] */

	oASCII_NTYPE, 

/* 243 363 F3 [�] */

	oASCII_NTYPE, 

/* 244 364 F4 [�] */

	oASCII_NTYPE, 

/* 245 365 F5 [�] */

	oASCII_NTYPE, 

/* 246 366 F6 [�] */

	oASCII_NTYPE, 

/* 247 367 F7 [�] */

	oASCII_NTYPE, 

/* 248 370 F8 [�] */

	oASCII_NTYPE, 

/* 249 371 F9 [�] */

	oASCII_NTYPE, 

/* 250 372 FA [�] */

	oASCII_NTYPE, 

/* 251 373 FB [�] */

	oASCII_NTYPE, 

/* 252 374 FC [�] */

	oASCII_NTYPE, 

/* 253 375 FD [�] */

	oASCII_NTYPE, 

/* 254 376 FE [�] */

	oASCII_NTYPE, 

/* 255 377 FF [�] */

	oASCII_NTYPE
}; 

/*====================================================================*
 *
 *   unsigned ctypemask (char const * ctypename) const;
 *
 *--------------------------------------------------------------------*/

unsigned oascii::ctypemask (char const * ctypename) const 

{ 
	unsigned bit = 0; 
	while (bit < SIZEOF (oascii::mbits)) 
	{ 
		if (!std::strcmp (ctypename, oascii::mbits [bit])) 
		{ 
			return (1 << bit); 
		} 
	} 
	return (0); 
} 

/*====================================================================*
 *
 *   bool isctype (signed c, unsigned short mask)
 *
 *
 *--------------------------------------------------------------------*/

bool oascii::isctype (signed c, unsigned short mask) 

{ 
	return ((oascii::cmask [c & UCHAR_MAX] & (mask))); 
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
	return ((oascii::cmask [c & UCHAR_MAX] & (oASCII_CNTRL))); 
} 

/*====================================================================*
 *
 *   bool isupper (signed c); 
 *
 *--------------------------------------------------------------------*/

bool oascii::isupper (signed c) 

{ 
	return ((oascii::cmask [c & UCHAR_MAX] & (oASCII_UPPER))); 
} 

/*====================================================================*
 *
 *   bool islower (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::islower (signed c) 

{ 
	return ((oascii::cmask [c & UCHAR_MAX] & (oASCII_LOWER))); 
} 

/*====================================================================*
 *
 *   bool isalpha (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::isalpha (signed c) 

{ 
	return ((oascii::cmask [c & UCHAR_MAX] & (oASCII_LOWER | oASCII_UPPER))); 
} 

/*====================================================================*
 *
 *   bool isdigit (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::isdigit (signed c) 

{ 
	return ((oascii::cmask [c & UCHAR_MAX] & (oASCII_DIGIT))); 
} 

/*====================================================================*
 *
 *   bool isxdigit (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::isxdigit (signed c) 

{ 
	return ((oascii::cmask [c & UCHAR_MAX] & (oASCII_HEX))); 
} 

/*====================================================================*
 *
 *   bool isalnum (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::isalnum (signed c) 

{ 
	return ((oascii::cmask [c & UCHAR_MAX] & (oASCII_UPPER | oASCII_LOWER | oASCII_DIGIT))); 
} 

/*====================================================================*
 *
 *   bool isspace (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::isspace (signed c) 

{ 
	return ((oascii::cmask [c & UCHAR_MAX] & (oASCII_SPACE))); 
} 

/*====================================================================*
 *
 *   bool isgraph (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::isgraph (signed c) 

{ 
	return ((oascii::cmask [c & UCHAR_MAX] & (oASCII_UPPER | oASCII_LOWER | oASCII_DIGIT | oASCII_PUNCT))); 
} 

/*====================================================================*
 *
 *   bool isprint (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::isprint (signed c) 

{ 
	return ((oascii::cmask [c & UCHAR_MAX] & (oASCII_CNTRL)) == 0); 
} 

/*====================================================================*
 *
 *   bool ispunct (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::ispunct (signed c) 

{ 
	return ((oascii::cmask [c & UCHAR_MAX] & (oASCII_PUNCT))); 
} 

/*====================================================================*
 *
 *   bool isident (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::isident (signed c) 

{ 
	return ((oascii::cmask [c & UCHAR_MAX] & (oASCII_IDENT))); 
} 

/*====================================================================*
 *
 *   bool isquote (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::isquote (signed c) 

{ 
	return ((oascii::cmask [c & UCHAR_MAX] & (oASCII_QUOTE))); 
} 

/*====================================================================*
 *
 *   bool isarith (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::isarith (signed c) 

{ 
	return ((oascii::cmask [c & UCHAR_MAX] & (oASCII_ARITH))); 
} 

/*====================================================================*
 *
 *   bool isequal (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::isequal (signed c) 

{ 
	return ((oascii::cmask [c & UCHAR_MAX] & (oASCII_EQUAL))); 
} 

/*====================================================================*
 *
 *   bool islogic (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::islogic (signed c) 

{ 
	return ((oascii::cmask [c & UCHAR_MAX] & (oASCII_LOGIC))); 
} 
/*====================================================================*
 *
 *   bool isgroup (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::isgroup (signed c) 

{ 
	return ((oascii::cmask [c & UCHAR_MAX] & (oASCII_BEGIN | oASCII_CLOSE))); 
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
	return ((oascii::cmask [c & UCHAR_MAX] & (oASCII_BEGIN))); 
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
	return ((oascii::cmask [c & UCHAR_MAX] & (oASCII_CLOSE))); 
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
	return ((oascii::cmask [c & UCHAR_MAX] & (oASCII_COMMA))); 
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
	return ((oascii::cmask [c & UCHAR_MAX] & (oASCII_TOKEN))); 
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
	return ((c == '\0') || (c == '\n') || (c == EOF)); 
} 

/*====================================================================*
 *
 *   bool isbreak (signed c, signed o);
 *
 *--------------------------------------------------------------------*/

bool oascii::isbreak (signed c, signed o) 

{ 
	return ((c == o) || (c == '\0') || (c == '\n') || (c == EOF)); 
} 

/*====================================================================*
 *
 *   bool nobreak (signed c);
 *
 *--------------------------------------------------------------------*/

bool oascii::nobreak (signed c) 

{ 
	return ((c != '\0') && (c != '\n') && (c != EOF)); 
} 

/*====================================================================*
 *
 *   bool nobreak (signed c, signed o);
 *
 *--------------------------------------------------------------------*/

bool oascii::nobreak (signed c, signed o) 

{ 
	return ((c != o) && (c != '\0') && (c != '\n') && (c != EOF)); 
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
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�", 
	"�"
}; 

/*====================================================================*
 *
 *   void enumerate () const;
 *
 *--------------------------------------------------------------------*/

void oascii::enumerate () const 

{ 
	for (unsigned bit = 0; bit < SIZEOF (oascii::mbits); bit++) 
	{ 
		std::cout << oascii::mbits [bit] << " "; 
		for (signed c = 0; c <= SCHAR_MAX; c++) 
		{ 
			if (oascii::cmask [c] & (1 << bit)) 
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
 *   print a character classification matrix on stdout suitable for
 *   input to program matrix which can print an HTML;
 *
 *--------------------------------------------------------------------*/

void oascii::matrix () const 

{ 
	std::cout << "ascii"; 
	for (unsigned bit = 0; bit < SIZEOF (oascii::mbits); bit++) 
	{ 
		std::cout << " " << oascii::mbits [bit]; 
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
		for (unsigned bit = 0; bit < SIZEOF (mbits); bit++) 
		{ 
			if (oascii::cmask [c] & (1 << bit)) 
			{ 
				std::cout << " " << oascii::mbits [bit]; 
			} 
		} 
		std::cout << ";" << std::endl; 
	} 
	return; 
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

oascii::~oascii () 

{ 
	return; 
} 

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif


