/*====================================================================*
 *
 *   ocprocwords.hpp - declaration of ocprocwords class;
 *
 *   this class implements the symbol table containg C language macro 
 *   processor strings;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCPROCWORDS_HEADER
#define oCPROCWORDS_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/okeywords.hpp"

/*====================================================================*
 *   table offsets;    
 *--------------------------------------------------------------------*/

#define oCPROCWORD_O_DEFINE                    0
#define oCPROCWORD_O_ELIF                      1
#define oCPROCWORD_O_ELSE                      2
#define oCPROCWORD_O_ENDIF                     3
#define oCPROCWORD_O_ERROR                     4
#define oCPROCWORD_O_IF                        5
#define oCPROCWORD_O_IFDEF                     6
#define oCPROCWORD_O_IFNDEF                    7
#define oCPROCWORD_O_INCLUDE                   8
#define oCPROCWORD_O_LINE                      9
#define oCPROCWORD_O_PRAGMA                   10
#define oCPROCWORD_O_UNDEF                    11

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) ocprocwords: public okeywords 

{
public:
	ocprocwords ();
	~ ocprocwords ();
};

/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif

