/*====================================================================*
 *
 *   _string.h - string constants, structures, functions and macros;
 *
 *.  Motley Tools by Charles Maier
 *:  modified sun 07 sep 03 by user root on host zeus;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef _STRING_HEADER
#define _STRING_HEADER

#include <stddef.h>

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

char *_strrev (char *string);
int _strcmp (char const *string1, char const *string2);
int _strncmp (char const *string1, char const *string2, size_t count);
int _strcasecmp (char const *string1, char const *string2);
char *_strcpy (char *buffer, char const *string);
char *_strcat (char *buffer, char const *string);
char *_strncpy (char *buffer, char const *string, size_t count);
char *_strncat (char *buffer, char const *string, size_t count);
char *_strdup (char const *string);
size_t _strlen (char const *string);
char *_strpbrk (char const *string, char const *charset);
size_t _strspn (char const *string, char const *charset);
size_t _strcspn (char const *string, char const *charset);
char *_strchr (char const *string, int c);
char *_strrchr (char const *string, int c);
char *_strstr (char const *buffer, char const *string);
char *_strtok (char *string, char const *charset);

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif

