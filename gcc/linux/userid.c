/*====================================================================*
 *
 *   uid_t userid (char const *string);
 *
 *   convert user number or user name to equivalent numeric uid;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef USERID_SOURCE
#define USERID_SOURCE

#include <ctype.h>
#include <sys/types.h>
#include <errno.h>
#include <limits.h>
#include <pwd.h>

#include "../tools/basic.h"
#include "../tools/error.h"

uid_t userid (char const *username) 

{
	struct passwd *passwd;
	char const *string = username;
	uid_t uid;
	if ((username == (char *) (0)) || (*username == (char)(0))) 
	{
		return ((uid_t)(-1));
	}
	for (uid = 0; isdigit (*string); string++) 
	{
		uid *= 10;
		uid += *string - '0';
	}
	if (*string == (char)(0)) 
	{
		if ((passwd = getpwuid (uid)) != (struct passwd *) (0)) 
		{
			return (uid);
		}
	}
	if ((passwd = getpwnam (username)) != (struct passwd *) (0)) 
	{
		return (passwd->pw_uid);
	}
	return ((uid_t)(-1));
}


#endif

