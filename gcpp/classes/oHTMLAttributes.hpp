/*====================================================================*
 *
 *   oHTMLAttributes.hpp - declaration of oHTMLAttributes class.
 *
 *   this object implements the detection, lookup and retrieval of HTML 
 *   attribute names;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oHTMLATTRIBUTES_HEADER
#define oHTMlATTRIBUTES_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/okeywords.hpp"

/*====================================================================*
 *   keyword table offsets;
 *--------------------------------------------------------------------*/

#define HTML_ATTR_O_ABBR                  0
#define HTML_ATTR_O_ACCEPT                1
#define HTML_ATTR_O_ACCEPT_CHARSET        2
#define HTML_ATTR_O_ACCESSKEY             3
#define HTML_ATTR_O_ACTION                4
#define HTML_ATTR_O_ALIGN                 5
#define HTML_ATTR_O_ALINK                 6
#define HTML_ATTR_O_ALT                   7
#define HTML_ATTR_O_ARCHIVE               8
#define HTML_ATTR_O_AXIS                  9
#define HTML_ATTR_O_BACKGROUND           10
#define HTML_ATTR_O_BGCOLOR              11
#define HTML_ATTR_O_BORDER               12
#define HTML_ATTR_O_BOTMARGIN            13
#define HTML_ATTR_O_CELLPADDING          14
#define HTML_ATTR_O_CELLSPACING          15
#define HTML_ATTR_O_CHAR                 16
#define HTML_ATTR_O_CHAROFF              17
#define HTML_ATTR_O_CHARSET              18
#define HTML_ATTR_O_CHECKED              19
#define HTML_ATTR_O_CITE                 20
#define HTML_ATTR_O_CLASS                21
#define HTML_ATTR_O_CLASSID              22
#define HTML_ATTR_O_CLEAR                23
#define HTML_ATTR_O_CODE                 24
#define HTML_ATTR_O_CODEBASE             25
#define HTML_ATTR_O_CODETYPE             26
#define HTML_ATTR_O_COLOR                27
#define HTML_ATTR_O_COLS                 28
#define HTML_ATTR_O_COLSPAN              29
#define HTML_ATTR_O_COMPACT              30
#define HTML_ATTR_O_CONTENT              31
#define HTML_ATTR_O_COORDS               32
#define HTML_ATTR_O_DATA                 33
#define HTML_ATTR_O_DATETIME             34
#define HTML_ATTR_O_DECLARE              35
#define HTML_ATTR_O_DEFER                36
#define HTML_ATTR_O_DIR                  37
#define HTML_ATTR_O_DISABLED             38
#define HTML_ATTR_O_ENCTYPE              39
#define HTML_ATTR_O_FACE                 40
#define HTML_ATTR_O_FOR                  41
#define HTML_ATTR_O_FRAME                42
#define HTML_ATTR_O_FRAMEBORDER          43
#define HTML_ATTR_O_HEADERS              44
#define HTML_ATTR_O_HEIGHT               45
#define HTML_ATTR_O_HREF                 46
#define HTML_ATTR_O_HREFLANG             47
#define HTML_ATTR_O_HSPACE               48
#define HTML_ATTR_O_HTTPEQUIV            49
#define HTML_ATTR_O_ID                   50
#define HTML_ATTR_O_ISMAP                51
#define HTML_ATTR_O_LABEL                52
#define HTML_ATTR_O_LANG                 53
#define HTML_ATTR_O_LANGUAGE             54
#define HTML_ATTR_O_LINK                 55
#define HTML_ATTR_O_LONGDESC             56
#define HTML_ATTR_O_MARGINHEIGHT         57
#define HTML_ATTR_O_MARGINWIDTH          58
#define HTML_ATTR_O_MAXLENGTH            59
#define HTML_ATTR_O_MEDIA                60
#define HTML_ATTR_O_METHOD               61
#define HTML_ATTR_O_MULTIPLE             62
#define HTML_ATTR_O_NAME                 63
#define HTML_ATTR_O_NOHREF               64
#define HTML_ATTR_O_NORESIZE             65
#define HTML_ATTR_O_NOSHADE              66
#define HTML_ATTR_O_NOWRAP               67
#define HTML_ATTR_O_OBJECT               68
#define HTML_ATTR_O_OL                   69
#define HTML_ATTR_O_ONBLUR               70
#define HTML_ATTR_O_ONCHANGE             71
#define HTML_ATTR_O_ONCLICK              72
#define HTML_ATTR_O_ONDBLCLICK           73
#define HTML_ATTR_O_ONFOCUS              74
#define HTML_ATTR_O_ONKEYDOWN            75
#define HTML_ATTR_O_ONKEYPRESS           76
#define HTML_ATTR_O_ONKEYUP              77
#define HTML_ATTR_O_ONMOUSEDOWN          78
#define HTML_ATTR_O_ONMOUSEMOVE          79
#define HTML_ATTR_O_ONMOUSEOUT           80
#define HTML_ATTR_O_ONMOUSEOVER          81
#define HTML_ATTR_O_ONMOUSEUP            82
#define HTML_ATTR_O_ONRESET              83
#define HTML_ATTR_O_ONSELECT             84
#define HTML_ATTR_O_ONSUBMIT             85
#define HTML_ATTR_O_ONUNLOAD             86
#define HTML_ATTR_O_PROFILE              87
#define HTML_ATTR_O_PROMPT               88
#define HTML_ATTR_O_READONLY             89
#define HTML_ATTR_O_REL                  90
#define HTML_ATTR_O_REV                  91
#define HTML_ATTR_O_ROWS                 92
#define HTML_ATTR_O_ROWSPAN              93
#define HTML_ATTR_O_RULES                94
#define HTML_ATTR_O_SCHEME               95
#define HTML_ATTR_O_SCOPE                96
#define HTML_ATTR_O_SCROLLING            97
#define HTML_ATTR_O_SELECTED             98
#define HTML_ATTR_O_SHAPE                99
#define HTML_ATTR_O_SIZE                100
#define HTML_ATTR_O_SPAN                101
#define HTML_ATTR_O_SRC                 102
#define HTML_ATTR_O_START               103
#define HTML_ATTR_O_STYLE               104
#define HTML_ATTR_O_SUMMARY             105
#define HTML_ATTR_O_TABINDEX            106
#define HTML_ATTR_O_TARGET              107
#define HTML_ATTR_O_TEXT                108
#define HTML_ATTR_O_TITLE               109
#define HTML_ATTR_O_TOPMARGIN           110
#define HTML_ATTR_O_TYPE                111
#define HTML_ATTR_O_USEMAP              112
#define HTML_ATTR_O_VALIGN              113
#define HTML_ATTR_O_VALUE               114
#define HTML_ATTR_O_VALUETYPE           115
#define HTML_ATTR_O_VERSION             116
#define HTML_ATTR_O_VLINK               117
#define HTML_ATTR_O_VSPACE              118
#define HTML_ATTR_O_WIDTH               119
#define HTML_ATTR_O_NULL                120

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oHTMLAttributes: public okeywords 

{
public:
	oHTMLAttributes ();
	virtual~ oHTMLAttributes ();
};


/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif

