/*====================================================================*
 *
 *   omacro.cpp - implementation of the omacro class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oMACRO_SOURCE
#define oMACRO_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstdlib>
#include <cstring>
#include <iostream>

/*====================================================================*
 *   custom hdader files;
 *--------------------------------------------------------------------*/

#include "../classes/omacro.hpp"
#include "../classes/oscantext.hpp"

/*====================================================================*
 *   class variables;
 *--------------------------------------------------------------------*/

char const omacro::msymbol = '$';
char const omacro::mprefix = '(';
char const omacro::msuffix = ')';

/*====================================================================*
 *
 *   bool defined (char const * symbol) const;
 *
 *   return true if symbol has a current macro definition;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool omacro::defined(char const * symbol) const

{
	return (this->mfunction->defined(symbol));
}

/*====================================================================*
 *
 *   omacro & revert (char const * symbol);
 *
 *   revert to the previous definition of symbol, if any exists;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

omacro & omacro::revert(char const * symbol)

{
	this->mfunction->revert(symbol);
	return (* this);
}

/*====================================================================*
 *
 *   omacro & define (char const *string);
 *
 *   arrive here once the caller has detected a macro definition; by
 *   convention, we are sitting on the keyword "define" but it could
 *   be any word or token; we merely discard it and move on; 
 *
 *   parse a macro definition string and store it in a generic form
 *   where "$(0)" represents the macro name and "$(1)", "$(2)", and 
 *   so on, represent the macro arguments;
 *
 *   for example:
 *
 *   define abc(x,y,z) abc(z,y,x)
 *
 *   is stored as
 *  
 *   abc --> $(0)($(3),$(2),$(1))
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

omacro & omacro::define(char const * string)

{
	unsigned count = 0;
	oscantext source(string);
	source.scanblank();
	source.flush();
	source.scanident();
	this->margument->define(this->argument(count), source.tokentext());
	this->margument->define(source.tokentext(), this->argument(count++));
	if (source.havebreak('('))
	{
		do 
		{
			source.scanspace();
			source.flush();
			source.scangroup(",)");
			source.trimtoken();
			this->margument->define(source.tokentext(), this->argument(count++));
			source.scanspace();
			source.scanbreak(',');
		}
		while (! source.havebreak(')'));
	}
	source.scanblank();
	while (! source.isempty())
	{
		source.flush();
		source.scantoken();
		if (source.isclass("_A"))
		{
			source.scanident();
			this->append(this->margument->expand(source.tokentext()));
			continue;
		}
		if (source.isclass('/'))
		{
			if (source.havebreak('/'))
			{
				source.scanquote('\n');
				source.scanbreak('\n');
				continue;
			}
			if (source.havebreak('*'))
			{
				source.scanblock();
				source.scanmatch();
				continue;
			}
		}
		this->append(source.tokentext());
	}
	if (omacro::anyset(oMACRO_B_DEFINE))
	{
		std::cerr << "[DEFINE[" << string << "]]" << std::endl;
		std::cerr << "[STRING[" << this->mbuffer << "]]" << std::endl;
	}
	this->mfunction->define(this->margument->lookup(this->argument(0)), this->mbuffer);
	this->margument->clear();
	this->mextent = 0;
	return (* this);
}

/*====================================================================*
 *
 *   char const * expand (char const *string);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * omacro::expand(char const * string)

{
	unsigned count = 0;
	oscantext source(string);
	source.scanspace();
	source.flush();
	source.scanident();
	this->margument->define(this->argument(count++), source.tokentext());
	source.scanspace();
	if (source.havebreak('('))
	{
		do 
		{
			source.scanspace().flush();
			source.scangroup(",)");
			source.trimtoken();
			this->margument->define(this->argument(count++), source.tokentext());
			source.scanspace();
			source.scanbreak(',');
		}
		while (! source.havebreak(')'));
	}
	source.copy(this->mfunction->lookup(this->margument->lookup(this->argument(0))));
	while (! source.isempty())
	{
		source.flush().scantoken();
		if (source.isclass(omacro::msymbol))
		{
			source.scanbreak(omacro::mprefix);
			source.scandigit();
			source.scanbreak(omacro::msuffix);
			this->append(this->margument->expand(source.tokentext()));
			continue;
		}
		if (source.isclass("_A"))
		{
			this->append(source.scanident().tokentext());
			continue;
		}
		if (source.isclass('/'))
		{
			if (source.havebreak('/'))
			{
				source.scanuntil('\n');
				source.scanbreak('\n');
				continue;
			}
			if (source.havebreak('*'))
			{
				source.scanblock();
				source.scanmatch();
				continue;
			}
		}
		this->append(source.tokentext());
	}
	if (omacro::anyset(oMACRO_B_EXPAND))
	{
		std::cerr << "[EXPAND[" << string << "]]" << std::endl;
		std::cerr << "[STRING[" << this->mbuffer << "]]" << std::endl;
	}
	this->margument->clear();
	this->mextent = 0;
	return (this->mbuffer);
}

/*====================================================================*
 *
 *   omacro & append (char const * string);
 *
 *   append string to the end of mbuffer; expand buffer if needed to
 *   accomodate string;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

omacro & omacro::append(char const * string)

{
	if (this->mextent +  std::strlen(string) > this->mlength)
	{
		char * scratch = this->mbuffer;
		this->mlength = this->mextent +  std::strlen(string);
		this->mbuffer = new char[this->mlength + 1];
		std::strcpy(this->mbuffer, scratch);
		delete [] scratch;
	}
	while (* string)
	{
		this->mbuffer[this->mextent++] = * string++;
	}
	this->mbuffer[this->mextent] = (char)(0);
	return (* this);
}

/*====================================================================*
 *
 *   char const * argument (unsigned number) const;
 *
 *   return a string representation for the numbered macro argument; 
 *   the generic form is "$(number)" but the actual "$", "(" and ")" 
 *   symbols may be user defined;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * omacro::argument(unsigned number) const

{
	static char buffer[oMACRO_SYMBOL_LENGTH];
	char * string = buffer +  sizeof(buffer);
	* -- string = (char)(0);
	* -- string = omacro::msuffix;
	do 
	{
		* -- string = '0' + (char)(number % 10);
	}
	while (number /= 10);
	* -- string = omacro::mprefix;
	* -- string = omacro::msymbol;
	return ((char const *)(string));
}

/*====================================================================*
 *
 *   omacro & enumerate (char const * title);
 *
 *   enumerate macro definitions on stderr; definitions are listed
 *   in alphabetical order with their corresponding definitions;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

omacro & omacro::enumerate(char const * title)

{
	std::cerr << "--- " << title << " ---" << std::endl;
	this->mfunction->enumerate();
	return (* this);
}

/*====================================================================*
 *
 *   omacro & clear();
 *
 *   empty the function and argument tables and the string buffer; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

omacro & omacro::clear()

{
	this->mfunction->clear();
	this->margument->clear();
	this->mbuffer[0] = (char)(0);
	this->mextent = 0;
	return (* this);
}

/*====================================================================*
 *
 *   omacro();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

omacro::omacro()

{
	this->mfunction = new osymbol("");
	this->margument = new osymbol("");
	this->mlength = oMACRO_STRING_LENGTH;
	this->mextent = 0;
	this->mbuffer = new char[this->mlength + 1];
	this->mbuffer[0] = (char)(0);
	return;
}

/*====================================================================*
 *
 *   ~omacro();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

omacro::~ omacro()

{
	delete [] this->mbuffer;
	delete this->mfunction;
	delete this->margument;
	return;
}

/*====================================================================*
 *  end implementation;
 *--------------------------------------------------------------------*/

#endif



