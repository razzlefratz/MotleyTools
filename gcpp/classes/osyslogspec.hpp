/*====================================================================*
 *
 *   osyslospecg.hpp - interface for the osyslogspec class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oSYSLOGSPEC_HEADER
#define oSYSLOGSPEC_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/oerror.hpp"
#include "../classes/types.h"

/*====================================================================*
 *    constant definitions;
 *--------------------------------------------------------------------*/

#define SYSLOG_FACILITY_MAX 20
#define SYSLOG_SEVERITY_MAX 20

#define INTERNAL_NOPRI	0x10 /* the "no priority" priority */
#define TABLE_ALLPRI    0xFF /* Value to indicate all priorities in f_pmask */
#define TABLE_NOPRI     0x00
#define	LOG_MARK	LOG_MAKEPRI(LOG_NFACILITIES, 0)  /* mark "facility" */

/*====================================================================*
 * 
 *--------------------------------------------------------------------*/

class __declspec (dllexport) osyslogspec 

{
public:
	osyslogspec ();
	virtual ~ osyslogspec ();
	static const struct _code_ facilities [];
	static const struct _code_ severities [];
	char const *decode (int flagword) const;
	int encode (char const *string) const;
	int lookup (char const *string, const struct _code_ table []) const;
private:
};


/*====================================================================*
 *   end interface declaration;
 *--------------------------------------------------------------------*/

#endif

