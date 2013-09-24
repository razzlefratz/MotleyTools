/*====================================================================*
 *
 *   oclangwords.hpp - declaration of oclangwords class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCLANGWORDS_HEADER
#define oCLANGWORDS_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/okeywords.hpp"

/*====================================================================*
 *   table offsets;  
 *--------------------------------------------------------------------*/

#define oCLANGWORD_O_AUTO                      0
#define oCLANGWORD_O_BREAK                     1
#define oCLANGWORD_O_CASE                      2
#define oCLANGWORD_O_CHAR                      3
#define oCLANGWORD_O_CONST                     4
#define oCLANGWORD_O_CONTINUE                  5
#define oCLANGWORD_O_DEFAULT                   6
#define oCLANGWORD_O_DO                        7
#define oCLANGWORD_O_DOUBLE                    8
#define oCLANGWORD_O_ELSE                      9
#define oCLANGWORD_O_ENTRY                    10
#define oCLANGWORD_O_ENUM                     11
#define oCLANGWORD_O_EXTERN                   12
#define oCLANGWORD_O_FLOAT                    13
#define oCLANGWORD_O_FOR                      14
#define oCLANGWORD_O_GOTO                     15
#define oCLANGWORD_O_IF                       16
#define oCLANGWORD_O_INT                      17
#define oCLANGWORD_O_LONG                     18
#define oCLANGWORD_O_REGISTER                 19
#define oCLANGWORD_O_RETURN                   20
#define oCLANGWORD_O_SHORT                    21
#define oCLANGWORD_O_SIGNED                   22
#define oCLANGWORD_O_SIZEOF                   23
#define oCLANGWORD_O_STATIC                   24
#define oCLANGWORD_O_STRUCT                   25
#define oCLANGWORD_O_SWITCH                   26
#define oCLANGWORD_O_TYPEDEF                  27
#define oCLANGWORD_O_UNION                    28
#define oCLANGWORD_O_UNSIGNED                 29
#define oCLANGWORD_O_VOID                     30
#define oCLANGWORD_O_VOLATILE                 31
#define oCLANGWORD_O_WHILE                    32

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oclangwords: public okeywords

{
public: 
	oclangwords ();
	~ oclangwords ();
};

/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif



