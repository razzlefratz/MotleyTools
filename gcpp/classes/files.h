/*====================================================================*
 *
 *   file.h - filename function definitions and declarations;
 *
 *
 *.  published 2003 by charles maier associates limited for internal use;
 *:  modified wed 29 oct 03 by user root on host zeus;
 *;  compiled for debian gnu/linux using gcc compiler;
 *
 *--------------------------------------------------------------------*/

#ifndef FILE_HEADER
#define FILE_HEADER
 
/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
 
/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/types.h"
 
/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#define VERLIMIT_MAX 100 // file version number limit */
#define DIRLEVEL_MAX 255 // deepest directory level */ 
#define FILE_EXT_MAX 64  // */ 
 
/*====================================================================*
 *   define special characters and strings;
 *--------------------------------------------------------------------*/

#ifdef _MSC_VER
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
 *
 *--------------------------------------------------------------------*/
 
char *fullpath (char pathname [], char const *filename);
char *makepath (char pathname [], char const *basename, char const *filename);
void partpath (char const *filespec, char pathname [], char filename []);
void partfile (char const *filespec, char basename [], char extender []);
size_t splitpath (size_t count, size_t length, char const *vector [], char pathname []);
size_t mergepath (size_t count, size_t length, char const *vector []);

/*====================================================================*
 *  file open/search function prototypes;
 *--------------------------------------------------------------------*/
 
bool vfopen (char const *pathname);
bool cfopen (char const *pathname, char const *extension);
FILE *fopenparent (char const *filename, char const *openmode);
FILE *fopensearch (char const *filename, char const *openmode, char const *pathlist);
int open1 (char const *file, int oflag);
int open2 (char const *file, int oflag, char const *pathstring);

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
 *  standard filename test and compare functions;
 *--------------------------------------------------------------------*/
 
bool plain (char const *filename);
bool match (char const *filename, char const *wildcard);

/*====================================================================*
 *   end definitions and declarations;
 *--------------------------------------------------------------------*/

#endif
 

