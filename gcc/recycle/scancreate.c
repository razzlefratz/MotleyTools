/*====================================================================*
 *
 *   int scancreate (SCAN *scan, int *mode, uid_t *uid, gid_t *gid);
 *
 *   scan 'create' option arguments of the form: [mode] [uid][:gid]; 
 *   mode must be octal; uid and gid may be decimal or alphanumeric;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SCANCREATE_SOURCE
#define SCANCREATE_SOURCE

#include <ctype.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>

#include "../recycle/recycle.h"
#include "../tools/error.h"
#include "../tools/chars.h"

int scancreate (SCAN *scan, LOGSET *logset) 

{
	struct passwd *passwd;
	struct group *group;
	while (isblank (*scan->cp)) 
	{
		++scan->cp;
	}
	if (isoctal (*scan->cp)) 
	{
		logset->mode = (mode_t) (0);
		for (scan->sp = scan->token; isoctal (*scan->cp); *scan->sp++ = *scan->cp++) 
		{
			logset->mode <<= 3;
			logset->mode += *scan->cp - '0';
		}
		*scan->sp = (char) (0);
		if (!isblank (*scan->cp) && !isbreak (*scan->cp)) 
		{
			error (0, 0, "%s:%d create mode %s has illegal octal syntax.", scan->file, scan->line, scan->token);
			return (1);
		}
		while (isblank (*scan->cp)) 
		{
			++scan->cp;
		}
	}
	if (isalnum (*scan->cp)) 
	{
		for (scan->sp = scan->token; isalnum (*scan->cp); *scan->sp++ = *scan->cp++);
		*scan->sp = (char) (0);
		if ((passwd = getpwnam (scan->token)) == (struct passwd *) (0)) 
		{
			error (0, 0, "%s:%d user '%s' does not exist on this host.", scan->file, scan->line, scan->token);
			return (1);
		}
		logset->uid = passwd->pw_uid;
		endpwent ();
	}
	if (isgroup (*scan->cp)) 
	{
		++scan->cp;
		for (scan->sp = scan->token; isalnum (*scan->cp); *scan->sp++ = *scan->cp++);
		*scan->sp = (char) (0);
		if ((group = getgrnam (scan->token)) == (struct group *) (0)) 
		{
			error (0, 0, "%s:%d group '%s' does not exist on this host.", scan->file, scan->line, scan->token);
			return (1);
		}
		logset->gid = group->gr_gid;
		endgrent ();
	}
	return (0);
}


#endif

