/*====================================================================*
 *
 *   files.h - filename function definitions and declarations;
 *
 *
 *.  Motley Tools by Charles Maier
 *:  compiled for debian gnu/linux environment using gcc 2.95 compiler;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef FILE_HEADER
#define FILE_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <stddef.h>
#include <sys/stat.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/types.h"

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

#define FILE_VER_MAX 100
#define FILE_DIR_MAX 255  
#define FILE_EXT_MAX 64  

#define BASENAME(sp,file,path) for((sp)=(file)=(path);(*sp)!=(char)(0);(++sp)){if((*sp)==('/')){(file)=(sp)+(1);}}

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

char *fullpath (char pathname [], char const *filename);
char *makepath (char pathname [], char const *basename, char const *filename);
void partpath (char const *filespec, char pathname [], char basename []);
void partfile (char const *filespec, char filename [], char extender []);
size_t splitpath (size_t count, size_t length, char const *vector [], char pathname []);
size_t mergepath (size_t count, size_t length, char const *vector []);

/*====================================================================*
 *  file open/search function prototypes;
 *--------------------------------------------------------------------*/

bool fopenserial (char const *pathname);
bool fopenbackup (char const *pathname, char const *extension);
FILE *fopenparent (char const *filename, char const *openmode);
FILE *fopensearch (char const *filename, char const *openmode, char const *pathlist);

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

bool fileexists (char const *pathname);
bool fileinfolder (char const *pathname, char const *wildcard);
bool fileinstring (char const *pathnames, char const *basename);
bool fileinvector (char const *pathnames [], char const *basename);
bool plain (char const *filename);
bool match (char const *filename, char const *wildcard);
bool isdotdir (char const *filename);

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

char *copypathname (char pathname [], char const *filespec);
char *copybasename (char basename [], char const *filespec);
char *copyfilename (char filename [], char const *filespec);
char *copyfiletype (char filetype [], char const *filespec);
char *makefiletype (char pathname [], char const *extension);
unsigned fileperm (char const *string);

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

signed fdcopy (int ifd, int ofd, size_t blocksize);

/*====================================================================*
 *   end definitions and declarations;
 *--------------------------------------------------------------------*/

#endif

