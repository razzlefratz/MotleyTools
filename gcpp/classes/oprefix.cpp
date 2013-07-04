/*====================================================================*
 *
 *   oprefix.cpp - interface for the oprefix class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oPREFIX_SOURCE
#define oPREFIX_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstring>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oprefix.hpp"

/*====================================================================*
 *
 *   oprefix * lookup (char const *symbol);
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oprefix * oprefix::lookup (char const * symbol) 

{
	oprefix * prefix = this;
	while ((prefix) && (* symbol)) 
	{
		if (* symbol < prefix->msymbol) 
		{
			prefix = prefix->mprior;
			continue;
		}
		if (* symbol > prefix->msymbol) 
		{
			prefix = prefix->mafter;
			continue;
		}
		prefix = prefix->mequal;
		symbol++;
	}
	return (prefix);
}

/*====================================================================*
 *
 *   char const *assume (char const *symbol) const 
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * oprefix::assume (char const * symbol) const 

{
	const oprefix * prefix = this;
	while (prefix) 
	{
		if (* symbol) 
		{
			if (* symbol < prefix->msymbol) 
			{
				prefix = prefix->mprior;
				continue;
			}
			if (* symbol > prefix->msymbol) 
			{
				prefix = prefix->mafter;
				continue;
			}
			prefix = prefix->mequal;
			symbol++;
			continue;
		}
		while (prefix) 
		{
			if (prefix->mprior) 
			{
				prefix = (oprefix *) (0);
				continue;
			}
			if (prefix->mafter) 
			{
				prefix = (oprefix *) (0);
				continue;
			}
			if (prefix->mequal) 
			{
				prefix = prefix->mequal;
				continue;
			}
			return (prefix->mstring);
		}
	}
	return ((char *) (0));
}

/*====================================================================*
 *
 *   char const *revise (char const *symbol) const 
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * oprefix::revise (char const * symbol) const 

{
	char const * temp;
	std::cout << "[" << * symbol << "]?[" << this->msymbol << "]" << std::endl;
	if (* symbol < this->msymbol) 
	{
		std::cout << "[" << * symbol << "]<[" << this->msymbol << "]" << std::endl;
		if (this->mprior) 
		{
			temp = this->mprior->revise (symbol + 0);
		}
		else
		{
			return ((char *) ("<"));
		}
	}
	else if (* symbol > this->msymbol) 
	{
		std::cout << "[" << * symbol << "]>[" << this->msymbol << "]" << std::endl;
		if (this->mafter) 
		{
			temp = this->mafter->revise (symbol + 0);
		}
		else
		{
			return ((char *) (">"));
		}
	}
	else if (* symbol) 
	{
		std::cout << "[" << * symbol << "]=[" << this->msymbol << "]" << std::endl;
		if (this->mequal) 
		{
			temp = this->mequal->revise (symbol + 1);
		}
		else
		{
			return ((char *) ("="));
		}
	}
	else
	{
		return ((char *) ("?"));
	}
	return (temp);
}

/*====================================================================*
 *
 *   char const * prefix (char const *symbol) const 
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * oprefix::prefix (char const * symbol) const 

{
	char const * sp = symbol;
	const oprefix * prefix = this;
	while (prefix) 
	{
		if (!prefix->msymbol) 
		{
			char const * string = prefix->mafter->prefix (symbol);
			if (string) 
			{
				return (string);
			}
			char * buffer = new char [symbol - sp + 1];
			strncpy (buffer, sp, symbol - sp);
			buffer [symbol - sp] = (char) (0);
			return (buffer);
		}
		else if (* symbol < prefix->msymbol) 
		{
			prefix = prefix->mprior;
		}
		else if (* symbol > prefix->msymbol) 
		{
			prefix = prefix->mafter;
		}
		else if (* symbol) 
		{
			++symbol;
			prefix = prefix->mequal;
		}
		else break;
	}
	return ((char *) (0));
}

/*====================================================================*
 *
 *   char const *suffix (char const *symbol) const 
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * oprefix::suffix (char const * symbol) const 

{
	const oprefix * prefix = this;
	while (prefix) 
	{
		if (!prefix->msymbol) 
		{
			char const * string = prefix->mafter->suffix (symbol);
			if (string) 
			{
				return (string);
			}
			return (symbol);
		}
		else if (* symbol < prefix->msymbol) 
		{
			prefix = prefix->mprior;
		}
		else if (* symbol > prefix->msymbol) 
		{
			prefix = prefix->mafter;
		}
		else if (* symbol) 
		{
			++symbol;
			prefix = prefix->mequal;
		}
		else break;
	}
	return ((char *) (0));
}

/*====================================================================*
 *
 *   oprefix & define (char const *symbol, char const *string) 
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oprefix & oprefix::define (char const * symbol, char const * string) 

{
	oprefix * prefix = this;
	while (prefix) 
	{
		if (* symbol < prefix->msymbol) 
		{
			if (!prefix->mprior) 
			{
				prefix->mprior = new oprefix (* symbol);
			}
			prefix = prefix->mprior;
		}
		else if (* symbol > prefix->msymbol) 
		{
			if (!prefix->mafter) 
			{
				prefix->mafter = new oprefix (* symbol);
			}
			prefix = prefix->mafter;
		}
		else if (* symbol) 
		{
			symbol++;
			if (!prefix->mequal) 
			{
				prefix->mequal = new oprefix (* symbol);
			}
			prefix = prefix->mequal;
		}
		else
		{
			delete prefix->mstring;
			prefix->mstring = new char [strlen (string) + 1];
			strcpy (prefix->mstring, string);
			break;
		}
	}
	return (* this);
}

/*====================================================================*
 *
 *   oprefix & report (char *buffer, size_t length);
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oprefix & oprefix::report (char * buffer, size_t length) 

{
	static size_t column = 0;
	if (this->mprior) 
	{
		this->mprior->report (buffer, length);
	}
	buffer [column] = this->msymbol;
	if (this->mequal) 
	{
		column++;
		this->mequal->report (buffer, length);
		column--;
	}
	else
	{
		std::cout << buffer << std::endl;
	}
	if (this->mafter) 
	{
		this->mafter->report (buffer, length);
	}
	return (* this);
}

/*====================================================================*
 *
 *   oprefix (const unsigned c);
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oprefix::oprefix (const unsigned c) 

{
	msymbol = c;
	mstring = new char [1];
	mstring [0] = (char) (0);
	mprior = (oprefix *) (0);
	mequal = (oprefix *) (0);
	mafter = (oprefix *) (0);
	return;
}

/*====================================================================*
 *
 *   oprefix ();
 *   
 *   
 *--------------------------------------------------------------------*/

oprefix::oprefix () 

{
	msymbol = (char) (0);
	mstring = new char [1];
	mstring [0] = (char) (0);
	mprior = (oprefix *) (0);
	mequal = (oprefix *) (0);
	mafter = (oprefix *) (0);
	return;
}

/*====================================================================*
 *
 *   ~oprefix ();
 *   
 *   
 *--------------------------------------------------------------------*/

oprefix::~oprefix () 

{
	delete [] mstring;
	return;
}

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

