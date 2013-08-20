/*====================================================================*
 *
 *   oascii.hpp - oascii class declaration;
 *
 *   character classification and conversion; this is a customxed
 *   and customizable implementation of the standard ctype macros 
 *   and library functions;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oASCII_HEADER
#define oASCII_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/otypes.hpp"

/*====================================================================*
 *   C Language Character Constants;
 *--------------------------------------------------------------------*/

#define oASCII_SP ' '  /* space                      */
#define oASCII_CR '\r' /* carriage return            */
#define oASCII_LF '\n' /* line feed                  */
#define oASCII_HT '\t' /* horizontal tab             */

/*====================================================================*
 *   ASCII Character Constants;
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
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oascii 

{
public:
	oascii ();
	virtual ~ oascii ();

#ifndef WIN32

	static bool isascii (signed c);

#endif

	static bool isalpha (signed c);
	static bool isupper (signed c);
	static bool islower (signed c);
	static bool isdigit (signed c);
	static bool isxdigit (signed c);
	static bool isalnum (signed c);
	static bool ispunct (signed c);
	static bool isspace (signed c);
	static bool isprint (signed c);
	static bool isgraph (signed c);
	static bool iscntrl (signed c);
	static bool isident (signed c);
	static bool isunary (signed c);
	static bool isquote (signed c);
	static bool isarith (signed c);
	static bool islogic (signed c);
	static bool isequal (signed c);
	static bool isgroup (signed c);
	static bool isbegin (signed c);
	static bool isclose (signed c);
	static bool ismoney (signed c);
	static bool isfract (signed c);
	static bool ispower (signed c);
	static bool iscomma (signed c);
	static bool isblock (signed c);
	static bool isblank (signed c);
	static bool ismatch (signed c, signed o);
	static bool isbreak (signed c);
	static bool isbreak (signed c, signed o);
	static bool nobreak (signed c);
	static bool nobreak (signed c, signed o);
	static bool nmtoken (signed c);
	static signed toupper (signed c);
	static signed tolower (signed c);
	static signed tocntrl (signed c);
	static signed todigit (signed c);

#ifndef WIN32

	static signed toascii (signed c);

#endif

	void enumerate () const;
	void matrix () const;

private:
	unsigned ctypemask (char const * ctypename) const;
	static bool isctype (signed c, unsigned mask);
	static char const * cbits [];
	static unsigned const ctype [];
	static char const * cname [];
};

/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif

