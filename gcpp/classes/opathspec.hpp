/*====================================================================*
 *
 *   opathspec.hpp - interface for the opathspec class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oPATH_HEADER
#define oPATH_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <sys/stat.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/owildcard.hpp"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

class __declspec (dllexport) opathspec: private owildcard 

{
public:
	opathspec ();
	virtual ~ opathspec ();
	bool isdotdir (char const * filename);
	bool exists (char const * pathname);
	bool infolder (char fullname [], char const * wildcard, bool recurse);
	bool instring (char fullname [], char const * pathname, char const * filename);
	bool instring (char fullname [], char const * pathname, char const * filename, bool recurse);
	bool invector (char fullname [], char const * pathname [], char const * filename);
	bool invector (char fullname [], char const * pathname [], char const * filename, bool recurse);
	char const * dirname (char const * filespec);
	char const * basename (char const * filespec);
	void fullpath (char fullname [], char const * filespec);
	void makepath (char fullname [], char const * pathname, char const * filename);
	void findpath (char const * fullname, char pathname [], char filename []);
	void partpath (char const * fullname, char pathname [], char filename []);
	void partfile (char const * filename, char basename [], char extender []);
private:
	struct stat mstatinfo;
	void splitpath (char * filespec);
	void mergepath ();
	char ** mstack;
	unsigned mindex;
	unsigned mstart;
	unsigned mlevel;
	unsigned mcount;
	unsigned mlimit;
};


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

