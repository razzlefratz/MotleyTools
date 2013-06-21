/*====================================================================*
 *
 *   oHTMLElements.hpp - declaration of oHTMLElements class;
 * 
 *   this object offers compact and fast detection, lookup and retrieval
 *   for HTML element names;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oHTMLELEMENTS_HEADER
#define oHTMLELEMENTS_HEADER

/*====================================================================*
 *   custom header files;  
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/okeywords.hpp"

/*====================================================================*
 *   keyword table indexes;
 *--------------------------------------------------------------------*/

#define HTML_O_A                          0
#define HTML_O_ABBR                       1
#define HTML_O_ACRONYM                    2
#define HTML_O_ADDRESS                    3
#define HTML_O_APPLET                     4
#define HTML_O_AREA                       5
#define HTML_O_B                          6
#define HTML_O_BASE                       7
#define HTML_O_BASEFONT                   8
#define HTML_O_BDO                        9
#define HTML_O_BGSOUND                   10
#define HTML_O_BIG                       11
#define HTML_O_BLOCKQUOTE                12
#define HTML_O_BODY                      13
#define HTML_O_BR                        14
#define HTML_O_BUTTON                    15
#define HTML_O_CAPTION                   16
#define HTML_O_CENTER                    17
#define HTML_O_CITE                      18
#define HTML_O_CODE                      19
#define HTML_O_COL                       20
#define HTML_O_COLGROUP                  21
#define HTML_O_DD                        22
#define HTML_O_DEL                       23
#define HTML_O_DFN                       24
#define HTML_O_DIR                       25
#define HTML_O_DIV                       26
#define HTML_O_DL                        27
#define HTML_O_DT                        28
#define HTML_O_EM                        29
#define HTML_O_EMBED                     30
#define HTML_O_FIELDSET                  31
#define HTML_O_FONT                      32
#define HTML_O_FORM                      33
#define HTML_O_FRAME                     34
#define HTML_O_FRAMESET                  35
#define HTML_O_H1                        36
#define HTML_O_H2                        37
#define HTML_O_H3                        38
#define HTML_O_H4                        39
#define HTML_O_H5                        40
#define HTML_O_H6                        41
#define HTML_O_HEAD                      42
#define HTML_O_HR                        43
#define HTML_O_HTML                      44
#define HTML_O_I                         45
#define HTML_O_IFRAME                    46
#define HTML_O_IMG                       47
#define HTML_O_INPUT                     48
#define HTML_O_INS                       49
#define HTML_O_ISINDEX                   50
#define HTML_O_KBD                       51
#define HTML_O_LABEL                     52
#define HTML_O_LI                        53
#define HTML_O_LINK                      54
#define HTML_O_LISTING                   55
#define HTML_O_MAP                       56
#define HTML_O_MARQUEE                   57
#define HTML_O_MENU                      58
#define HTML_O_META                      59
#define HTML_O_NOFRAMES                  60
#define HTML_O_NOSCRIPT                  61
#define HTML_O_OBJECT                    62
#define HTML_O_OL                        63
#define HTML_O_OPTGROUP                  64
#define HTML_O_OPTION                    65
#define HTML_O_P                         66
#define HTML_O_PARAM                     67
#define HTML_O_PLAINTEXT                 68
#define HTML_O_PRE                       69
#define HTML_O_Q                         70
#define HTML_O_S                         71
#define HTML_O_SAMP                      72
#define HTML_O_SCRIPT                    73
#define HTML_O_SELECT                    74
#define HTML_O_SMALL                     75
#define HTML_O_SPAN                      76
#define HTML_O_STRIKE                    77
#define HTML_O_STRONG                    78
#define HTML_O_STYLE                     79
#define HTML_O_SUB                       80
#define HTML_O_SUP                       81
#define HTML_O_TABLE                     82
#define HTML_O_TBODY                     83
#define HTML_O_TD                        84
#define HTML_O_TEXTAREA                  85
#define HTML_O_TFOOT                     86
#define HTML_O_TH                        87
#define HTML_O_THEAD                     88
#define HTML_O_TITLE                     89
#define HTML_O_TR                        90
#define HTML_O_TT                        91
#define HTML_O_U                         92
#define HTML_O_UL                        93
#define HTML_O_VAR                       94
#define HTML_O_WBR                       95
#define HTML_O_XML                       96
#define HTML_O_XMP                       97
#define HTML_O_NULL                      98

/*====================================================================*
 *   class declaration; 
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oHTMLElements: public okeywords 

{
public:
	oHTMLElements ();
	virtual~ oHTMLElements ();
};


/*====================================================================*
 *   end defintion;
 *--------------------------------------------------------------------*/

#endif

