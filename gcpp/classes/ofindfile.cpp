/*====================================================================*
 *
 *   ofindfile.cpp - implementation of the ofindfile class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oSEARCH_SOURCE
#define oSEARCH_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstdlib>
#include <cstring>
#include <iostream>

#include <dirent.h>
#include <sys/stat.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ofindfile.hpp"

#include "../../gcc/files/files.h"

/*====================================================================*
 *   
 *   FILE *fopen1(char const *file, char const *mode);
 *
 *   try to open the named file using fopen(); if it does not open 
 *   then try each parent folder in turn; return a file pointer on
 *   success; return (FILE *)(0) on failure;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

FILE * ofindfile::fopen1 (char const * file, char const * mode) 

{
	FILE * fp;
	char pathname [FILENAME_MAX];
	int node = 0;
	pathname [0] = (char) (0);
	this->mstack [0] = pathname;
	for (char * cp = pathname; (node < FILE_DIR_MAX) && (* cp = * file); cp++, file++) 
	{
		if (* cp == PATH_C_EXTENDER) 
		{
			this->mstack [node++] = cp;
		}
	}
	while (((fp = fopen (pathname, mode)) == (FILE *) (0)) && (node-- > 1)) 
	{
		strcpy (this->mstack [node - 1], this->mstack [node]);
	}
	return (fp);
}

/*====================================================================*
 *   
 *   FILE *ofindfile::fopen2 (char const *file, char const *mode, char const *pathstring);
 *
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

FILE * ofindfile::fopen2 (char const * file, char const * mode, char const * pathstring) 

{
	FILE * fp = (FILE *) (0);
	char temp [FILENAME_MAX] = 
	{
		(char) (0)
	};
	if (file != (char const *) (0)) 
	{
		if (mode != (char const *) (0)) 
		{
			if (pathstring != (char const *) (0)) 
			{
				char * sp = (char *) (file);
				while (* file != (char) (0)) 
				{
					file++;
				}
				while ((file > sp) && (* file != PATH_C_EXTENDER)) 
				{
					file--;
				}
				std::strcpy (temp, sp);
				while (((fp = this->fopen1 (temp, mode)) == (FILE *) (0)) && (* pathstring)) 
				{
					sp = temp;
					while ((* sp = * pathstring) && (* sp != PATH_C_SEPARATOR)) 
					{
						sp++,
						pathstring++;
					}
					if (* pathstring) 
					{
						pathstring++;
					}
					* sp++ = PATH_C_EXTENDER;
					std::strcpy (sp, file);
				}
			}
		}
	}
	return (fp);
}

/*====================================================================*
 *   
 *   ofindfile ();
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ofindfile::ofindfile () 

{
	this->mstack = new char * [FILE_DIR_MAX];
	this->mlimit = FILE_DIR_MAX;
	this->mcount = 0;
	this->mlevel = 0;
	this->mindex = 0;
	return;
}

/*====================================================================*
 *   
 *   ~ofindfile ();
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ofindfile::~ofindfile () 

{
	delete [] this->mstack;
	return;
}

/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif

