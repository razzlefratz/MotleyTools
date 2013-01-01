/*====================================================================*
 *
 *   ascii.h - ASCII control character definitions;
 *
 *   symbolic definitions for ASCII control characters;
 *
 *.  Motley Tools by Charles Maier
 *:  modified sun 07 sep 03 by user root on host zeus;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef ASCII_HEADER
#define ASCII_HEADER

/*====================================================================*
 *   prevent compiler warnings;
 *--------------------------------------------------------------------*/

#ifdef NUL
#undef NUL
#endif

/*====================================================================*
 *   start definitions;
 *--------------------------------------------------------------------*/

#define NUL '\000'   /* NUL ; null, tape feed        */
#define SOH '\001'   /* SOH ; start of heading       */
#define STX '\002'   /* STX ; start of text          */
#define ETX '\003'   /* ETX ; end of text            */
#define EOT '\004'   /* EOT ; end of transmission    */
#define ENQ '\005'   /* ENQ ; enquire                */
#define ACK '\006'   /* ACK ; acknowledge            */
#define BEL '\007'   /* BEL ; bell                   */
#define BS  '\010'   /* BKS ; backspace              */
#define HT  '\011'   /* HT  ; horizontal tab         */
#define LF  '\012'   /* LF  ; line feed              */
#define VT  '\013'   /* VT  ; vertical tab           */
#define FF  '\014'   /* FF  ; form feed              */
#define CR  '\015'   /* CR  ; carriage return        */
#define SO  '\016'   /* SO  ; shift out              */
#define SI  '\017'   /* SI  ; shift in               */
#define DLE '\020'   /* DLE ; data line escape       */
#define DC1 '\021'   /* DC1 ; dev control 1          */
#define DC2 '\022'   /* DC2 ; dev control 2          */
#define DC3 '\023'   /* DC3 ; dev control 3          */
#define DC4 '\024'   /* DC4 ; dev control 4          */
#define NAK '\025'   /* NAK ; negative acknowledge   */
#define SYN '\026'   /* SYN ; synchronous idle       */
#define ETB '\027'   /* ETB ; end of xmission block  */
#define CAN '\030'   /* CAN ; cancel escape sequence */
#define EM  '\031'   /* EM  ; end of medium          */
#define SUB '\032'   /* SUB ; substitute             */
#define ESC '\033'   /* ESC ; escape                 */
#define FS  '\034'   /* FS  ; file seperator         */
#define GS  '\035'   /* GS  ; group seperator        */
#define RS  '\036'   /* RS  ; record seperator       */
#define US  '\037'   /* US  ; unit seperator         */
#define SP  '\040'   /* SP  ; space                  */
#define DEL '\177'   /* DEL ; delete                 */

/*====================================================================*
 *   end definitions;
 *--------------------------------------------------------------------*/

#endif

