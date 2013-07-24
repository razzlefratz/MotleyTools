/*====================================================================*
 *
 *   opassword.cpp - implementation of the opassword class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oPASSWORD_SOURCE
#define oPASSWORD_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <iostream>
#include <climits>
#include <cstdlib>
#include <cctype>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/opassword.hpp"

/*====================================================================*
 *
 *   const unsigned count () const;
 *
 *
 *--------------------------------------------------------------------*/

unsigned opassword::count () const 

{
	return (this->mcount);
}

/*====================================================================*
 *
 *   opassword & count (unsigned count);
 *
 *
 *--------------------------------------------------------------------*/

opassword & opassword::count (unsigned count) 

{
	this->mcount = count;
	return (* this);
}

/*====================================================================*
 *
 *   const unsigned group () const;
 *
 *
 *--------------------------------------------------------------------*/

unsigned opassword::group () const 

{
	return (this->mgroup);
}

/*====================================================================*
 *
 *   opassword & group (unsigned group);
 *
 *
 *--------------------------------------------------------------------*/

opassword & opassword::group (unsigned group) 

{
	this->mgroup = group;
	return (* this);
}

/*====================================================================*
 *
 *   unsigned space () const;
 *
 *
 *--------------------------------------------------------------------*/

unsigned opassword::space () const 

{
	return (this->mbreak);
}

/*====================================================================*
 *
 *   opassword & space (unsigned space);
 *
 *
 *--------------------------------------------------------------------*/

opassword & opassword::space (unsigned space) 

{
	this->mbreak = space;
	return (* this);
}

/*====================================================================*
 *
 *   opassword & print (unsigned salt);
 *
 *
 *--------------------------------------------------------------------*/

opassword & opassword::print (unsigned salt) 

{
	std::srand (salt);
	this->mindex = 0;
	while (this->mindex < this->mcount) 
	{
		unsigned c = (char)(std::rand () % (SCHAR_MAX+1));
		if ((this->mindex) && (this->mgroup) && !(this->mindex % this->mgroup)) 
		{
			std::cout << this->mbreak;
		}
		std::cout << this->mcharset [c];
		this->mindex++;
	}
	return (* this);
}

/*====================================================================*
 *
 *   opassword();
 *
 *
 *--------------------------------------------------------------------*/

opassword::opassword (unsigned seed) 

{
	std::srand (seed);
	this->mcharset = new char [UCHAR_MAX];
	this->mindex = 0;
	while (this->mindex < UCHAR_MAX) 
	{
		char c = (char)(std::rand () % (SCHAR_MAX+1));
		if (std::isupper (c)) 
		{
			mcharset [this->mindex++] = c;
		}
	}
	this->mcount = 16;
	this->mgroup = 4;
	this->mbreak = '-';
	return;
};

/*====================================================================*
 *
 *   ~opassword();
 *
 *
 *--------------------------------------------------------------------*/

opassword::~opassword () 

{
	delete [] this->mcharset;
	return;
}

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

