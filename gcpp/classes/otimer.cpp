/*====================================================================*
 *
 *   otimer.cpp - definition of otimer class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oTIMER_SOURCE
#define oTIMER_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstring>
#include <time.h>

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#include "../classes/otimer.hpp"

/*====================================================================*
 *
 *   otimer & set (unsigned timer);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otimer & otimer::set (unsigned timer)

{
	this->mtimer = timer;
	return (* this);
}

/*====================================================================*
 *
 *   otimer & reset ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otimer & otimer::reset ()

{
	gettimeofday (this->mstart, NULL);
	return (* this);
}

/*====================================================================*
 *
 *   unsigned since ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

unsigned otimer::since ()

{
	gettimeofday (this->mclock, NULL);
	this->msince = (this->mclock->tv_sec - this->mstart->tv_sec) * 1000;
	this->msince += (this->mclock->tv_usec - this->mstart->tv_usec) / 1000;
	return (this->msince);
}

/*====================================================================*
 *
 *   bool expired ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool otimer::expired ()

{
	gettimeofday (this->mclock, NULL);
	this->msince = (this->mclock->tv_sec - this->mstart->tv_sec) * 1000;
	this->msince += (this->mclock->tv_usec - this->mstart->tv_usec) / 1000;
	return (this->msince > this->mtimer);
}

/*====================================================================*
 *
 *   otimer ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otimer::otimer ()

{
	this->mstart = new struct timeval;
	this->mclock = new struct timeval;
	std::memset (this->mstart, 0, sizeof (struct timeval));
	std::memset (this->mclock, 0, sizeof (struct timeval));
	this->mtimer = 0;
	return;
}

/*====================================================================*
 *
 *   otimer::~otimer ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otimer::~ otimer ()

{
	return;
}

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif



