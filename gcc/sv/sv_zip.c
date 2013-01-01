/*====================================================================*
 * 
 *   sv_zip[] - 
 * 
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 * 
 *--------------------------------------------------------------------*/

#include <stddef.h>

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define ZIP_O_GZ                         0
#define ZIP_O_TAR                        1
#define ZIP_O_TARBZ2                     2
#define ZIP_O_TARGZ                      3
#define ZIP_O_TGZ                        4
#define ZIP_O_ZIP                        5

#define ZIP_N_ITEM                       6

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

char const *sv_zip [] = 

{
	".gz",
	".tar",
	".tar.bz2",
	".tar.gz",
	".tgz",
	".zip",
	NULL
};

