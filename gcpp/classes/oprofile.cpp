/*====================================================================*
 *
 *   oprofile.cpp - interface for the oprofile class.
 *
 *   Microsoft provides a series of API function calls for reading
 *   and writing configuration files; this class provides the read
 *   interface;
 *
 *   configuration files, or profiles, have sections that contain
 *   elements that have content; section names should be, but need
 *   not be, unique with a profile; element name should be, but
 *   need not be, unique with a section; in either case, the first
 *   name is used when duplcates exist;
 *
 *   [section]
 *   element = content
 *   element = content
 *   ...
 *   [section]
 *   element = content
 *   ...
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oPROFILE_SOURCE
#define oPROFILE_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <climits>
#include <cstring>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oprofile.hpp"
#include "../classes/oascii.hpp"

/*====================================================================*
 *
 *   oprofile & write (char const * section);
 *
 *   write a profile section header to stdout;
 *
 *--------------------------------------------------------------------*/

oprofile & oprofile::write (char const * section) 

{
	std::cout << "[" << section << "]" << std::endl;
	return (* this);
}


/*====================================================================*
 *
 *   oprofile & write (char const * element, char const * content);
 *
 *   write a profile element and content to stdout; insert backslash
 *   before newlines;
 *
 *--------------------------------------------------------------------*/

oprofile & oprofile::write (char const * element, char const * content) 

{
	std::cout << element << "=";
	while (* content) 
	{
		if (* content == '\n') 
		{
			std::cout << "\\";
		}
		std::cout << * content++;
	}
	std::cout << std::endl;
	return (* this);
}


/*====================================================================*
 *
 *   char const * string (char const * profile, char const * section, char const * element, char const * content);
 *
 *   return string associated with a profile section element;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * oprofile::string (char const * profile, char const * section, char const * element, char const * content) 

{

#if CMASSOC_SAFEMODE

	if ((!profile) || (!section) || (!element)) 
	{
		return (content);
	}
#endif

	this->mstream.open (profile, std::ifstream::in);
	if (this->mstream.good ()) 
	{
		for (this->newchar (); this->mbreak != EOF; this->newline ()) 
		{
			if (this->mbreak != '[') 
			{
				continue;
			}
			this->newchar ();
			if (!this->compare (section)) 
			{
				continue;
			}
			if (this->mbreak != ']') 
			{
				continue;
			}
			for (this->newline (); this->mbreak != EOF; this->newline ()) 
			{
				if (this->mbreak == ';') 
				{
					continue;
				}
				if (!this->compare (element)) 
				{
					continue;
				}
				if (this->mbreak != '=') 
				{
					continue;
				}
				this->newchar ();
				this->newtext ();
				content = this->mbuffer;
				break;
			}
			break;
		}
	}
	this->mstream.close ();
	return (content);
}


/*====================================================================*
 *
 *   signed number (char const *profile, char const *section, char const *element, signed value);
 *
 *   retrn element value as a signed integer by converting the content
 *   string; non-numeric content returns zero;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed oprofile::number (char const * profile, char const * section, char const * element, signed value) 

{
	signed minus = 0;
	char const * string = this->string (profile, section, element, "");
	if (!* string) 
	{
		return (value);
	}
	else if (* string == '+') 
	{
		minus = 0;
		string++;
	}
	else if (* string == '-') 
	{
		minus = 1;
		string++;
	}
	value = 0;
	while (isdigit (* string)) 
	{
		value *= 10;
		value += * string++ - '0';
	}
	if (* string) 
	{
		return (0);
	}
	if (minus) 
	{
		value = -value;
	}
	return (value);
}


/*====================================================================*
 *
 *   bool enable (char const *profile, char const *section, char const *element, bool state);
 *
 *   return element content as a boolean value by searching mstate[]
 *   for the content string; strings having an even index are false;
 *   those having an odd index are true;
 *   t
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oprofile::enable (char const * profile, char const * section, char const * element, bool state) 

{
	this->string (profile, section, element, (char const *)(0));
	return (oprofile::state (this->mstring, state));
}


/*====================================================================*
 *
 *   oprofile & newtext();
 *
 *   collect the remainder of the current line in mstring; allocate
 *   as much memory as needed to hold long strings;
 *
 *   replace selected escape sequences with their equivalent value;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oprofile & oprofile:: newtext () 

{
	this->moutput = 0;
	this->mappend = 0;
	while ((this->mbreak != ';') && oascii::nobreak (this->mbreak)) 
	{
		if (this->mbreak == '\\') 
		{
			this->mbreak = this->mstream.get ();
			if (this->mbreak == 'n') 
			{
				this->mbreak = '\n';
			}
			if (this->mbreak == 't') 
			{
				this->mbreak = '\t';
			}
		}
		if (this->mappend == this->mlength) 
		{
			this->mlength = this->mlength + this->mrecord;
			this->mrecord = this->mlength - this->mrecord;
			this->mbuffer = this->mstring;
			this->mstring = new char [this->mlength];
			std::memcpy (this->mstring, this->mbuffer, this->mappend);
			delete [] this->mbuffer;
		}
		this->mstring [this->mappend++] = this->mbreak;
		if (!isblank (this->mbreak)) 
		{
			this->moutput = this->mappend;
		}
		this->mbreak = this->mstream.get ();
	}
	this->mstring [this->moutput++] = (char)(0);
	this->mbuffer = new char [this->moutput];
	std::memcpy (this->mbuffer, this->mstring, this->moutput);
	return (* this);
}


/*====================================================================*
 *
 *   bool compare (char const *string);
 *
 *   perform a case insensitive compare of string with the input and
 *   ignore embedded and trailing blank space;
 * 
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oprofile::compare (char const * string) 

{
	while (oascii::isblank (* string)) 
	{
		string++;
	}
	while ((* string) && oascii::nobreak (this->mbreak) && oascii::ismatch (* string, this->mbreak)) 
	{
		do 
		{
			string++;
		}
		while (oascii::isblank (* string));
		this->newchar ();
	}
	return (!* string);
}


/*====================================================================*
 *
 *   oprofile & newchar();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oprofile & oprofile:: newchar () 

{
	do 
	{
		this->mbreak = this->mstream.get ();
	}
	while (oascii::isblank (this->mbreak));
	return (* this);
}


/*====================================================================*
 *
 *   oprofile & newline();
 *
 *   discard the rest of the line by reading and discarding characters
 *   until a newline or EOF detected; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oprofile & oprofile:: newline () 

{
	while (oascii::nobreak (this->mbreak)) 
	{
		this->mbreak = this->mstream.get ();
	}
	this->newchar ();
	return (* this);
}


/*====================================================================*
 *
 *   oprofile() 
 *   
 *   initialize object with default buffer;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oprofile::oprofile () 

{
	this->mrecord = 256;
	this->mlength = 256;
	this->mstring = new char [this->mlength];
	this->mstring [0] = (char) (0);
	return;
}


/*====================================================================*
 *
 *   ~oprofile() 
 *   
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oprofile::~oprofile () 

{
	delete [] this->mstring;
	return;
}


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

