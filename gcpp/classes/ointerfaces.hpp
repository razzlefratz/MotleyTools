/*====================================================================*
 *
 *   ointerfaces.hpp - interface for the ointerfaces class  
 *
 *   host interface enumerator;
 *
 *   This software and documentation is the property of Intellon 
 *   Corporation, Ocala, Florida. It is provided 'as is' without 
 *   expressed or implied warranty of any kind to anyone for any 
 *   reason. Intellon assumes no responsibility or liability for 
 *   errors or omissions in the software or documentation and 
 *   reserves the right to make changes without notification. 
 *   
 *   Intellon customers may modify and distribute the software 
 *   without obligation to Intellon. Since use of this software 
 *   is optional, users shall bear sole responsibility and 
 *   liability for any consequences of it's use. 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *   Contributor(s): 
 *	    Charles Maier <charles.maier@intellon.com>
 *
 *--------------------------------------------------------------------*/

#ifndef oINTERFACES_HEADER
#define oINTERFACES_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/ointerface.hpp"

/*====================================================================*
 *   class constants;
 *--------------------------------------------------------------------*/

#define oINTERFACES_FILTER  1

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) ointerfaces 

{
public:
	ointerfaces ();
	virtual~ ointerfaces ();
	bool Empty (void) const;
	bool End (void) const;
	unsigned Count (void) const;
	unsigned Index (void) const;
	ointerfaces & Select (unsigned);
	ointerfaces & SelectPrev ();
	ointerfaces & SelectNext ();
	ointerfaces & SelectFirst ();
	ointerfaces & SelectFinal ();
	ointerfaces & Enumerate (void);
	ointerfaces & operator = (unsigned);
	ointerface & Selected () const;
	ointerface & Interface () const;
	ointerface & operator [] (unsigned);
private:
	ointerface ** mtable;
	unsigned mcount;
	unsigned mindex;
};

/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif

