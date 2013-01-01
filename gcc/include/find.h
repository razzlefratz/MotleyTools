/*====================================================================*
 *
 *   find.h - find structure definitions and declarations;
 *
 *
 *.  Motley Tools by Charles Maier
 *:  compiled for debian gnu/linux environment using gcc 2.95 compiler;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef FIND_HEADER
#define FIND_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <stddef.h>
#include <sys/stat.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/types.h"

/*====================================================================*
 *    declare constants;
 *--------------------------------------------------------------------*/

#define FIND_M_NORMAL 0
#define FIND_M_SEARCH 1

#define FIND_B_RECURSE  0x00000001
#define FIND_B_TRAVERSE 0x00000002
#define FIND_B_BAILOUT  0x00000004
#define FIND_B_TESTRUN  0x00000008
#define FIND_B_DATETIME 0x00000010 
#define FIND_B_PATHNAME 0x00000020
#define FIND_B_BASENAME 0x00000040
#define FIND_B_WILDCARD 0x00000080
#define FIND_B_ERRORS   0x00000100
#define FIND_B_EVENTS   0x00000200
#define FIND_B_FAILURE  FIND_B_ERRORS
#define FIND_B_VERBOSE  FIND_B_EVENTS

#define FIND_B_DIR      0x00010000
#define FIND_B_REG      0x00020000
#define FIND_B_LNK      0x00040000
#define FIND_B_BLK      0x00080000
#define FIND_B_CHR      0x00100000
#define FIND_B_FIFO     0x00200000
#define FIND_B_SOCK     0x00400000
#define FIND_B_ALL (FIND_B_DIR|FIND_B_REG|FIND_B_LNK|FIND_B_BLK|FIND_B_CHR|FIND_B_FIFO|FIND_B_SOCK)

/*====================================================================*
 *   declare structures; 
 *--------------------------------------------------------------------*/

typedef struct _find_ 

{
	struct stat statinfo;
	char fullpath [FILENAME_MAX+1];
	char pathname [FILENAME_MAX+1];
	char basename [FILENAME_MAX+1];
	char filename [FILENAME_MAX+1];
	char extender [FILENAME_MAX+1];
	char wildcard [FILENAME_MAX+1];
	flag_t flagword;
}

FIND;

/*====================================================================*
 *   declare functions; 
 *--------------------------------------------------------------------*/

void makefind (struct _find_ *find, char const *filespec, int mode);
void showfind (struct _find_ *find, FILE * basename);

/*====================================================================*
 *   end definitions and declarations;
 *--------------------------------------------------------------------*/

#endif

