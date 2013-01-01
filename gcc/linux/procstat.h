/*====================================================================*
 *
 *   procstat.h -
 *
 *.  Motley Tools by Charles Maier
 *:  compiled for debian gnu/linux environment using gcc 2.95 compiler;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef PROCSTAT_HEADER
#define PROCSTAT_HEADER

/*====================================================================*
 *   /proc/pid/stat sizes and offsets; 
 *--------------------------------------------------------------------*/

#define PROCSTAT_MAX 512
#define PROCSTAT_CNT 45

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define PROCROOT "/proc/"
#define STATFILE "/stat"

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#define PROCSTAT_PID     0
#define PROCSTAT_NAME     1
#define PROCSTAT_MODE     2
#define PROCSTAT_PPID     3
#define PROCSTAT_PGID     4
#define PROCSTAT_SID     5
#define PROCSTAT_TTY     6
#define PROCSTAT_TPGID     7
#define PROCSTAT_FLAGS     8
#define PROCSTAT_MINFLT    9
#define PROCSTAT_CMINFLT    10
#define PROCSTAT_MAJFLT    11
#define PROCSTAT_CMAJFLT    12
#define PROCSTAT_UTIME    13
#define PROCSTAT_STIME    14
#define PROCSTAT_CUTIME    15
#define PROCSTAT_CSTIME    16
#define PROCSTAT_COUNTER    17
#define PROCSTAT_PRI    18
#define PROCSTAT_TIMEOUT    19
#define PROCSTAT_ITREALVAL    20
#define PROCSTAT_STARTTIME    21
#define PROCSTAT_VSIZE    22
#define PROCSTAT_RLIM    23
#define PROCSTAT_SRTCODE    24
#define PROCSTAT_ENDCODE    25
#define PROCSTAT_SRTSTACK    26
#define PROCSTAT_KSTKEEP    27
#define PROCSTAT_KSTKEIP    28
#define PROCSTAT_SIGNAL    29
#define PROCSTAT_BLOCKED    30
#define PROCSTAT_SIGINORE    31
#define PROCSTAT_CIGCATCH    32
#define PROCSTAT_WCHAN    33

/*====================================================================*
 *   structure used by function readproc();
 *--------------------------------------------------------------------*/

typedef struct procstat 

{
	struct procstat *next;
	struct procstat *prev;
	char *filename;
	char *basename;
	char *statname;
	ino_t ino;
	dev_t dev;
	pid_t ppid;
	pid_t pgid;
	pid_t pid;
	pid_t sid;
}

PROCSTAT;

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

void mountproc (void);
struct procstat *readproc (void);

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#endif

