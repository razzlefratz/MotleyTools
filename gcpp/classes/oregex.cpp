/*====================================================================*
 *
 *   oregex.cpp - implementation of the oregex class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *
 *--------------------------------------------------------------------*/

#ifndef oREGEX_SOURCE
#define oREGEX_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <iostream>
#include <cstring>
#include <climits>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oregex.hpp"

/*====================================================================*
 *
 *   char const *oregex::select(char const *string) const;
 *
 *   search the string argument for the first and longest substring
 *   that satisfies this regular expression; return a pointer to the
 *   start of that substring; all text preceding this address is the
 *   pattern prefix;
 *
 *--------------------------------------------------------------------*/

char const * oregex::select (char const * string) const

{
	if (string) while (* string)
	{
		if (size_t length = this->length (string))
		{
			char * buffer = new char [length + 1];
			strncpy (buffer, string, length);
			buffer [length] = (char) (0);
			return (buffer);
		}
		string++;
	}
	return ((char *) (0));
}

/*====================================================================*
 *
 *   char const *oregex::span(char const *string) const;
 *
 *   return a pointer to the character following the first and
 *   longest prefix of the string argument that satisfies this
 *   regular espression; all text from this address to the end
 *   of the string is the pattern suffix;
 *
 *--------------------------------------------------------------------*/

char const * oregex::span (char const * literal) const

{
	char const * minimum = literal + this->mminimum;
	char const * maximum = literal + this->mmaximum;
	char const * sp = (char *) (0);
	if (! literal)
	{
		return (literal);
	}
	while (literal < maximum)
	{
		if (! oregex::compare (this->mcharset, * literal, this->mexclude))
		{
			break;
		}
		literal++;
	}
	while (literal >= minimum)
	{
		if ((sp = this->mpattern->span (literal)))
		{
			break;
		}
		literal--;
	}
	return (sp);
}

/*====================================================================*
 *
 *   bool oregex::compare (char const * charset, char const character, bool exclude);
 *
 *   return true if the character argument is legal for this position in
 *   the regular expression; legal (or illegal) characters are specified
 *   by the mcharset string member; normally, this string enumerates all
 *   legal characters but when the exclude flags is true then enumerated
 *   characters are illegal; NUL is always illegal;
 *
 *--------------------------------------------------------------------*/

bool oregex::compare (char const * charset, char const character, bool exclude)

{
	if ((! charset) || (! character))
	{
		return (false);
	}
	while (* charset)
	{
		if (* charset++ == character)
		{
			return (! exclude);
		}
	}
	return (exclude);
}

/*====================================================================*
 *
 *   oregex & oregex::show ();
 *
 *   print the pattern chain from;
 *
 *--------------------------------------------------------------------*/

oregex & oregex::show ()

{
	std::cout << "minimum=(" << this->mminimum << ")" << std::endl;
	std::cout << "maximum=(" << this->mmaximum << ")" << std::endl;
	std::cout << "exclude=(" << this->mexclude << ")" << std::endl;
	std::cout << "any of " << REGEX_C_SRT << this->mcharset << REGEX_C_END << std::endl;
	if (this->mpattern)
	{
		this->mpattern->show ();
	}
	return (* this);
}

/*====================================================================*
 *
 *   char *oregex::fill (unsigned clower, unsigned cupper, char buffer[], size_t * length);
 *
 *   fill buffer with consecutive characters from clower through cupper;
 *   update length after each insertion; return the next unfille buffer
 *   location;
 *
 *--------------------------------------------------------------------*/

char * oregex::fill (unsigned clower, unsigned cupper, char buffer [], size_t * length)

{
	while ((clower <= cupper) && (* length > 0))
	{
		* buffer++ = clower++;
		(* length)--;
	}
	return (buffer);
}

/*====================================================================*
 *
 *   char *oregex::charset(char const *string, char const c, char *buffer, size_t length);
 *
 *   return true if the character argument is legal for this position in
 *   the regular expression; legal (or illegal) characters are specified
 *   by the mcharset string member; normally, this string enumerates all
 *   legal characters; but when the first character is REGEX_C_EXCEPT it
 *   enumerates illegal characters; character NUL is always illegal;
 *
 *--------------------------------------------------------------------*/

char const * oregex::charset (char const * string, char const close, char buffer [], size_t length)

{
	unsigned c;
	if (! string || ! buffer)
	{
		return (string);
	}
	while ((length) && (* string) && (* string != close))
	{
		* buffer = * string++;
		if (* buffer == REGEX_C_ESC)
		{
			if (* string)
			{
				* buffer = * string++;
			}
			buffer++;
			continue;
		}
		if (* string == REGEX_C_RNG)
		{
			string++;
			if (* string > * buffer)
			{
				if (oascii::islower (* buffer) && oascii::islower (* string))
				{
					buffer = oregex::fill (* buffer, * string, buffer, & length);
					continue;
				}
				if (oascii::isupper (* buffer) && oascii::isupper (* string))
				{
					buffer = oregex::fill (* buffer, * string, buffer, & length);
					continue;
				}
				if (oascii::isdigit (* buffer) && oascii::isdigit (* string))
				{
					buffer = oregex::fill (* buffer, * string, buffer, & length);
					continue;
				}
				buffer++;
				string--;
				continue;
			}
			if (* string < * buffer)
			{
				buffer++;
				string--;
				continue;
			}
			continue;
		}

#ifdef REGEX_LABEL_EXTENSIONS

		if ((* buffer == '[') && (* string == ':'))
		{
			char * symbol = buffer + 1;
			while ((* string) && (* string != ']'))
			{
				while ((* string) && (* string != ':'))
				{
					* symbol++ = * string++;
				}
				* symbol++ = * string++;
			}
			if (* string)
			{
				* symbol++ = * string++;
			}
			* symbol = (char) (0);
			if (! std::strcmp (buffer, "[:upper:]"))
			{
				buffer = fill ('A', 'Z', buffer, & length);
				continue;
			}
			if (! std::strcmp (buffer, "[:lower:]"))
			{
				buffer = fill ('a', 'z', buffer, & length);
				continue;
			}
			if (! std::strcmp (buffer, "[:digit:]"))
			{
				buffer = fill ('0', '9', buffer, & length);
				continue;
			}
			if (! std::strcmp (buffer, "[:alpha:]"))
			{
				buffer = fill ('a', 'z', buffer, & length);
				buffer = fill ('A', 'Z', buffer, & length);
				continue;
			}
			if (! std::strcmp (buffer, "[:alnum:]"))
			{
				buffer = fill ('a', 'z', buffer, & length);
				buffer = fill ('A', 'Z', buffer, & length);
				buffer = fill ('0', '9', buffer, & length);
				continue;
			}
			if (! std::strcmp (buffer, "[:xdigit:]"))
			{
				buffer = fill ('0', '9', buffer, & length);
				buffer = fill ('A', 'F', buffer, & length);
				buffer = fill ('a', 'f', buffer, & length);
				continue;
			}

#ifdef REGEX_POSIX_EXTENSIONS

			if (! std::strcmp (buffer, "[:word:]"))
			{
				buffer = fill ('_', '_', buffer, & length);
				buffer = fill ('a', 'z', buffer, & length);
				buffer = fill ('A', 'Z', buffer, & length);
				buffer = fill ('0', '9', buffer, & length);
				continue;
			}
			if (! std::strcmp (buffer, "[:blank:]"))
			{
				for (c = 0; c < (UCHAR_MAX + 1); c++)
				{
					if (oascii::isblank (c) && (length > 0))
					{
						* buffer++ = c;
						length--;
					}
				}
				continue;
			}
			if (! std::strcmp (buffer, "[:space:]"))
			{
				for (c = 0; c < (UCHAR_MAX + 1); c++)
				{
					if (oascii::isspace (c) && (length > 0))
					{
						* buffer++ = c;
						length--;
					}
				}
				continue;
			}
			if (! std::strcmp (buffer, "[:cntrl:]"))
			{
				for (c = 0; c < (UCHAR_MAX + 1); c++)
				{
					if (oascii::iscntrl (c) && (length > 0))
					{
						* buffer++ = c;
						length--;
					}
				}
				continue;
			}
			if (! std::strcmp (buffer, "[:punct:]"))
			{
				for (c = 0; c < (UCHAR_MAX + 1); c++)
				{
					if (oascii::ispunct (c) && (length > 0))
					{
						* buffer++ = c;
						length--;
					}
				}
				continue;
			}
			if (! std::strcmp (buffer, "[:print:]"))
			{
				for (c = 0; c < (UCHAR_MAX + 1); c++)
				{
					if (oascii::isprint (c) && (length > 0))
					{
						* buffer++ = c;
						length--;
					}
				}
				continue;
			}
			if (! std::strcmp (buffer, "[:graph:]"))
			{
				for (c = 0; c < (UCHAR_MAX + 1); c++)
				{
					if (oascii::isgraph (c) && (length > 0))
					{
						* buffer++ = c;
						length--;
					}
				}
				continue;
			}
			buffer = symbol;
			continue;
		}

#endif
#endif

		buffer++;
	}
	* buffer = (char) (0);
	return (string);
}

/*====================================================================*
 *
 *   oregex (char const * string);
 *
 *
 *
 *--------------------------------------------------------------------*/

oregex::oregex (char const * string)

{
	this->mcharset = new char [2];
	this->mcharset [0] = (char) (0);
	this->mcharset [1] = (char) (0);
	this->mpattern = (oregex *) (0);
	if (string == (char *) (0))
	{
		return;
	}
	if (* string == (char) (0))
	{
		return;
	}
	switch (* string)
	{
	case (char) (REGEX_C_ESC):
		if (* ++ string)
		{
			this->mexclude = false;
			this->mcharset [0] = oescape::unescape (* string);
			this->mcharset [1] = (char) (0);
			string++;
		}
		else 
		{
			this->mexclude = false;
			this->mcharset [0] = (char) (REGEX_C_ESC);
			this->mcharset [1] = (char) (0);
		}
		break;
	case REGEX_C_SRT:
		delete [] this->mcharset;
		this->mcharset = new char [UCHAR_MAX + 1];
		if (* ++ string == REGEX_C_NOT)
		{
			this->mexclude = true;
			string++;
		}
		string = oregex::charset (string, REGEX_C_END, this->mcharset, UCHAR_MAX);
		if (* string)
		{
			string++;
		}
		break;
	case REGEX_C_ANY:
		this->mexclude = true;
		this->mcharset [0] = (char) (0);
		this->mcharset [1] = (char) (0);
		string++;
		break;
	default: 
		this->mexclude = false;
		this->mcharset [0] = (char) (0);
		this->mcharset [0] = * string;
		this->mcharset [1] = (char) (0);
		string++;
		break;
	}
	switch (* string)
	{
	case REGEX_C_KLEENE_ONCE:
		this->mminimum = 0;
		this->mmaximum = 1;
		string++;
		break;
	case REGEX_C_KLEENE_STAR:
		this->mminimum = 0;
		this->mmaximum = REGEX_COUNT_MAX;
		string++;
		break;
	case REGEX_C_KLEENE_PLUS:
		this->mminimum = 1;
		this->mmaximum = REGEX_COUNT_MAX;
		string++;
		break;
	default: 
		this->mminimum = 1;
		this->mmaximum = 1;
		break;
	}
	if (* string)
	{
		this->mpattern = new oregex (string);
	}
	return;
}

/*====================================================================*
 *
 *   ~oregex ()
 *
 *
 *
 *--------------------------------------------------------------------*/

oregex::~ oregex ()

{
	delete [] this->mcharset;
	delete this->mpattern;
	return;
}

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif



