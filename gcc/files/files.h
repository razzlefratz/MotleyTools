/*====================================================================*
 *
 *   file.h - filename function definitions and declarations;
 *
 *
 *.  Motley Tools by Charles Maier
 *:  modified wed 29 oct 03 by user root on host zeus;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef FILE_HEADER
#define FILE_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/types.h"
#include "../files/find.h"

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#define FILE_VER_MAX 100 	/* file version number limit */
#define FILE_DIR_MAX 255 	/* deepest directory level */ 
#define FILE_EXT_MAX 64 	/* longest file extension */ 

/*====================================================================*
 *   define special characters and strings;
 *--------------------------------------------------------------------*/

#ifdef WIN32
#define PATH_C_EXTENDER ('\\')
#define PATH_S_EXTENDER ("\\")
#define FILE_C_EXTENDER ('.')
#define FILE_S_EXTENDER (".")
#define FILE_C_WILDCARD ('*')
#define FILE_S_WILDCARD ("*")
#define PATH_C_SEPARATOR (';')
#define PATH_S_SEPARATOR (";")
#define FILE_C_SEPARATOR (';')
#define FILE_S_SEPARATOR (";")
#else
#define PATH_C_EXTENDER ('/')
#define PATH_S_EXTENDER ("/")
#define FILE_C_EXTENDER ('.')
#define FILE_S_EXTENDER (".")
#define FILE_C_WILDCARD ('*')
#define FILE_S_WILDCARD ("*")
#define PATH_C_SEPARATOR (':')
#define PATH_S_SEPARATOR (":")
#define FILE_C_SEPARATOR (';')
#define FILE_S_SEPARATOR (";")
#endif

/*====================================================================*
 *   file create and access modes;
 *--------------------------------------------------------------------*/

#ifndef WIN32
#define O_BINARY 0
#endif

#ifdef WIN32
#define FILE_READMODE O_BINARY|O_RDONLY
#define FILE_EDITMODE O_BINARY|O_CREAT|O_RDWR|O_EXCL
#define FILE_SAVEMODE O_BINARY|O_CREAT|O_RDWR|O_EXCL|O_TRUNC
#define FILE_FILEMODE O_BINARY|S_IREAD|S_IWRITE
#else
#define FILE_READMODE O_RDONLY
#define FILE_EDITMODE O_CREAT|O_RDWR
#define FILE_SAVEMODE O_CREAT|O_RDWR|O_TRUNC
#define FILE_FILEMODE S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH
#endif

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#define FILE_CANTOPEN "%s can't open %s", __func__
#define FILE_CANTHOME "%s can't home %s", __func__
#define FILE_CANTSIZE "%s can't size %s", __func__
#define FILE_CANTREAD "%s can't read %s", __func__
#define FILE_CANTSAVE "%s can't save %s", __func__
#define FILE_CANTSTAT "%s can't stat %s", __func__

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

char *fullpath (char pathname [], char const *filename);
char *makepath (char fullpath [], char const *basename, char const *filename);
void partpath (char const * filespec, char pathname [], char filename []);
void partfile (char const * filespec, char basename [], char extender []);
char const * pathpart (char const * string);
char const * filepart (char const * string);
char const * pathname (char const * string);
char const * filename (char const * string);
size_t splitpath (size_t count, size_t length, char const * vector [], char pathname []);
size_t mergepath (size_t count, size_t length, char const * vector []);

/*====================================================================*
 *  file open/search function prototypes;
 *--------------------------------------------------------------------*/

bool vfopen (char const *pathname);
bool cfopen (char const *pathname, char const * extension);
FILE *fopenparent (char const *filename, char const *openmode);
FILE *fopensearch (char const *filename, char const *openmode, char const *pathlist);
int openroot (char const * filename, int oflag);
int openpath (char const * filename, int oflag, char const * pathnames);
int openauth (char const * filename, char const * registry);

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

bool isdotdir (char const *filename);
bool fileexists (char const *pathname);
bool fileinfolder (char const *pathname, char const *wildcard);
bool fileinstring (char const *pathnames, char const *filename);
bool fileinvector (char const *pathnames [], char const *filename);

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

char *copypathname (char pathname [], char const *filespec);
char *copybasename (char basename [], char const *filespec);
char *copyfilename (char filename [], char const *filespec);
char *copyfiletype (char filetype [], char const *filespec);
char *setfiletype (char pathname [], char const *extension);

/*====================================================================*
 *  filename test functions;
 *--------------------------------------------------------------------*/

bool plain (char const *filename);
bool match (char const *filename, char const *wildcard);

/*====================================================================*
 *   file open functions (also declared in error.h);
 *--------------------------------------------------------------------*/

FILE *efopen (char const *pathname, char const *openmode);
FILE *efreopen (char const *pathname, char const *openmode, FILE * fp);

/*====================================================================*
 *   file mode specification functions;
 *--------------------------------------------------------------------*/

mode_t modespec (char const *string);

/*====================================================================*
 *   end definitions and declarations;
 *--------------------------------------------------------------------*/

#endif

