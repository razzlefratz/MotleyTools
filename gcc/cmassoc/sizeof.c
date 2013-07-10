/*====================================================================*
 *
 *   sizeof.c - display sizeof variable types;
 *
 *   this program is a simple debugging tool that displays the size of
 *   each intrinsic c language data type on stdout;
 *
 *   use it to confirm actual data types sizes on your host computer;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <stddef.h>
#include <unistd.h>

#if defined (__APPLE__)
#define SIZE_T_SPEC "%zu"
#define OFF_T_SPEC "%llu"
#else
#define SIZE_T_SPEC "%zu"
#define OFF_T_SPEC "%llu"
#endif

int main (int argc, char const * argv []) 

{ 
	union 
	{ 
		unsigned number; 
		char octets [sizeof (unsigned)]; 
	} 
	endian; 
	unsigned octet = 0; 
	unsigned value = 0x12; 
	while (octet < sizeof (unsigned)) 
	{ 
		endian.octets [octet++ ] = value; 
		value += 0x22; 
	} 
	printf ("order         %8x\n", endian.number); 
	printf ("\n"); 
	printf ("true          %d\n", (int)(1 > 0)); 
	printf ("false         %d\n", (int)(1 < 0)); 
	printf ("\n"); 
	printf ("double        " SIZE_T_SPEC " bytes\n", sizeof (double)); 
	printf ("long long     " SIZE_T_SPEC " bytes\n", sizeof (long long)); 
	printf ("float         " SIZE_T_SPEC " bytes\n", sizeof (float)); 
	printf ("long          " SIZE_T_SPEC " bytes\n", sizeof (long)); 
	printf ("int           " SIZE_T_SPEC " bytes\n", sizeof (int)); 
	printf ("short         " SIZE_T_SPEC " bytes\n", sizeof (short)); 
	printf ("char          " SIZE_T_SPEC " bytes\n", sizeof (char)); 
	printf ("\n"); 
	printf ("(double *)    " SIZE_T_SPEC " bytes\n", sizeof (double * )); 
	printf ("(long long *) " SIZE_T_SPEC " bytes\n", sizeof (long long * )); 
	printf ("(float *)     " SIZE_T_SPEC " bytes\n", sizeof (float * )); 
	printf ("(long *)      " SIZE_T_SPEC " bytes\n", sizeof (long * )); 
	printf ("(int *)       " SIZE_T_SPEC " bytes\n", sizeof (int * )); 
	printf ("(short *)     " SIZE_T_SPEC " bytes\n", sizeof (short * )); 
	printf ("(char *)      " SIZE_T_SPEC " bytes\n", sizeof (char * )); 
	printf ("\n"); 
	printf ("off_t         " SIZE_T_SPEC " bytes\n", sizeof (off_t)); 
	printf ("size_t        " SIZE_T_SPEC " bytes\n", sizeof (size_t)); 
	printf ("ssize_t       " SIZE_T_SPEC " bytes\n", sizeof (ssize_t)); 
	printf ("ptrdiff_t     " SIZE_T_SPEC " bytes\n", sizeof (ptrdiff_t)); 
	return (0); 
} 

