/*====================================================================*
 *
 *   omonth.hpp - interface for the omonth class;
 *
 *   this object imlements an ordered list engine for oitem objects; it 
 *   is used by oroster, ocatalog and oglossary object classes to store,
 *   select and fetch information; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oMONTH_HEADER
#define oMONTH_HEADER

/*====================================================================*
 *   custom header files; 
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/oindent.hpp"
#include "../classes/odate.hpp"

/*====================================================================*
 *   interface definition;
 *--------------------------------------------------------------------*/

class __declspec(dllexport) omonth

{
public: 
	omonth ();
	omonth (signed month);
	omonth (unsigned year, signed month);
	virtual ~ omonth();
	char const * title() const;
	unsigned year() const;
	unsigned month() const;
	unsigned weekday() const;
	unsigned lastday() const;
	unsigned date(unsigned block) const;
	unsigned date(unsigned week, unsigned weekday) const;
	void encode(char buffer[], size_t length);
protected: 
private: 
	static odate mdate;
	char const * mtitle;
	unsigned mannum;
	unsigned mmonth;
	unsigned mstart;
	unsigned mlimit;
};

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif



