/*====================================================================*
 *
 *   vtdef.h - VT100/ANSI video definitions and declarations;
 *
 *.  Motley Tools by Charles Maier
 *:  modified sun 07 sep 03 by user root on host zeus;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef VTDEF_HEADER
#define VTDEF_HEADER

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#define VT_LINES 52
#define VT_WIDTH 80
#define VT_LIMIT 1024 

#define VT_HOME       "\033[H"   /* home cursor                 */
#define VT_BASE       "\033[52;1H" /* base cursor               */
#define VT_ERASED     "\033[2J"  /* erase display               */
#define VT_ERASEL     "\033[K"	 /* erase line			*/

#define VT_NORMAL     "\033[0m"  /* display norm text           */
#define VT_ENBOLD     "\033[1m"  /* display bold text           */
#define VT_UNLINE     "\033[4m"  /* display underlined          */
#define VT_BLINK      "\033[5m"  /* display blinking text       */
#define VT_VIDEO      "\033[7m"  /* display reverse video text  */

#define VT_GRAPH      "\033(0"   /* enter graphics mode         */
#define VT_ASCII      "\033(B"   /* enter ASCII text mode       */

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#define ANSI_CUP "\033[1;1H"     /* set cursor position         */
#define ANSI_CUU "\033[1A"       /* cursor up                   */
#define ANSI_CUD "\033[1B"       /* cursor down                 */
#define ANSI_CUF "\033[1C"       /* cursor forward              */
#define ANSI_CUB "\033[1D"       /* cursor back                 */
#define ANSI_HVP "\033[1;1f"     /* hor/vert position           */
#define ANSI_DSR "\033[6n"       /* device status report        */
#define ANSI_CPR "\033[1;1R"     /* position report             */
#define ANSI_SCP "\033[s"        /* save cursor position        */
#define ANSI_RCP "\033[u"        /* restore cursor position     */
#define ANSI_ED  "\033[2J"       /* erase display; home         */
#define ANSI_EL  "\033[K"        /* erase to end-of-line        */

#define ANSI_SGR_NORM "\033[0m"  /* display norm text           */
#define ANSI_SGR_BOLD "\033[1m"  /* display bold text           */
#define ANSI_SGR_ULIN "\033[4m"  /* display underlined          */
#define ANSI_SGR_BLNK "\033[5m"  /* display blinking text       */
#define ANSI_SGR_INVS "\033[7m"  /* display reverse video text  */

#define ANSI_FMT_CUP "\033[%d;%dH" /* cursor position           */
#define ANSI_FMT_CUU "\033[%dA"    /* cursor up                 */
#define ANSI_FMT_CUD "\033[%dB"    /* cursor down               */
#define ANSI_FMT_CUF "\033[%dC"    /* cursor down               */
#define ANSI_FMT_CUB "\033[%dD"    /* cursor down               */
#define ANSI_FMT_HVP "\033[%d;%df" /* hor/vert position         */
#define ANSI_FMT_CPR "\033[%d;%dR" /* position report           */
#define ANSI_FMT_SGR "\033[%dm"    /* reverse video text        */

/*====================================================================*
 *  end of definitions
 *--------------------------------------------------------------------*/

#endif

