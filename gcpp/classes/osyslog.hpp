/*====================================================================*
 *
 *   osyslog.hpp - interface for the osyslog class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oSYSLOG_HEADER
#define oSYSLOG_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstdarg>
#include <sys/socket.h>
#include <sys/un.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../../gcc/tools/types.h"
#include "../../gcc/linux/syslog.h"

/*====================================================================*
 *   class constants;
 *--------------------------------------------------------------------*/

#define SYSLOG_MESSAGE_MAX 1024
#define SYSLOG_LOGTIME_MAX 24
#define SYSLOG_LOGTIME_FMT "%F %T %Z"

/*====================================================================*
 * 
 *--------------------------------------------------------------------*/

class __declspec (dllexport) osyslog 

{
public:
	osyslog ();
	virtual~ osyslog ();
	osyslog & identity (char const * identity);
	osyslog & facility (unsigned facility);
	osyslog & options (unsigned options);
	char const * identity () const;
	unsigned facility () const;
	unsigned options () const;
	void syslog (unsigned priority, char const * format, ...);
	void syslogerr (unsigned priority, errno_t errnum, char const * format, ...);
	void syslogerr_at_line (unsigned priority, errno_t errnum, char const * file, size_t line, char const * format, ...);
	void vsyslog (unsigned priority, char const * format, va_list arglist);
private:
	char * midentity;
	facility_t mfacility;
	severity_t mseverity;
	flag_t moptions;
	struct sockaddr msocket;
	struct sockaddr_un msocket_un;
	bool mconnected;
	file_t mfile;
};

/*====================================================================*
 *   end interface declaration;
 *--------------------------------------------------------------------*/

#endif

