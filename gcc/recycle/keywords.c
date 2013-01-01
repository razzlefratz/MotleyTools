/*====================================================================*
 *   
 *   keywords.c - recycle reserved word functions; 
 *   
 *   an alphabetical list of recycle keywords; we call svindex() 
 *   to perform a binary search on this table because that is fast
 *   but could call svfirst() to perform a linear search; 
 *
 *   all keywords included here are option names but argument names
 *   could be included, too; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef KEYWORDS_SOURCE
#define KEYWORDS_SOURCE

#include "keywords.h"

char const *keywords [LR_O_NULL+1] = 

{
	"compress",
	"compresscmd",
	"compressext",
	"compressoptions",
	"copytruncate",
	"create",
	"daily",
	"delaycompress",
	"endscript",
	"errors",
	"extension",
	"ifempty",
	"include",
	"keep",
	"mail",
	"mailfirst",
	"maillast",
	"missingok",
	"monthly",
	"nocompress",
	"nocopytruncate",
	"nocreate",
	"nodelaycompress",
	"nomail",
	"nomissingok",
	"noolddir",
	"nosharedscripts",
	"notifempty",
	"olddir",
	"optional",
	"postcycle",
	"precycle",
	"recycle",
	"required",
	"sharedscripts",
	"size",
	"tabooext",
	"uncompresscmd",
	"weekly",
	(char const *) (0)
};


#endif

