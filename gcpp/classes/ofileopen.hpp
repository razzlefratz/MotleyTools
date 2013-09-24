/*====================================================================*
 *
 *   ofileopen.hpp - interface for the ofileopen class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oFILEOPEN_HEADER
#define oFILEOPEN_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <sys/stat.h>
#include <fstream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/oerror.hpp"
#include "../classes/ofilespec.hpp"

/*====================================================================*
 *   begin definition;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) ofileopen

{
public: 
	ofileopen (void);
	ofileopen (unsigned limit);
	virtual ~ ofileopen (void);
	unsigned count (void) const;
	unsigned versions (void) const;
	bool permit (char const * filespec) const;
	bool filter (char const * filespec, char const * savespec);
	bool opensave (char const * filespec, char const * extender);
	bool openedit (char const * filespec);
	ofileopen & close (void);
protected: 
private: 
	static struct stat statinfo;
	static std::ifstream source;
	static std::ofstream target;
	oerror merror;
	unsigned mcount;
	unsigned mlimit;
	unsigned mdigit;
};

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif



