/*====================================================================*
 *
 *   ocpluswords.hpp - declaration of ocpluswords class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCPLUSWORDS_HEADER
#define oCPLUSWORDS_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/okeywords.hpp"

/*====================================================================*
 *   table offsets;
 *--------------------------------------------------------------------*/

#define oCPLUSWORD_O___BASED                   0
#define oCPLUSWORD_O___CDECL                   1
#define oCPLUSWORD_O___DECLSPECBOOL            2
#define oCPLUSWORD_O___EXCEPTCATCH             3
#define oCPLUSWORD_O___FASTCALL                4
#define oCPLUSWORD_O___FINALLY                 5
#define oCPLUSWORD_O___INLINE                  6
#define oCPLUSWORD_O___INT16                   7
#define oCPLUSWORD_O___INT32                   8
#define oCPLUSWORD_O___INT64                   9
#define oCPLUSWORD_O___INT8                   10
#define oCPLUSWORD_O___LEAVE                  11
#define oCPLUSWORD_O___STDCALL                12
#define oCPLUSWORD_O___UUIDOF                 13
#define oCPLUSWORD_O__TRY                     14
#define oCPLUSWORD_O_AUTO                     15
#define oCPLUSWORD_O_BOOL                     16
#define oCPLUSWORD_O_BREAK                    17
#define oCPLUSWORD_O_CASE                     18
#define oCPLUSWORD_O_CHAR                     19
#define oCPLUSWORD_O_CLASS                    20
#define oCPLUSWORD_O_CONST                    21
#define oCPLUSWORD_O_CONTINUE                 22
#define oCPLUSWORD_O_DEFAULT                  23
#define oCPLUSWORD_O_DELETE                   24
#define oCPLUSWORD_O_DLLEXPORT                25
#define oCPLUSWORD_O_DLLIMPORT                26
#define oCPLUSWORD_O_DO                       27
#define oCPLUSWORD_O_DOUBLE                   28
#define oCPLUSWORD_O_DYNAMIC_CAST             29
#define oCPLUSWORD_O_ELSE                     30
#define oCPLUSWORD_O_ENTRY                    31
#define oCPLUSWORD_O_ENUM                     32
#define oCPLUSWORD_O_EXTERN                   33
#define oCPLUSWORD_O_FALSE                    34
#define oCPLUSWORD_O_FLOAT                    35
#define oCPLUSWORD_O_FOR                      36
#define oCPLUSWORD_O_FRIEND                   37
#define oCPLUSWORD_O_GOTO                     38
#define oCPLUSWORD_O_IF                       39
#define oCPLUSWORD_O_INLINE                   40
#define oCPLUSWORD_O_INT                      41
#define oCPLUSWORD_O_LONG                     42
#define oCPLUSWORD_O_MAIN                     43
#define oCPLUSWORD_O_MUTABLE                  44
#define oCPLUSWORD_O_NAKED                    45
#define oCPLUSWORD_O_NAMESPACE                46
#define oCPLUSWORD_O_NEW                      47
#define oCPLUSWORD_O_NORETURN                 48
#define oCPLUSWORD_O_OPERATOR                 49
#define oCPLUSWORD_O_PRIVATE                  50
#define oCPLUSWORD_O_PROTECTED                51
#define oCPLUSWORD_O_PUBLIC                   52
#define oCPLUSWORD_O_REGISTER                 53
#define oCPLUSWORD_O_REINTERPRET_CAST         54
#define oCPLUSWORD_O_RETURN                   55
#define oCPLUSWORD_O_SHORT                    56
#define oCPLUSWORD_O_SIGNED                   57
#define oCPLUSWORD_O_SIZEOF                   58
#define oCPLUSWORD_O_STATIC                   59
#define oCPLUSWORD_O_STATIC_CAST              60
#define oCPLUSWORD_O_STRUCT                   61
#define oCPLUSWORD_O_SWITCH                   62
#define oCPLUSWORD_O_TEMPLATE                 63
#define oCPLUSWORD_O_THIS                     64
#define oCPLUSWORD_O_THREAD                   65
#define oCPLUSWORD_O_THROW                    66
#define oCPLUSWORD_O_TRUE                     67
#define oCPLUSWORD_O_TRY                      68
#define oCPLUSWORD_O_TYPEDEF                  69
#define oCPLUSWORD_O_TYPEID                   70
#define oCPLUSWORD_O_TYPENAME                 71
#define oCPLUSWORD_O_UNION                    72
#define oCPLUSWORD_O_UNSIGNED                 73
#define oCPLUSWORD_O_USING                    74
#define oCPLUSWORD_O_UUID                     75
#define oCPLUSWORD_O_VIRTUAL                  76
#define oCPLUSWORD_O_VOID                     77
#define oCPLUSWORD_O_VOLATILE                 78
#define oCPLUSWORD_O_WHILE                    79
#define oCPLUSWORD_O_WMAIN                    80

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) ocpluswords: public okeywords 

{
public:
	ocpluswords ();
	virtual ~ ocpluswords ();
};

/*====================================================================*
 *   end declaration; 
 *--------------------------------------------------------------------*/

#endif

