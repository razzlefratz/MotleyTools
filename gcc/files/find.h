/*====================================================================*
 *
 *   find.h - find structure declaration and definitions; 
 *
 *
 *.  Motley Tools by Charles Maier
 *:  modified wed 29 oct 03 by user root on host zeus;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef FIND_HEADER
#define FIND_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/types.h"

/*====================================================================*
 *   declare constants;
 *--------------------------------------------------------------------*/

#define FIND_M_NORMAL 0
#define FIND_M_SEARCH 1

#define FIND_B_RECURSE  (1 << 0)
#define FIND_B_TRAVERSE (1 << 1)
#define FIND_B_TESTRUN  (1 << 2)
#define FIND_B_BAILOUT  (1 << 3)
#define FIND_B_DATETIME (1 << 4) 
#define FIND_B_FILESIZE (1 << 5) 
#define FIND_B_PATHNAME (1 << 6)
#define FIND_B_FILENAME (1 << 7)
#define FIND_B_WILDCARD (1 << 8)
#define FIND_B_VERBOSE  (1 << 9)
#define FIND_B_SILENCE  (1 << 10)
#define FIND_B_EVENTS   (1 << 11)
#define FIND_B_ERRORS   (1 << 12)
#define FIND_B_SPARE1   (1 << 13)
#define FIND_B_SPARE2   (1 << 14)
#define FIND_B_SPARE3   (1 << 15)
#define FIND_B_SPARE4   (1 << 16)
#define FIND_B_SPARE5   (1 << 17)
#define FIND_B_SPARE6   (1 << 18)
#define FIND_B_DIR      (1 << 19)
#define FIND_B_REG      (1 << 20)
#define FIND_B_REGULAR  (1 << 20)
#define FIND_B_LNK      (1 << 21)
#define FIND_B_SYMLINK  (1 << 21)
#define FIND_B_BLK      (1 << 22)
#define FIND_B_CHR      (1 << 23)
#define FIND_B_FIFO     (1 << 24)
#define FIND_B_SOCK     (1 << 25)

#define FIND_B_ALL (FIND_B_DIR|FIND_B_REG|FIND_B_LNK|FIND_B_BLK|FIND_B_CHR|FIND_B_FIFO|FIND_B_SOCK)

/*====================================================================*
 *   declare structures; 
 *--------------------------------------------------------------------*/

typedef struct _find_ 

{
	struct stat statinfo;
	char fullname [FILENAME_MAX];
	char pathname [FILENAME_MAX];
	char filename [FILENAME_MAX];
	char basename [FILENAME_MAX];
	char extender [FILENAME_MAX];
	char wildcard [FILENAME_MAX];
	flag_t flagword;
	mode_t filemode;
	time_t filetime;
	size_t filesize;
	file_t fd;
}

FIND;

/*====================================================================*
 *   declare functions; 
 *--------------------------------------------------------------------*/

void makefind (struct _find_ *find, char const *filename);
void showfind (struct _find_ *find, FILE * fp);

/*====================================================================*
 *   end definitions and declarations;
 *--------------------------------------------------------------------*/

#endif

