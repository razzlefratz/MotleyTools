/*====================================================================*
 *
 *   oscancode.cpp - implementation of oscancode class.
 *
 *   the oscancode class is a C Language specific descendent of the
 *   oscantext class; it detects and classifies C languge operators 
 *   and keywords; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oSCANCODE_SOURCE
#define oSCANCODE_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include <iostream>

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#include "../classes/oscancode.hpp"

/*====================================================================*
 *   class variables; 
 *--------------------------------------------------------------------*/

ocprocwords oscancode::cprocword;
oclangwords oscancode::clangword;
ocpluswords oscancode::cplusword;
oconstants oscancode::constant;
ofunctions oscancode::function;

/*====================================================================*
 *
 *   oscancode & oscancode::scantoken();
 *
 *   scan text for the next C Language token;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscancode & oscancode::scantoken () 

{
	if (this->isempty ()) 
	{
		this->flush ();
	}
	else if (this->isspace ()) 
	{
		this->tokentype (CL_T_NOTHING);
		this->scanspace ();
	}
	else if (this->isdigit ()) 
	{
		this->tokentype (CL_T_CONSTANT);
		this->scandigit ();
		if (this->istoken ("0")) 
		{
			if (this->havebreak (".")) 
			{
				this->scandigit ();
			}
			else if (this->havebreak ("xX")) 
			{
				this->scanwhile ("0123456789ABCDEFabcdef");
			}
		}
		else if (this->havebreak (".")) 
		{
			this->scandigit ();
		}
	}
	else if (this->isident ()) 
	{
		this->scanident ();
		if (oscancode::cprocword.defined (this->tokentext ())) 
		{
			this->tokentype (CL_T_COMPILER);
		}
		else if (oscancode::clangword.defined (this->tokentext ())) 
		{
			this->tokentype (CL_T_LANGUAGE);
		}
		else if (oscancode::cplusword.defined (this->tokentext ())) 
		{
			this->tokentype (CL_T_LANGUAGE);
		}
		else if (oscancode::constant.defined (this->tokentext ())) 
		{
			this->tokentype (CL_T_CONSTANT);
		}
		else if (oscancode::function.defined (this->tokentext ())) 
		{
			this->tokentype (CL_T_FUNCTION);
		}
		else 
		{
			this->tokentype (CL_T_VARIABLE);
		}
	}
#if 0

/*
 * do no treat processor statements as individual tokens; let the 
 * application handle them;
 */

	else if (this->havebreak ("#")) 
	{
		this->tokentype (CL_T_COMMAND);
		this->scanbreak ("#");
		this->scanquote ("\r\n");
		this->scanwhile ("\r\n");
	}
#endif

	else if (this->havebreak ('\"')) 
	{
		this->tokentype (CL_T_CONSTANT);
		this->scanquote ();
		this->scanmatch ();
	}
	else if (this->havebreak ('\'')) 
	{
		this->tokentype (CL_T_CONSTANT);
		this->scanquote ();
		this->scanmatch ();
	}
	else if (this->havebreak ('?')) 
	{
		this->tokentype (CL_T_OPERATOR);
		this->scanmatch ();
	}
	else if (this->havebreak (':')) 
	{
		this->tokentype (CL_T_OPERATOR);
		this->scanmatch ();
	}
	else if (this->havebreak ('+')) 
	{
		this->tokentype (CL_T_OPERATOR);
		if (this->havebreak ('+'));
		else if (this->havebreak ('='));
		else 
		{
		}
	}
	else if (this->havebreak ('-')) 
	{
		this->tokentype (CL_T_OPERATOR);
		if (this->havebreak ('-'));
		else if (this->havebreak ('='));
		else if (this->havebreak ('>'));
		else 
		{
		}
	}
	else if (this->havebreak ('*')) 
	{
		this->tokentype (CL_T_OPERATOR);
		this->scanbreak ('=');
	}
	else if (this->havebreak ('=')) 
	{
		this->tokentype (CL_T_OPERATOR);
		this->scanmatch ();
	}
	else if (this->havebreak ("!~")) 
	{
		this->tokentype (CL_T_OPERATOR);
		this->scanbreak ('=');
	}
	else if (this->havebreak ("|&<>")) 
	{
		this->tokentype (CL_T_OPERATOR);
		if (this->havebreak ('='));
		else this->scanmatch ();
	}
	else if (this->havebreak ('/')) 
	{
		if (this->havebreak ('*')) 
		{
			this->tokentype (CL_T_COMMENTS);
			this->scanblock ();
			this->scanmatch ();
		}
		else if (this->havebreak ('/')) 
		{
			this->tokentype (CL_T_COMMENTS);
			this->scanuntil ("\n");
			this->scanbreak ("\n");
		}
		else if (this->havebreak ('=')) 
		{
			this->tokentype (CL_T_OPERATOR);
		}
		else 
		{
			this->tokentype (CL_T_OPERATOR);
		}
	}
	else 
	{
		this->tokentype (CL_T_SEPERATE);
		this->scanbreak ();
	}
	return (* this);
}


/*====================================================================*
 *
 *   oscancode & elaborate();
 *
 *   scan text for C Language tokens and elaborate them;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oscancode & oscancode::elaborate () 

{
	while (!this->isempty ()) 
	{
		switch (this->nexttoken ().tokentype ()) 
		{
		case CL_T_NOTHING:
			std::cout << "[NOTHING[" << this->tokentext () << "]]" << std::endl;
			break;
		case CL_T_COMMENTS:
			std::cout << "[COMMENT[" << this->tokentext () << "]]" << std::endl;
			break;
		case CL_T_COMPILER:
			std::cout << "[COMPILER[" << this->tokentext () << "]]" << std::endl;
			break;
		case CL_T_LANGUAGE:
			std::cout << "[LANGUAGE[" << this->tokentext () << "]]" << std::endl;
			break;
		case CL_T_CONSTANT:
			std::cout << "[CONSTANT[" << this->tokentext () << "]]" << std::endl;
			break;
		case CL_T_VARIABLE:
			std::cout << "[VARIABLE[" << this->tokentext () << "]]" << std::endl;
			break;
		case CL_T_OPERATOR:
			std::cout << "[OPERATOR[" << this->tokentext () << "]]" << std::endl;
			break;
		case CL_T_FUNCTION:
			std::cout << "[FUNCTION[" << this->tokentext () << "]]" << std::endl;
			break;
		case CL_T_RESERVED:
			std::cout << "[RESERVED[" << this->tokentext () << "]]" << std::endl;
			break;
		case CL_T_STANDARD:
			std::cout << "[STANDARD[" << this->tokentext () << "]]" << std::endl;
			break;
		default:
			std::cout << "[SEPARATE[" << this->tokentext () << "]]" << std::endl;
			break;
		}
	}
	return (* this);
}


/*====================================================================*
 *
 *   oscancode ();
 *
 *--------------------------------------------------------------------*/

oscancode::oscancode () 

{
	return;
}


/*====================================================================*
 *
 *   ~ oscancode ()
 *
 *--------------------------------------------------------------------*/

oscancode::~oscancode () 

{
	return;
}


/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif

