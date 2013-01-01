/*====================================================================*
 *
 *   sv_css[] -
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <stddef.h>

#define CSS_O_AZIMUTH                     0
#define CSS_O_BACKGROUND                  1
#define CSS_O_BACKGROUNDATTACHMENT        2
#define CSS_O_BACKGROUNDCOLOR             3
#define CSS_O_BACKGROUNDIMAGE             4
#define CSS_O_BACKGROUNDPOSITION          5
#define CSS_O_BACKGROUNDREPEAT            6
#define CSS_O_BORDER                      7
#define CSS_O_BORDERBOTTOM                8
#define CSS_O_BORDERBOTTOMCOLOR           9
#define CSS_O_BORDERBOTTOMSTYLE          10
#define CSS_O_BORDERBOTTOMWIDTH          11
#define CSS_O_BORDERCOLLAPSE             12
#define CSS_O_BORDERCOLOR                13
#define CSS_O_BORDERLEFT                 14
#define CSS_O_BORDERLEFTCOLOR            15
#define CSS_O_BORDERLEFTSTYLE            16
#define CSS_O_BORDERLEFTWIDTH            17
#define CSS_O_BORDERRIGHT                18
#define CSS_O_BORDERRIGHTCOLOR           19
#define CSS_O_BORDERRIGHTSTYLE           20
#define CSS_O_BORDERRIGHTWIDTH           21
#define CSS_O_BORDERSPACING              22
#define CSS_O_BORDERSTYLE                23
#define CSS_O_BORDERTOP                  24
#define CSS_O_BORDERTOPCOLOR             25
#define CSS_O_BORDERTOPSTYLE             26
#define CSS_O_BORDERTOPWIDTH             27
#define CSS_O_BORDERWIDTH                28
#define CSS_O_BOTTOM                     29
#define CSS_O_CAPTIONSIDE                30
#define CSS_O_CLEAR                      31
#define CSS_O_CLIP                       32
#define CSS_O_COLOR                      33
#define CSS_O_CONTENT                    34
#define CSS_O_COUNTERINCREMENT           35
#define CSS_O_COUNTERRESET               36
#define CSS_O_CUE                        37
#define CSS_O_CUEAFTER                   38
#define CSS_O_CUEBEFORE                  39
#define CSS_O_CURSOR                     40
#define CSS_O_DIRECTION                  41
#define CSS_O_DISPLAY                    42
#define CSS_O_ELEVATION                  43
#define CSS_O_EMPTYCELLS                 44
#define CSS_O_FLOAT                      45
#define CSS_O_FONT                       46
#define CSS_O_FONTFAMILY                 47
#define CSS_O_FONTSIZE                   48
#define CSS_O_FONTSIZEADJUST             49
#define CSS_O_FONTSTRETCH                50
#define CSS_O_FONTSTYLE                  51
#define CSS_O_FONTVARIANT                52
#define CSS_O_FONTWEIGHT                 53
#define CSS_O_HEIGHT                     54
#define CSS_O_LEFT                       55
#define CSS_O_LETTERSPACING              56
#define CSS_O_LINEHEIGHT                 57
#define CSS_O_LISTSTYLE                  58
#define CSS_O_LISTSTYLEIMAGE             59
#define CSS_O_LISTSTYLEPOSITION          60
#define CSS_O_LISTSTYLETYPE              61
#define CSS_O_MARGIN                     62
#define CSS_O_MARGINBOTTOM               63
#define CSS_O_MARGINLEFT                 64
#define CSS_O_MARGINRIGHT                65
#define CSS_O_MARGINTOP                  66
#define CSS_O_MARKEROFFSET               67
#define CSS_O_MARKS                      68
#define CSS_O_MAXHEIGHT                  69
#define CSS_O_MAXWIDTH                   70
#define CSS_O_MINHEIGHT                  71
#define CSS_O_MINWIDTH                   72
#define CSS_O_ORPHANS                    73
#define CSS_O_OUTLINE                    74
#define CSS_O_OUTLINECOLOR               75
#define CSS_O_OUTLINESTYLE               76
#define CSS_O_OUTLINEWIDTH               77
#define CSS_O_OVERFLOW                   78
#define CSS_O_PADDING                    79
#define CSS_O_PADDINGBOTTOM              80
#define CSS_O_PADDINGLEFT                81
#define CSS_O_PADDINGRIGHT               82
#define CSS_O_PADDINGTOP                 83
#define CSS_O_PAGE                       84
#define CSS_O_PAGEBREAKAFTER             85
#define CSS_O_PAGEBREAKBEFORE            86
#define CSS_O_PAGEBREAKINSIDE            87
#define CSS_O_PAUSE                      88
#define CSS_O_PAUSEAFTER                 89
#define CSS_O_PAUSEBEFORE                90
#define CSS_O_PITCH                      91
#define CSS_O_PITCHRANGE                 92
#define CSS_O_PLAYDURING                 93
#define CSS_O_POSITION                   94
#define CSS_O_QUOTES                     95
#define CSS_O_RICHNESS                   96
#define CSS_O_RIGHT                      97
#define CSS_O_SIZE                       98
#define CSS_O_SPEAK                      99
#define CSS_O_SPEAKHEADER               100
#define CSS_O_SPEAKNUMERAL              101
#define CSS_O_SPEAKPUNCTUATION          102
#define CSS_O_SPEECHRATE                103
#define CSS_O_STRESS                    104
#define CSS_O_TABLELAYOUT               105
#define CSS_O_TEXTALIGN                 106
#define CSS_O_TEXTDECORATION            107
#define CSS_O_TEXTINDENT                108
#define CSS_O_TEXTSHADOW                109
#define CSS_O_TEXTTRANSFORM             110
#define CSS_O_TOP                       111
#define CSS_O_UNICODEBIDI               112
#define CSS_O_VERTICALALIGN             113
#define CSS_O_VISIBILITY                114
#define CSS_O_VOICEFAMILY               115
#define CSS_O_VOLUME                    116
#define CSS_O_WHITESPACE                117
#define CSS_O_WIDOWS                    118
#define CSS_O_WIDTH                     119
#define CSS_O_WORDSPACING               120
#define CSS_O_ZINDEX                    121
#define CSS_O_NULL                      122

char const *sv_css [] = 

{
	"azimuth",
	"background",
	"background-attachment",
	"background-color",
	"background-image",
	"background-position",
	"background-repeat",
	"border",
	"border-bottom",
	"border-bottom-color",
	"border-bottom-style",
	"border-bottom-width",
	"border-collapse",
	"border-color",
	"border-left",
	"border-left-color",
	"border-left-style",
	"border-left-width",
	"border-right",
	"border-right-color",
	"border-right-style",
	"border-right-width",
	"border-spacing",
	"border-style",
	"border-top",
	"border-top-color",
	"border-top-style",
	"border-top-width",
	"border-width",
	"bottom",
	"caption-side",
	"clear",
	"clip",
	"color",
	"content",
	"counter-increment",
	"counter-reset",
	"cue",
	"cue-after",
	"cue-before",
	"cursor",
	"direction",
	"display",
	"elevation",
	"empty-cells",
	"float",
	"font",
	"font-family",
	"font-size",
	"font-size-adjust",
	"font-stretch",
	"font-style",
	"font-variant",
	"font-weight",
	"height",
	"left",
	"letter-spacing",
	"line-height",
	"list-style",
	"list-style-image",
	"list-style-position",
	"list-style-type",
	"margin",
	"margin-bottom",
	"margin-left",
	"margin-right",
	"margin-top",
	"marker-offset",
	"marks",
	"max-height",
	"max-width",
	"min-height",
	"min-width",
	"orphans",
	"outline",
	"outline-color",
	"outline-style",
	"outline-width",
	"overflow",
	"padding",
	"padding-bottom",
	"padding-left",
	"padding-right",
	"padding-top",
	"page",
	"page-break-after",
	"page-break-before",
	"page-break-inside",
	"pause",
	"pause-after",
	"pause-before",
	"pitch",
	"pitch-range",
	"play-during",
	"position",
	"quotes",
	"richness",
	"right",
	"size",
	"speak",
	"speak-header",
	"speak-numeral",
	"speak-punctuation",
	"speech-rate",
	"stress",
	"table-layout",
	"text-align",
	"text-decoration",
	"text-indent",
	"text-shadow",
	"text-transform",
	"top",
	"unicode-bidi",
	"vertical-align",
	"visibility",
	"voice-family",
	"volume",
	"white-space",
	"widows",
	"width",
	"word-spacing",
	"z-index",
	NULL
};

