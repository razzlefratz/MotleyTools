/*====================================================================*
 *
 *   int valid_name (const struct dirent *d);
 *
 *   this function has been extracted from debian run-parts and
 *   re-organized to reduct the number of variables; basically,
 *   it confirms that run scripts have LSB compliant names; 
 *
 *   These regcomp tests should be moved to program init;
 *
 *--------------------------------------------------------------------*/

#include <error.h>
#include <errno.h>

signed valid_name (char const *filename, flag_t flags) 

{
	regex_t regex;
	if (_anyset (flags, RP_B_LSBSYSINIT)) 
	{
		if (regcomp (&regex, "^_?([a-z0-9_.]+-)+[a-z0-9]+$", REG_EXTENDED | REG_NOSUB)) 
		{
			error (1, errno, "internal regex compile trouble");
		}
		if (regexec (&regex, filename, 0, (regmatch_t *) (0), 0) == 0) 
		{
			regfree (&regex);
			if (regcomp (&regex, "^[a-z0-9-].*dpkg-(old|dist)$", REG_EXTENDED | REG_NOSUB)) 
			{
				error (1, errno, "internal regex compile trouble");
			}
			return (regexec (&regex, filename, 0, (regmatch_t *) (0), 0));
		}
		else 
		{
			regfree (&regex);
			if (regcomp (&regex, "^[a-z0-9][a-z0-9-]*$", REG_NOSUB)) 
			{
				error (1, errno, "internal regex compile trouble");
			}
			return (!regexec (&regex, filename, 0, (regmatch_t *) (0), 0));
		}
	}
	else 
	{
		regfree (&regex);
		if (regcomp (&regex, "^[a-zA-Z0-9_-]+$", REG_EXTENDED | REG_NOSUB)) 
		{
			error (1, errno, "internal regex compile trouble");
		}
		return (!regexec (&regex, filename, 0, (regmatch_t *) (0), 0));
	}
}

