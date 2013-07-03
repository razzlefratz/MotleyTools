/*====================================================================*
 *
 *   oscancode.hpp - interface for oscancode class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oSCANCODE_HEADER
#define oSCANCODE_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/oscantext.hpp"
#include "../classes/ocprocwords.hpp"
#include "../classes/oclangwords.hpp"
#include "../classes/ocpluswords.hpp"
#include "../classes/oclibwords.hpp"
#include "../classes/oconstants.hpp"
#include "../classes/ofunctions.hpp"

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define CL_T_NOTHING     'B' 
#define CL_T_COMMENTS    'C' 
#define CL_T_COMPILER    'F'
#define CL_T_LANGUAGE    'G'
#define CL_T_RESERVED    'H'
#define CL_T_STANDARD    'I'
#define CL_T_VARIABLE    'J'
#define CL_T_CONSTANT    'K'
#define CL_T_FUNCTION    'L'
#define CL_T_OPERATOR    'M'
#define CL_T_SEPERATE	 'O'

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oscancode: public oscantext 

{
public:
	oscancode ();
	~ oscancode ();
	oscancode & scantoken ();
	oscancode & elaborate ();
private:
	static ocprocwords cprocword;
	static oclangwords clangword;
	static ocpluswords cplusword;
	static oconstants constant;
	static ofunctions function;
};

/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif

