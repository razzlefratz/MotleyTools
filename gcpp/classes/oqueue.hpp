/*====================================================================*
 *
 *   oqueue.hpp - interface for the oqueue class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oQUEUE_HEADER
#define oQUEUE_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstddef>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oqueue 

{
public:
	oqueue ();
	oqueue (void * object);
	virtual ~ oqueue ();
	unsigned count () const;
	bool empty () const;
	void * data () const;
	oqueue * head () const;
	oqueue * tail () const;
	oqueue & clear ();
	oqueue & insert (void * object);
	oqueue & append (void * object);
	oqueue & remove ();
	oqueue & unwind ();
	oqueue & attach (oqueue * queue);
	oqueue & detach ();
private:
	oqueue * mhead;
	oqueue * mtail;
	void * mdata;
};


/*====================================================================*
 *   end class declaration;
 *--------------------------------------------------------------------*/

#endif

