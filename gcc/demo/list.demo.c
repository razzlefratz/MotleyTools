/*====================================================================*
 *
 *   list.demo.c - 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <stdio.h>

#include "../list/list.h"
#include "../files/files.h"
#include "../linux/linux.h"
#include "../tools/tools.h"

#ifndef MAKEFILE
#include "../list/list.c"
#include "../tools/eprintf.c"
#include "../tools/emalloc.c"
#include "../linux/getviewport.c"
#endif

char const *program_name = "list.demo";
int main (int argc, char const *argv []) 

{
	LIST *list;
	listcreate (list, 10);

#ifdef normal

	listappend (list, "hello world");
	listappend (list, "goodbye cruel world");
	listappend (list, "make my day");
	listappend (list, "save the whale");
	listappend (list, "ban the bomb");
	listappend (list, "make my day");
	listappend (list, "hello world");
	listappend (list, "hasta la vista, baby");
	listappend (list, "make love not war");
	listappend (list, "yankee go home");
	listappend (list, "give peace a chance");
	listappend (list, "world domination");
	listappend (list, "god save the queen");
	listappend (list, "vive la difference");
	listappend (list, "vive la france");

#else

	listinsert (list, "hello world");
	listinsert (list, "goodbye cruel world");
	listinsert (list, "make my day");
	listinsert (list, "save the whale");
	listinsert (list, "ban the bomb");
	listinsert (list, "make my day");
	listinsert (list, "hello world");
	listinsert (list, "hasta la vista, baby");
	listinsert (list, "make love not war");
	listinsert (list, "yankee go home");
	listinsert (list, "give peace a chance");
	listinsert (list, "world domination");
	listinsert (list, "god save the queen");
	listinsert (list, "vive la difference");
	listinsert (list, "vive la france");

#endif

	liststatus (list, stdout);
	listdelete (list);
	listcreate (list, 20);
	listdefine (list, getenv ("PKG_CONFIG_PATH"), PATH_C_SEPARATOR);
	liststatus (list, stdout);
	return (0);
}

