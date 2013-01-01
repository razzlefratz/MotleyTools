/*====================================================================*
 *
 *   ftype.c - Linux file type converstion;
 *
 *   linux.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef FTYPE_SOURCE
#define FTYPE_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <string.h>
#include <sys/stat.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../linux/linux.h"

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

static struct 

{
	char code;
	mode_t mask;
}

ftypes [] = 

{
	{
		'R',
		__S_IFREG
	},
	{
		'D',
		__S_IFDIR
	},
	{
		'L',
		__S_IFLNK
	},
	{
		'C',
		__S_IFCHR
	},
	{
		'B',
		__S_IFBLK
	},
	{
		'F',
		__S_IFIFO
	},
	{
		'S',
		__S_IFSOCK
	},
};


/*====================================================================*
 *
 *   char const *ftypecode (mode_t ftypemask);
 *
 *   return a single character typecode corresponding to the stat 
 *   structure st_mode typemask; return '?' for illegal mask values; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char ftypecode (mode_t ftypemask) 

{
	int index;
	ftypemask &= ~FILE_MODE_MASK;
	for (index = 0; index < sizeof (ftypes); index++) 
	{
		if (ftypemask == ftypes [index].mask) 
		{
			return (ftypes [index].code);
		}
	}
	return ('?');
}


/*====================================================================*
 *
 *   mode_t ftypemask (char *ftypecode);
 *
 *   return the stat struct st_mode mask corresponding to the single
 *   letter typecode; return 0 for illegal typecodes;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

mode_t ftypemask (char ftypecode) 

{
	int index;
	for (index = 0; index < sizeof (ftypes); index++) 
	{
		if (ftypecode == ftypes [index].code) 
		{
			return (ftypes [index].mask);
		}
	}
	return (0);
}


/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#endif

