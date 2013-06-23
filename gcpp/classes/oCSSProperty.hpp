/*====================================================================*
 *
 *   oCSSProperty.hpp - declaration of oCSSProperty class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCSSPROPERTY_HEADER
#define oCSSPROPERTY_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/okeywords.hpp"

/*====================================================================*
 *   table offsets;
 *--------------------------------------------------------------------*/

#define oCSSPROPERTY_O_AZIMUTH                       0
#define oCSSPROPERTY_O_BACKGROUND                    1
#define oCSSPROPERTY_O_BACKGROUNDATTACHMENT          2
#define oCSSPROPERTY_O_BACKGROUNDCOLOR               3
#define oCSSPROPERTY_O_BACKGROUNDIMAGE               4
#define oCSSPROPERTY_O_BACKGROUNDPOSITION            5
#define oCSSPROPERTY_O_BACKGROUNDREPEAT              6
#define oCSSPROPERTY_O_BORDER                        7
#define oCSSPROPERTY_O_BORDERBOTTOM                  8
#define oCSSPROPERTY_O_BORDERBOTTOMCOLOR             9
#define oCSSPROPERTY_O_BORDERBOTTOMSTYLE            10
#define oCSSPROPERTY_O_BORDERBOTTOMWIDTH            11
#define oCSSPROPERTY_O_BORDERCOLLAPSE               12
#define oCSSPROPERTY_O_BORDERCOLOR                  13
#define oCSSPROPERTY_O_BORDERLEFT                   14
#define oCSSPROPERTY_O_BORDERLEFTCOLOR              15
#define oCSSPROPERTY_O_BORDERLEFTSTYLE              16
#define oCSSPROPERTY_O_BORDERLEFTWIDTH              17
#define oCSSPROPERTY_O_BORDERRIGHT                  18
#define oCSSPROPERTY_O_BORDERRIGHTCOLOR             19
#define oCSSPROPERTY_O_BORDERRIGHTSTYLE             20
#define oCSSPROPERTY_O_BORDERRIGHTWIDTH             21
#define oCSSPROPERTY_O_BORDERSPACING                22
#define oCSSPROPERTY_O_BORDERSTYLE                  23
#define oCSSPROPERTY_O_BORDERTOP                    24
#define oCSSPROPERTY_O_BORDERTOPCOLOR               25
#define oCSSPROPERTY_O_BORDERTOPSTYLE               26
#define oCSSPROPERTY_O_BORDERTOPWIDTH               27
#define oCSSPROPERTY_O_BORDERWIDTH                  28
#define oCSSPROPERTY_O_BOTTOM                       29
#define oCSSPROPERTY_O_CAPTIONSIDE                  30
#define oCSSPROPERTY_O_CLEAR                        31
#define oCSSPROPERTY_O_CLIP                         32
#define oCSSPROPERTY_O_COLOR                        33
#define oCSSPROPERTY_O_CONTENT                      34
#define oCSSPROPERTY_O_COUNTERINCREMENT             35
#define oCSSPROPERTY_O_COUNTERRESET                 36
#define oCSSPROPERTY_O_CUE                          37
#define oCSSPROPERTY_O_CUEAFTER                     38
#define oCSSPROPERTY_O_CUEBEFORE                    39
#define oCSSPROPERTY_O_CURSOR                       40
#define oCSSPROPERTY_O_DIRECTION                    41
#define oCSSPROPERTY_O_DISPLAY                      42
#define oCSSPROPERTY_O_ELEVATION                    43
#define oCSSPROPERTY_O_EMPTYCELLS                   44
#define oCSSPROPERTY_O_FLOAT                        45
#define oCSSPROPERTY_O_FONT                         46
#define oCSSPROPERTY_O_FONTFAMILY                   47
#define oCSSPROPERTY_O_FONTSIZE                     48
#define oCSSPROPERTY_O_FONTSIZEADJUST               49
#define oCSSPROPERTY_O_FONTSTRETCH                  50
#define oCSSPROPERTY_O_FONTSTYLE                    51
#define oCSSPROPERTY_O_FONTVARIANT                  52
#define oCSSPROPERTY_O_FONTWEIGHT                   53
#define oCSSPROPERTY_O_HEIGHT                       54
#define oCSSPROPERTY_O_LEFT                         55
#define oCSSPROPERTY_O_LETTERSPACING                56
#define oCSSPROPERTY_O_LINEHEIGHT                   57
#define oCSSPROPERTY_O_LISTSTYLE                    58
#define oCSSPROPERTY_O_LISTSTYLEIMAGE               59
#define oCSSPROPERTY_O_LISTSTYLEPOSITION            60
#define oCSSPROPERTY_O_LISTSTYLETYPE                61
#define oCSSPROPERTY_O_MARGIN                       62
#define oCSSPROPERTY_O_MARGINBOTTOM                 63
#define oCSSPROPERTY_O_MARGINLEFT                   64
#define oCSSPROPERTY_O_MARGINRIGHT                  65
#define oCSSPROPERTY_O_MARGINTOP                    66
#define oCSSPROPERTY_O_MARKEROFFSET                 67
#define oCSSPROPERTY_O_MARKS                        68
#define oCSSPROPERTY_O_MAXHEIGHT                    69
#define oCSSPROPERTY_O_MAXWIDTH                     70
#define oCSSPROPERTY_O_MINHEIGHT                    71
#define oCSSPROPERTY_O_MINWIDTH                     72
#define oCSSPROPERTY_O_ORPHANS                      73
#define oCSSPROPERTY_O_OUTLINE                      74
#define oCSSPROPERTY_O_OUTLINECOLOR                 75
#define oCSSPROPERTY_O_OUTLINESTYLE                 76
#define oCSSPROPERTY_O_OUTLINEWIDTH                 77
#define oCSSPROPERTY_O_OVERFLOW                     78
#define oCSSPROPERTY_O_PADDING                      79
#define oCSSPROPERTY_O_PADDINGBOTTOM                80
#define oCSSPROPERTY_O_PADDINGLEFT                  81
#define oCSSPROPERTY_O_PADDINGRIGHT                 82
#define oCSSPROPERTY_O_PADDINGTOP                   83
#define oCSSPROPERTY_O_PAGE                         84
#define oCSSPROPERTY_O_PAGEBREAKAFTER               85
#define oCSSPROPERTY_O_PAGEBREAKBEFORE              86
#define oCSSPROPERTY_O_PAGEBREAKINSIDE              87
#define oCSSPROPERTY_O_PAUSE                        88
#define oCSSPROPERTY_O_PAUSEAFTER                   89
#define oCSSPROPERTY_O_PAUSEBEFORE                  90
#define oCSSPROPERTY_O_PITCH                        91
#define oCSSPROPERTY_O_PITCHRANGE                   92
#define oCSSPROPERTY_O_PLAYDURING                   93
#define oCSSPROPERTY_O_POSITION                     94
#define oCSSPROPERTY_O_QUOTES                       95
#define oCSSPROPERTY_O_RICHNESS                     96
#define oCSSPROPERTY_O_RIGHT                        97
#define oCSSPROPERTY_O_SIZE                         98
#define oCSSPROPERTY_O_SPEAK                        99
#define oCSSPROPERTY_O_SPEAKHEADER                 100
#define oCSSPROPERTY_O_SPEAKNUMERAL                101
#define oCSSPROPERTY_O_SPEAKPUNCTUATION            102
#define oCSSPROPERTY_O_SPEECHRATE                  103
#define oCSSPROPERTY_O_STRESS                      104
#define oCSSPROPERTY_O_TABLELAYOUT                 105
#define oCSSPROPERTY_O_TEXTALIGN                   106
#define oCSSPROPERTY_O_TEXTDECORATION              107
#define oCSSPROPERTY_O_TEXTINDENT                  108
#define oCSSPROPERTY_O_TEXTSHADOW                  109
#define oCSSPROPERTY_O_TEXTTRANSFORM               110
#define oCSSPROPERTY_O_TOP                         111
#define oCSSPROPERTY_O_UNICODEBIDI                 112
#define oCSSPROPERTY_O_VERTICALALIGN               113
#define oCSSPROPERTY_O_VISIBILITY                  114
#define oCSSPROPERTY_O_VOICEFAMILY                 115
#define oCSSPROPERTY_O_VOLUME                      116
#define oCSSPROPERTY_O_WHITESPACE                  117
#define oCSSPROPERTY_O_WIDOWS                      118
#define oCSSPROPERTY_O_WIDTH                       119
#define oCSSPROPERTY_O_WORDSPACING                 120
#define oCSSPROPERTY_O_ZINDEX                      121
#define oCSSPROPERTY_O_NULL                        122

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oCSSProperty: public okeywords 

{
public:
	oCSSProperty ();
	~oCSSProperty ();
};

/*====================================================================*
 *   end declaration; 
 *--------------------------------------------------------------------*/

#endif

