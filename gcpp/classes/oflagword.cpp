/*====================================================================*
 *
 *   oflagword.cpp - oflagword class definition;
 *
 *   bitmapped flagword manager; this class can be inherited by other
 *   classes that need a flagword; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oFLAGWORD_SOURCE
#define oFLAGWORD_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oflagword.hpp"

/*====================================================================*
 *
 *   unsigned state () const;
 *
 *   return current flagword;
 *
 *--------------------------------------------------------------------*/

unsigned oflagword::state () const 

{
	return (this->mbits);
}


/*====================================================================*
 *
 *   oflagword & state (unsigned bits);
 *
 *   replace the current flagword;
 *
 *--------------------------------------------------------------------*/

oflagword & oflagword::state (unsigned bits) 

{
	this->mbits = bits;
	return (*this);
}


/*====================================================================*
 *
 *   unsigned getword () const;
 *
 *   return current flagword;
 *
 *--------------------------------------------------------------------*/

unsigned oflagword::getword () const 

{
	return (this->mbits);
}


/*====================================================================*
 *
 *   oflagword & setword (unsigned word);
 *
 *   replace current flagword;
 *
 *--------------------------------------------------------------------*/

oflagword & oflagword::setword (unsigned word) 

{
	this->mbits = word;
	return (*this);
}


/*====================================================================*
 *
 *   unsigned getbits (unsigned mask) const;
 *
 *   return selected flagword bits;
 *
 *--------------------------------------------------------------------*/

unsigned oflagword::getbits (unsigned mask) const 

{
	return (this->mbits & mask);
}


/*====================================================================*
 *
 *   oflagword & setbits (unsigned mask);
 *
 *   set selected flagword bits;
 *
 *--------------------------------------------------------------------*/

oflagword & oflagword::setbits (unsigned mask) 

{
	this->mbits |= mask;
	return (*this);
}


/*====================================================================*
 *
 *   oflagword & clearbits (unsigned bits);
 *
 *   clear the specified flagword bits;
 *
 *--------------------------------------------------------------------*/

oflagword & oflagword::clearbits (unsigned mask) 

{
	this->mbits &= ~mask;
	return (*this);
}


/*====================================================================*
 * 
 *   bool anyset (unsigned mask) const;
 * 
 *--------------------------------------------------------------------*/

bool oflagword::anyset (unsigned mask) const 

{
	return ((this->mbits & mask) != 0);
}


/*====================================================================*
 * 
 *   bool allset (unsigned mask) const;
 * 
 *--------------------------------------------------------------------*/

bool oflagword::allset (unsigned mask) const 

{
	return ((this->mbits & mask) == mask);
}


/*====================================================================*
 * 
 *   bool anyclear (unsigned mask) const;
 * 
 *--------------------------------------------------------------------*/

bool oflagword::anyclear (unsigned mask) const 

{
	return ((this->mbits & mask) != mask);
}


/*====================================================================*
 * 
 *   bool allclear (unsigned make) const;
 * 
 *--------------------------------------------------------------------*/

bool oflagword::allclear (unsigned mask) const 

{
	return ((this->mbits & mask) == 0);
}


/*====================================================================*
 *
 *   oflagword (unsigned word);
 *
 *--------------------------------------------------------------------*/

oflagword::oflagword (unsigned word) 

{
	this->mbits = word;
	return;
}


/*====================================================================*
 *
 *   oflagword ();
 *
 *--------------------------------------------------------------------*/

oflagword::oflagword () 

{
	this->mbits = 0;
	return;
}


/*====================================================================*
 *
 *   ~oflagword ();
 *
 *--------------------------------------------------------------------*/

oflagword::~oflagword () 

{
	return;
}


/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif

