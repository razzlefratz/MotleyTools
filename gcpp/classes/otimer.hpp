/*====================================================================*
 *
 *   otimer.hpp - declaration of otimer class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oTIMER_HEADER
#define oTIMER_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstddef>
#include <sys/time.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *   macros;
 *--------------------------------------------------------------------*/

#define MILLISECONDS(start,timer) ((((timer).tv_sec - (start).tv_sec) * 1000) + ((timer).tv_usec - (start).tv_usec) / 1000)
#define SECONDS(start,timer) (MILLISECONDS(start,timer) / 1000)

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) otimer

{
public: 
	otimer ();
	virtual ~ otimer ();
	otimer & set (unsigned);
	otimer & reset ();
	otimer & start ();
	unsigned since ();
	bool expired ();
protected: 
private: 
	struct timeval * mstart;
	struct timeval * mclock;
	unsigned msince;
	unsigned mtimer;
};

/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif



