/*====================================================================*
 *
 *   oscanfile.hpp - interface for the oscanfile class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oSCANFILE_HEADER
#define oSCANFILE_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstdio>
#include <fstream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/oascii.hpp"
#include "../classes/ochrlwr.hpp"
#include "../classes/ochrupr.hpp"
#include "../classes/ocursor.hpp"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oscanfile: public ocursor, private oascii, private ochrupr, private ochrlwr 

{
public:
	oscanfile ();
	virtual ~ oscanfile ();
	size_t charcount () const;
	size_t linecount () const;
	size_t pagecount () const;
	size_t rowcount () const;
	size_t colcount () const;
	size_t tokensize () const;
	unsigned int character () const;
	unsigned int tokentype () const;
	char const * tokentext () const;
	char const * copytoken () const;
	oscanfile & copytoken (char buffer [], size_t length);
	oscanfile & tokentype (char c);
	bool isempty () const;
	bool isspace () const;
	bool isalpha () const;
	bool isalnum () const;
	bool isdigit () const;
	bool isident () const;
	bool isbreak (signed c) const;
	bool isbreak (char const *charset) const;
	bool isclass (signed c) const;
	bool isclass (char const *charset) const;
	bool istoken (char const *literal) const;
	bool havebreak (unsigned c);
	bool havebreak (char const *charset);
	bool haveclass (signed c);
	bool haveclass (char const *charset);
	bool havetoken (char const *literal);
	oscanfile & unget (char const *string);
	oscanfile & unget (char c);
	oscanfile & scanbreak ();
	oscanfile & scanbreak (unsigned c);
	oscanfile & scanbreak (char const *charset);
	oscanfile & scanwhile ();
	oscanfile & scanwhile (unsigned c);
	oscanfile & scanwhile (char const *charset);
	oscanfile & scanspace ();
	oscanfile & scanalpha ();
	oscanfile & scanalnum ();
	oscanfile & scandigit ();
	oscanfile & scanident ();
	oscanfile & scanmatch ();
	oscanfile & scanuntil ();
	oscanfile & scanuntil (unsigned c);
	oscanfile & scanuntil (char const *charset);
	oscanfile & scantoken ();
	oscanfile & scanquote ();
	oscanfile & scanquote (unsigned c);
	oscanfile & scanquote (char const *charset);
	oscanfile & scangroup ();
	oscanfile & scangroup (unsigned c);
	oscanfile & scangroup (char const *charset);
	oscanfile & scanblock ();
	oscanfile & scanblock (char const *literal);
	oscanfile & skiptoken ();
	oscanfile & skipbreak ();
	oscanfile & skiptoken (char const *literal);
	oscanfile & skipbreak (char const *literal);
	oscanfile & trimtoken ();
	oscanfile & trimtoken (char const *charset);
	oscanfile & lowercase ();
	oscanfile & uppercase ();
	oscanfile & write ();
	oscanfile & write (std::ofstream * stream);
	oscanfile & print ();
	oscanfile & print (std::ofstream * stream);
	oscanfile & clear ();
	oscanfile & flush ();
	bool end () const;
private:
	char * mtoken;
	char * munget;
	signed mclass;
	signed mbreak;
	size_t mcount;
	size_t mblock;
	size_t mlimit;
	size_t mindex;
	size_t ucount;
	size_t ulimit;
};


/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif

