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
 *   unsigned ofileopen::versions () const;
 *
 *   return the maximum number of versions supported; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

unsigned ofileopen::versions () const 

{
	return (this->mlimit);
}

/*====================================================================*
 *
 *   bool opensave (char const *pathname, char const *extender);
 *
 *   open the named file as stdout and create a backup file having a
 *   specified file extension;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
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
			ofileopen::message.error ("Can't remove %s", savespec.fullname ());
			return (false);
		}
	}
	return (this->filter (loadspec.fullname (), savespec.fullname ()));
}

/*====================================================================*
 *
 *   bool openedit(char const *filespec);
 *
 *   open the named file as stdout and create a backup file having a
 *   numeric file extension; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
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
	ofileopen::message.print ("can't open %s: too many file versions", loadspec.fullname ());
	return (false);
}

/*====================================================================*
 *
 *   bool ofileopen::permit (char const *filespec) const;
 *
 *   confirm that filespec exists and check the file type; only open
 *   regular files; report messages in standard fashion;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool ofileopen::permit (char const * filespec) const 

{
	if (lstat (filespec, & this->statinfo)) 
	{
		ofileopen::message.error (filespec);
		return (false);
	}
	if (S_ISDIR (this->statinfo.st_mode)) 
	{
		ofileopen::message.print ("Won't open %s: file is a folder", filespec);
		return (false);
	}
	if (S_ISLNK (this->statinfo.st_mode)) 
	{
		ofileopen::message.print ("Won't open %s: file is a symlink", filespec);
		return (false);
	}
	if (S_ISBLK (this->statinfo.st_mode)) 
	{
		ofileopen::message.print ("Won't open %s: file is a device", filespec);
		return (false);
	}
	if (S_ISCHR (this->statinfo.st_mode)) 
	{
		ofileopen::message.print ("Won't open %s: file is a device", filespec);
		return (false);
	}
	if (S_ISFIFO (this->statinfo.st_mode)) 
	{
		ofileopen::message.print ("Won't open %s: file is a fifo", filespec);
		return (false);
	}
	if (S_ISSOCK (this->statinfo.st_mode)) 
	{
		ofileopen::message.print ("Won't open %s: file is a socket", filespec);
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
 *   bool filter ();
 *
 *   
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool ofileopen::filter (char const * filespec, char const * savespec) 

{
	ofileopen::close ();
	ofileopen::source.open (filespec, std::ios::binary | std::ios::in);
	if (!ofileopen::source.is_open ()) 
	{
		ofileopen::message.error ("Can't open %s for input", filespec);
		return (false);
	}
	std::cin.rdbuf (ofileopen::source.rdbuf ());
	if (rename (filespec, savespec)) 
	{
		ofileopen::message.error ("Can't rename %s as %s", filespec, savespec);
		return (false);
	}
	ofileopen::target.open (filespec, std::ios::binary | std::ios::out);
	if (!ofileopen::target.is_open ()) 
	{
		ofileopen::message.error ("Can't open %s for output", filespec);
		return (false);
	}
	std::cout.rdbuf (ofileopen::target.rdbuf ());
	if (chmod (filespec, this->statinfo.st_mode)) 
	{
		ofileopen::message.error ("Can't preserve %s permissions", filespec);
		return (false);
	}
	if (chown (filespec, this->statinfo.st_uid, this->statinfo.st_gid)) 
	{
		ofileopen::message.error ("Can't preserve %s ownership", filespec);
		return (false);
	}
	return (true);
}

/*====================================================================*
 *   
 *   ofileopen & close ();
 *
 *   close source and target file streams; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ofileopen & ofileopen::close () 

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
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
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
 *   ofileopen ();
 *
 *   initialize version limit and extension field width; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ofileopen::ofileopen () 

{
	this->mcount = 0;
	this->mlimit = 1000;
	this->mdigit = 3;
	return;
}

/*====================================================================*
 *   
 *   ~ofileopen ();
 *
 *   Nothing to do;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ofileopen::~ofileopen () 

{
	return;
}

/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif

