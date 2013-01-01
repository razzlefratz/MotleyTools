/*====================================================================*
 *
 *   NODE * xmlopen (char const * filename);
 *
 *   nodes.h
 *
 *   open an XML file and return the parse tree root;     
 *   
 *   the entire file is read into a buffer associated with the text
 *   member in the root node; the buffer is then split into strings
 *   referenced by child nodes, forming a hierarchial string vector;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef XMLOPEN_SOURCE
#define XMLOPEN_SOURCE

#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
#include <fcntl.h>
#include <errno.h>

#include "../tools/error.h"
#include "../tools/memory.h"
#include "../files/files.h"
#include "../nodes/nodes.h"

NODE * xmlopen (char const * filename) 

{
	NODE * node = NEW (NODE);
	struct stat stat;
	signed fd;
	memset (node, 0, sizeof (NODE));
	if (lstat (filename, &stat)) 
	{
		error (1, errno, "Can't stat %s", filename);
	}
	if (!(node->text = malloc (stat.st_size + 1))) 
	{
		error (1, errno, "Can't hold %s", filename);
	}
	if ((fd = open (filename, O_BINARY|O_RDONLY)) == -1) 
	{
		error (1, errno, "Can't open %s", filename);
	}
	if (read (fd, node->text, stat.st_size) != stat.st_size) 
	{
		error (1, errno, "Can't read %s", filename);
	}
	node->text [stat.st_size] = (char)(0);
	close (fd);
	return (node);
}


#endif

