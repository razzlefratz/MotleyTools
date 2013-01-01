/*====================================================================*
 *
 *   recycle.h - log file rotation utility;
 *
 *
 *.  Motley Tools by Charles Maier
 *:  compiled for debian gnu/linux environment using gcc 2.95 compiler;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef RECYCLE_HEADER
#define RECYCLE_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/types.h"
#include "../tools/sizes.h"
#include "../tools/flags.h"

/*====================================================================*
 *   constant definitions; 
 *--------------------------------------------------------------------*/

#undef RECYCLE_TRACE

#define RECYCLE_PATH_CONFIG "/etc/recycle.conf"
#define RECYCLE_PATH_SCRIPT "/tmp/recycle.XXXXXX"
#define RECYCLE_PATH_STATUS "/var/state/recycle"

#define SIGNATURE "0000-00-00 00:00:00 --- Recycle Logs V3.1\n"
#define FILENAME_FORMAT "%s/%s.%02d%s%s"

#define START_OF_WEEK 0
#define MAIL_PROGRAM "/usr/bin/mail"
#define MAIL_OPTIONS "-s"
#define COMPRESS_COMMAND "/bin/gzip"
#define COMPRESS_OPTIONS "-9"
#define COMPRESS_EXT ".gz"
#define UNCOMPRESS_COMMAND "/bin/gunzip"
#define UNCOMPRESS_OPTIONS ""
#define UNCOMPRESS_EXT ""

#define LOGSET_FLAG_MONTHLY		(1 << 0)
#define LOGSET_FLAG_WEEKLY		(1 << 1)
#define LOGSET_FLAG_DAILY		(1 << 2)
#define LOGSET_FLAG_NOTIFEMPTY		(1 << 4)
#define LOGSET_FLAG_REQUIRED		(1 << 5)
#define LOGSET_FLAG_CREATE		(1 << 6)
#define LOGSET_FLAG_COPYTRUNCATE	(1 << 7)
#define LOGSET_FLAG_COMPRESS		(1 << 8)
#define LOGSET_FLAG_DELAYCOMPRESS	(1 << 9)
#define LOGSET_FLAG_MAILFIRST		(1 << 10)
#define LOGSET_FLAG_SHAREDSCRIPTS	(1 << 11)

#define RECYCLE_B_VERBOSE          (1 << 0)
#define RECYCLE_B_RECURSE          (1 << 1)
#define RECYCLE_B_TRAVERSE         (1 << 2)
#define RECYCLE_B_FORCE            (1 << 5)
#define RECYCLE_B_CHECK            (1 << 6)

/*====================================================================*
 *   custom macro definitions;
 *--------------------------------------------------------------------*/

#ifndef isblank
#define isblank(c) (((c) == ' ') || ((c) == '\n'))
#endif

#ifndef isgroup
#define isgroup(c) (((c) == ':') || ((c) == '.'))
#endif

#ifndef isoctal
#define isoctal(c) (((c) >= '0') && ((c) <= '7'))
#endif

/*
 * for scanning purposes, options are terminated by break characters
 * and lines by newline characters; specific checks can be made when
 * necessary; 
 */

#define isbreak(c) (((c) == (char)(0)) || ((c) == '\n') || ((c) == '{') || ((c) == ';') || ((c) == '}'))
#define newline(c) (((c) == (char)(0)) || ((c) == '\n'))

/*====================================================================*
 *   datatype declarations; 
 *--------------------------------------------------------------------*/

typedef struct _scan_ 

{
	char const *file;
	size_t line;
	char *input;
	char *token;
	char *tp;
	char *sp;
	char *cp;
}

SCAN;

/*
 * holds filenames and specification details for one logset; it is initialized
 * using the default configuration and modified by configuration file options;      
 * these are stored as a circular linked list where the list head contains the 
 * default configuration;
 */

typedef struct _logset_ 

{
	struct _logset_ *next;
	char * filespec;
	char ** files;
	int nfiles;
	int file;
	flag_t flags;
	long threshold;
	short keep;
	char * folder;
	char * prescript;
	char * postscript;
	char * recipient;
	char * comp_program;
	char * comp_options;
	char * comp_ext;
	char * uncomp_program;
	char * uncomp_options;
	char * ext;
	struct stat statinfo;
	struct tm tm;
	mode_t mode;
	uid_t uid;
	gid_t gid;
	signed error;
}

LOGSET;

/*
 * holds the rotation state for each file; rotation states are currently stored as
 * a dynamically allocated array but will be converted to a linked list, thus the
 * 'next' pointer; 
 */

typedef struct _state_ 

{
	struct _state_ *next;
	char *filename;
	struct tm tm;
}

STATE;

/*
 * holds information needed to manage recycling; this forms the basis 
 * for a recycling object; initialization is done in main(); 
 */

typedef struct _recycle_ 

{
	flag_t flags;
	struct tm tm;
	char const * statefilename;
	char const * mail_program;
	char const * mail_options;
	struct _logset_ *logsets;
	struct _logset_ *logset;
	struct _state_ *states;
	size_t nstates;
	size_t state;
	signed error;
}

RECYCLE;

/*====================================================================*
 *   function declarations;  
 *--------------------------------------------------------------------*/

int configure (RECYCLE *recycle, char filename []);
int cyclelogs (RECYCLE *recycle);
int readstate (RECYCLE *recycle);
int writestate (RECYCLE *recycle);
bool findstate (RECYCLE *recycle, char const *filename);
bool makestate (RECYCLE *recycle, char const *filename);
bool due (RECYCLE *recycle);

/*====================================================================*
 *   recycle scanning functions;
 *--------------------------------------------------------------------*/

char *scanscript (SCAN *scan);
int scanlogset (SCAN *scan, RECYCLE *recycle);
int scanargs (SCAN *scan);
int scanmonthly (SCAN *scan, LOGSET *logset);
int scanweekly (SCAN *scan, LOGSET *logset);
int scandaily (SCAN *scan, LOGSET *logset);
int scancreate (SCAN *scan, LOGSET *logset);
int scansize (SCAN *scan, LOGSET *logset);

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

int copyfile (char const *source, char const *output, struct stat *statinfo, flag_t flags);
int runscript (char const *script, char const *args, flag_t flags);

/*====================================================================*
 *   end definitions and declarations;
 *--------------------------------------------------------------------*/

#endif

