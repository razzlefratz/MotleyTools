/*====================================================================*
 *
 *   ofileopen.cpp - implementation of the ofileopen class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oFILEOPEN_SOURCE
#define oFILEOPEN_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <dirent.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ofileopen.hpp"

/*====================================================================*
 *   class variables;    
 *--------------------------------------------------------------------*/

struct stat ofileopen::statinfo;
std::ifstream ofileopen::source;
std::ofstream ofileopen::target;

/*====================================================================*
 *
 *   unsigned versions (void) const;
 *
 *   return the maximum number of versions supported; 
 *
 *--------------------------------------------------------------------*/

unsigned ofileopen::versions (void) const 

{
	return (this->mlimit);
}

/*====================================================================*
 *
 *   bool opensave (char const * pathname, char const * extender);
 *
 *   open the named file as stdout and create a backup file having a
 *   specified file extension;
 *
 *--------------------------------------------------------------------*/

bool ofileopen::opensave (char const * filespec, char const * extender) 

{
	ofilespec loadspec (filespec);
	ofilespec savespec (filespec);
	if (!ofileopen::permit (filespec)) 
	{
		return (false);
	}
	savespec.extender (extender);
	if (!stat (savespec.fullname (), & this->statinfo)) 
	{
		if (!std::remove (savespec.fullname ())) 
		{
			ofileopen::merror.error ("Can't remove %s", savespec.fullname ());
			return (false);
		}
	}
	return (this->filter (loadspec.fullname (), savespec.fullname ()));
}

/*====================================================================*
 *
 *   bool openedit (char const *filespec);
 *
 *   open the named file as stdout and create a backup file having a
 *   numeric file extension; 
 *
 *--------------------------------------------------------------------*/

bool ofileopen::openedit (char const * filespec) 

{
	ofilespec loadspec (filespec);
	ofilespec savespec (filespec);
	if (!ofileopen::permit (filespec)) 
	{
		return (false);
	}
	for (this->mcount = 1; this->mcount < this->mlimit; this->mcount++) 
	{
		savespec.savename (this->mcount, this->mdigit);
		if (stat (savespec.fullname (), & this->statinfo)) 
		{
			return (this->filter (loadspec.fullname (), savespec.fullname ()));
		}
	}
	ofileopen::merror.print ("can't open %s: too many file versions", loadspec.fullname ());
	return (false);
}

/*====================================================================*
 *
 *   bool permit (char const * filespec) const;
 *
 *   confirm that filespec exists and check the file type; only open
 *   regular files; report merrors in standard fashion;
 *
 *--------------------------------------------------------------------*/

bool ofileopen::permit (char const * filespec) const 

{
	if (lstat (filespec, & this->statinfo)) 
	{
		ofileopen::merror.error (filespec);
		return (false);
	}
	if (S_ISDIR (this->statinfo.st_mode)) 
	{
		ofileopen::merror.print ("Won't open %s: file is a folder", filespec);
		return (false);
	}
	if (S_ISLNK (this->statinfo.st_mode)) 
	{
		ofileopen::merror.print ("Won't open %s: file is a symlink", filespec);
		return (false);
	}
	if (S_ISBLK (this->statinfo.st_mode)) 
	{
		ofileopen::merror.print ("Won't open %s: file is a device", filespec);
		return (false);
	}
	if (S_ISCHR (this->statinfo.st_mode)) 
	{
		ofileopen::merror.print ("Won't open %s: file is a device", filespec);
		return (false);
	}
	if (S_ISFIFO (this->statinfo.st_mode)) 
	{
		ofileopen::merror.print ("Won't open %s: file is a fifo", filespec);
		return (false);
	}
	if (S_ISSOCK (this->statinfo.st_mode)) 
	{
		ofileopen::merror.print ("Won't open %s: file is a socket", filespec);
		return (false);
	}
	if (S_ISREG (this->statinfo.st_mode)) 
	{
		return (true);
	}
	return (true);
}

/*====================================================================*
 *   
 *   bool filter (char const * filespec, char const * savespec);
 *
 *   
 *
 *--------------------------------------------------------------------*/

bool ofileopen::filter (char const * filespec, char const * savespec) 

{
	ofileopen::close ();
	ofileopen::source.open (filespec, std::ios::binary | std::ios::in);
	if (!ofileopen::source.is_open ()) 
	{
		ofileopen::merror.error ("Can't open %s for input", filespec);
		return (false);
	}
	std::cin.rdbuf (ofileopen::source.rdbuf ());
	if (std::rename (filespec, savespec)) 
	{
		ofileopen::merror.error ("Can't rename %s as %s", filespec, savespec);
		return (false);
	}
	ofileopen::target.open (filespec, std::ios::binary | std::ios::out);
	if (!ofileopen::target.is_open ()) 
	{
		ofileopen::merror.error ("Can't open %s for output", filespec);
		return (false);
	}
	std::cout.rdbuf (ofileopen::target.rdbuf ());
	if (chmod (filespec, this->statinfo.st_mode)) 
	{
		ofileopen::merror.error ("Can't preserve %s permissions", filespec);
		return (false);
	}
	if (chown (filespec, this->statinfo.st_uid, this->statinfo.st_gid)) 
	{
		ofileopen::merror.error ("Can't preserve %s ownership", filespec);
		return (false);
	}
	return (true);
}

/*====================================================================*
 *   
 *   ofileopen & close (void);
 *
 *   close source and target file streams; 
 *
 *--------------------------------------------------------------------*/

ofileopen & ofileopen::close (void) 

{
	if (ofileopen::source.is_open ()) 
	{
		ofileopen::source.close ();
	}
	if (ofileopen::target.is_open ()) 
	{
		ofileopen::target.close ();
	}
	return (* this);
}

/*====================================================================*
 *   
 *   ofileopen (unsigned limit);
 *
 *   initialize version limit and compute numeric field width; 
 *
 *--------------------------------------------------------------------*/

ofileopen::ofileopen (unsigned limit) 

{
	this->mcount = 0;
	this->mlimit = limit;
	this->mdigit = 0;
	while (limit > 0) 
	{
		this->mdigit++;
		limit /= 10;
	}
	return;
}

/*====================================================================*
 *   
 *   ofileopen (void);
 *
 *   initialize version limit and extension field width; 
 *
 *--------------------------------------------------------------------*/

ofileopen::ofileopen (void) 

{
	this->mcount = 0;
	this->mlimit = 1000;
	this->mdigit = 3;
	return;
}

/*====================================================================*
 *   
 *   ~ ofileopen (void);
 *
 *   Nothing to do;
 *
 *--------------------------------------------------------------------*/

ofileopen::~ofileopen (void) 

{
	return;
}

/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif

