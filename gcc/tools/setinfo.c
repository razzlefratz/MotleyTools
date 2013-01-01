/*====================================================================*
 *
 *   void setinfo();
 *
 *   tools.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SETINFO_SOURCE
#define SETINFO_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "../tools/info.h"
#include "../tools/version.h"
#include "../strlib/strlib.h"
#include "../linux/linux.h"
#include "../date/date.h"

struct _info_ info;
void setinfo () 

{
	static bool init = false;
	if (!init) 
	{
		time_t now = time ((time_t *)(0));
		strftime (info.thisyear, 5, "%Y", localtime (&now));
		strftime (info.thisdate, DATETIME_MAX, DAYTIME, localtime (&now));
		strlwr (info.thisdate);
		gethostname (info.hostname, HOSTNAME_MAX);
		getusername (info.username, USERNAME_MAX, getuid ());
		sprintf (info.released, "  Released %s by %s for private use;", info.thisyear, PROJECT);
		sprintf (info.licensed, "  Licensed is %s version 2 only;", LICENSE);
		sprintf (info.packaged, "  Packaged as %s-%s.%s by %s;", PACKAGE, VERSION, RELEASE, CONTACT);
		init = true;
	}
	return;
}


#endif

