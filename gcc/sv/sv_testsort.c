/*====================================================================*
 *
 *   sv_sort[] - sample sort string vector;
 *
 *   this module declares a simple string vector used to test various sort
 *   functions; it contains some duplicate strings;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <stddef.h>

#define SV_SORT_MAX 24

char const *sv_sort [] = 

{
	"abc",
	"def",
	"ghi",
	"jkl",
	"mno",
	"pqr",
	"stu",
	"vwx",
	"yz0",
	"123",
	"456",
	"789",
	"ABC",
	"DEF",
	"GHI",
	"JKL",
	"MNO",
	"PQR",
	"STU",
	"VWX",
	"YZ0",
	"123",
	"456",
	"789",
	NULL
};

