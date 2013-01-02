/*====================================================================*
 *
 *   oscantext.hpp - interface for the oscantext class;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oSCANTEXT_HEADER
#define oSCANTEXT_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <sys/types.h>
#include <fstream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/oascii.hpp"
#include "../classes/ocursor.hpp"
#include "../classes/ochrlwr.hpp"
#include "../classes/ochrupr.hpp"

/*====================================================================*
 *   class constants;
 *--------------------------------------------------------------------*/

#define oSCANTEXT_UNGET_LENGTH 512
#define oSCANTEXT_TOKEN_LENGTH 512

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oscantext: public ocursor, private oascii, private ochrupr, private ochrlwr 

{
public:
	oscantext ();
	oscantext (std::ifstream *stream);
	oscantext (char const *string);
	virtual ~ oscantext ();
	virtual oscantext & scantoken ();
	virtual oscantext & elaborate ();
	virtual oscantext & translate (char const * oldtoken, char const * newtoken);
	size_t charcount () const;
	size_t linecount () const;
	size_t pagecount () const;
	size_t rowcount () const;
	size_t colcount () const;
	size_t tokensize () const;
	char character () const;
	char tokentype () const;
	char const * tokentext ();
	char const * savetoken ();
	bool isempty () const;
	bool isspace () const;
	bool isalpha () const;
	bool isdigit () const;
	bool isalnum () const;
	bool ispunct () const;
	bool isident () const;
	bool isarith () const;
	bool islogic () const;
	bool isgroup () const;
	bool isclass (unsigned c) const;
	bool isclass (char const *charset) const;
	bool istoken (char const *literal) const;
	bool isbreak (unsigned c) const;
	bool isbreak (char const * charset) const;
	bool isbreak (bool (*) (unsigned)) const;
	bool ismatch () const;
	bool havebreak (unsigned c);
	bool havebreak (char const * charset);
	bool havebreak (bool (*) (unsigned));
	bool havematch ();
	bool haveclass (unsigned c);
	bool haveclass (char const * charset);
	bool havetoken (char const * literal);
	oscantext & operator= (char const * string);
	oscantext & copy (char const * string);
	oscantext & read (char const * filename);
	oscantext & read (std::ifstream * stream);
	oscantext & read ();
	oscantext & readtoken (char buffer [], size_t length);
	oscantext & tokentype (char c);
	oscantext & scanflush ();
	oscantext & scanspace ();
	oscantext & scanblank ();
	oscantext & scanalpha ();
	oscantext & scandigit ();
	oscantext & scanalnum ();
	oscantext & scanident ();
	oscantext & scanmatch ();
	oscantext & scanbreak ();
	oscantext & scanbreak (unsigned c);
	oscantext & scanbreak (char const *charset);
	oscantext & scanwhile ();
	oscantext & scanwhile (unsigned c);
	oscantext & scanwhile (char const *charset);
	oscantext & scanwhile (bool (*) (unsigned));
	oscantext & scanuntil ();
	oscantext & scanuntil (unsigned c);
	oscantext & scanuntil (char const *charset);
	oscantext & scanuntil (bool (*) (unsigned));
	oscantext & scanquote ();
	oscantext & scanquote (unsigned c);
	oscantext & scanquote (char const *charset);
	oscantext & scangroup (unsigned c);
	oscantext & scangroup (char const *charset);
	oscantext & scanblock ();
	oscantext & scanblock (char const *literal);
	oscantext & nexttoken ();
	oscantext & trimtoken ();
	oscantext & trimtoken (char const *charset);
	oscantext & lowercase ();
	oscantext & uppercase ();
	oscantext & enumerate ();
	oscantext & write ();
	oscantext & write (std::ofstream *stream);
	oscantext & print ();
	oscantext & print (std::ofstream *stream);
	oscantext & unget ();
	oscantext & unget (char const *string);
	oscantext & unget (char c);
	oscantext & cleanse ();
	oscantext & clear ();
protected:
private:
	oscantext & reset (off_t length);
	char mclass;
	char * mtoken;
	char * minput;
	char * mstart;
	char * mbreak;
	char * mlimit;
	char * mindex;
	size_t mwidth;
	size_t munget;
};


/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif

