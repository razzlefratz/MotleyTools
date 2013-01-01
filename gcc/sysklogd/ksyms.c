/*====================================================================*
 *
 *   ksyms.c - functions for kernel address->symbol translation
 *
 *   Copyright (c) 1995, 1996  Dr. G.W. Wettstein <greg@wind.rmcc.com>
 *   Copyright (c) 1996 Enjellic Systems Development
 *   
 *   This file is part of the sysklogd package, a kernel and system log daemon.
 *   
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *   
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *   
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *--------------------------------------------------------------------*/

/*====================================================================*
 *   
 * This file contains functions which handle the translation of kernel
 * numeric addresses into symbols for the klogd utility.
 *
 * Sat Oct 28 09:00:14 CDT 1995:  Dr. Wettstein
 *	Initial Version.
 *
 * Fri Nov 24 12:50:52 CST 1995:  Dr. Wettstein
 *	Added VERBOSE_DEBUGGING define to make debugging output more
 *	manageable.
 *
 *	Added support for verification of the loaded kernel symbols.  If
 *	no version information can be be found in the mapfile a warning
 *	message is issued but translation will still take place.  This
 *	will be the default case if kernel versions < 1.3.43 are used.
 *
 *	If the symbols in the mapfile are of the same version as the kernel
 *	that is running an informative message is issued.  If the symbols
 *	in the mapfile do not match the current kernel version a warning
 *	message is issued and translation is disabled.
 *
 * Wed Dec  6 16:14:11 CST 1995:  Dr. Wettstein
 *	Added /boot/System.map to the list of symbol maps to search for.
 *	Also made this map the first item in the search list.  I am open
 *	to CONSTRUCTIVE suggestions for any additions or corrections to
 *	the list of symbol maps to search for.  Be forewarned that the
 *	list in use is the consensus agreement between myself, Linus and
 *	some package distributers.  It is a given that no list will suit
 *	everyone's taste.  If you have rabid concerns about the list
 *	please feel free to edit the system_maps array and compile your
 *	own binaries.
 *
 *	Added support for searching of the list of symbol maps.  This
 *	allows support for access to multiple symbol maps.  The theory
 *	behind this is that a production kernel may have a system map in
 *	/boot/System.map.  If a test kernel is booted this system map
 *	would be skipped in favor of one found in /usr/src/linux.
 *
 * Thu Jan 18 11:18:31 CST 1996:  Dr. Wettstein
 *	Added patch from beta-testers to allow for reading of both
 *	ELF and a.out map files.
 *
 * Wed Aug 21 09:15:49 CDT 1996:  Dr. Wettstein
 *	Reloading of kernel module symbols is now turned on by the
 *	SetParanoiaLevel function.  The default behavior is to NOT reload
 *	the kernel module symbols when a protection fault is detected.
 *
 *	Added support for freeing of the current kernel module symbols.
 *	This was necessary to support reloading of the kernel module symbols.
 *
 *	When a matching static symbol table is loaded the kernel version
 *	number is printed.
 *
 * Mon Jun  9 17:12:42 CST 1997:  Martin Schulze
 *	Added #1 and #2 to some error messages in order to being able
 *	to divide them (ulmo@Q.Net)
 *
 * Fri Jun 13 10:50:23 CST 1997:  Martin Schulze
 *	Changed definition of LookupSymbol to non-static because it is
 *	used in klogd.c, too.
 *
 * Fri Jan  9 23:00:08 CET 1998: Martin Schulze <joey@infodrom.north.de>
 *	Fixed bug that caused klogd to die if there is no System.map available.
 *
 * Sun 29 Mar 18:14:07 BST 1998: Mark Simon Phillips <M.S.Phillips@nortel.co.uk>
 *	Switched to fgets() as gets() is not buffer overrun secure.
 *
 * Mon Apr 13 18:18:45 CEST 1998: Martin Schulze <joey@infodrom.north.de>
 *	Modified loop for detecting the correct system map.  Now it won't
 *	stop if a file has been found but doesn't contain the correct map.
 *	Special thanks go go Mark Simon Phillips for the hint.
 *
 * Mon Oct 12 00:42:30 CEST 1998: Martin Schulze <joey@infodrom.north.de>
 *	Modified CheckVersion()
 *	. Use shift to decode the kernel version
 *	. Compare integers of kernel version
 *	. extract major.minor.patch from utsname.release via sscanf()
 *	The reason lays in possible use of kernel flavours which
 *	modify utsname.release but no the Version_ symbol.
 *
 * Sun Feb 21 22:27:49 EST 1999: Keith Owens <kaos@ocs.com.au>
 *	Fixed bug that caused klogd to die if there is no symbols available.
 *
 * Tue Sep 12 23:48:12 CEST 2000: Martin Schulze <joey@infodrom.ffis.de>
 *	Close symbol file in InitKsyms() when an error occurred.
 *   
 *--------------------------------------------------------------------*/

#ifndef KSYMS_SOURCE
#define KSYMS_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <string.h>
#include <malloc.h>
#include <sys/utsname.h>
#include <stdarg.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../sysklogd/ksyms.h"
#include "../linux/syslog.h"

/*====================================================================*
 *   program constants;   
 *--------------------------------------------------------------------*/

#define VERBOSE_DEBUGGING 0

/*====================================================================*
 *   program variables;   
 *--------------------------------------------------------------------*/

static int num_syms = 0;
static int i_am_paranoid = 0;
static char vstring [12];
static struct module_symbol *symbols = (struct module_symbol *)(0);
static char *system_maps [] = 

{
	"/boot/System.map",
	"/System.map",

#if defined(TEST)

	"./System.map",

#endif

	(char *) 0
};


#if defined(TEST)

int debugging;

#else

extern int debugging;

#endif

/*====================================================================*
 *   program functions;
 *--------------------------------------------------------------------*/

static char *FindSymbolFile ();
static int CheckVersion (char *version);
static int CheckMapVersion (char *fname);
static int AddSymbol (unsigned long address, char *symbol);
static void FreeSymbols ();

/*====================================================================*
 *   
 *   void SetParanoiaLevel (int level);
 *
 * Purpose:	This function is an interface function for setting the
 *		mode of loadable module symbol lookups.  Probably overkill
 *		but it does slay another global variable.
 *
 * Arguements:	(int) level
 *
 *		level:->	The amount of paranoia which is to be
 *				present when resolving kernel exceptions.
 * Return:	void
 *   
 *--------------------------------------------------------------------*/

extern void SetParanoiaLevel (int level) 

{
	i_am_paranoid = level;
	return;
}


/*====================================================================*
 *   
 *   int InitKsyms (char const *mapfile);
 *   
 * Purpose:	This function is responsible for initializing and loading
 *		the data tables used by the kernel address translations.
 *
 * Arguements:	(char *) mapfile
 *
 *			mapfile:->	A pointer to a complete path
 *					specification of the file containing
 *					the kernel map to use.
 *
 * Return:	int
 *
 *		A boolean style context is returned.  The return value will
 *		be true if initialization was successful.  False if not.
 *   
 *--------------------------------------------------------------------*/

extern int InitKsyms (char const *mapfile) 

{
	char type,
	symbol [512];
	int version = 0;
	unsigned long int address;
	FILE *sym_file;

/*
 * Check and make sure that we are starting with a clean slate. 
 */

	if (num_syms > 0) FreeSymbols ();

/*
 * Search for and open the file containing the kernel symbols.
 */

	if (mapfile != (char *) 0) 
	{
		if ((sym_file = fopen (mapfile, "r")) == (FILE *) 0) 
		{
			Syslog (LOG_WARNING, "Cannot open map file: %s.", mapfile);
			return (0);
		}
	}
	else 
	{
		if ((mapfile = FindSymbolFile ()) == (char *) 0) 
		{
			Syslog (LOG_WARNING, "Cannot find map file.");
			if (debugging) fputs ("Cannot find map file.\n", stderr);
			return (0);
		}
		if ((sym_file = fopen (mapfile, "r")) == (FILE *) 0) 
		{
			Syslog (LOG_WARNING, "Cannot open map file.");
			if (debugging) fputs ("Cannot open map file.\n", stderr);
			return (0);
		}
	}

/*
 * Read the kernel symbol table file and add entries for each
 * line.  I suspect that the use of fscanf is not really in vogue
 * but it was quick and dirty and IMHO suitable for fixed format
 * data such as this.  If anybody doesn't agree with this please
 * e-mail me a diff containing a parser with suitable political
 * correctness -- GW.
 */

	while (!feof (sym_file)) 
	{
		if (fscanf (sym_file, "%lx %c %s\n", &address, &type, symbol) != 3) 
		{
			Syslog (LOG_ERR, "Error in symbol table input (#1).");
			fclose (sym_file);
			return (0);
		}
		if (VERBOSE_DEBUGGING && debugging) fprintf (stderr, "Address: %lx, Type: %c, Symbol: %s\n", address, type, symbol);
		if (AddSymbol (address, symbol) == 0) 
		{
			Syslog (LOG_ERR, "Error adding symbol - %s.", symbol);
			fclose (sym_file);
			return (0);
		}
		if (version == 0) version = CheckVersion (symbol);
	}
	Syslog (SYSLOG_INFO, "Loaded %d symbols from %s.", num_syms, mapfile);
	switch (version) 
	{
	case -1:
		Syslog (LOG_WARNING, "Symbols do not match kernel version.");
		num_syms = 0;
		break;
	case 0:
		Syslog (LOG_WARNING, "Cannot verify that symbols match kernel version.");
		break;
	case 1:
		Syslog (SYSLOG_INFO, "Symbols match kernel version %s.", vstring);
		break;
	}
	fclose (sym_file);
	return (1);
}


/*====================================================================*
 *   
 *   char *FindSymbolFile ();
 *   
 * Purpose:	This function is responsible for encapsulating the search
 *		for a valid symbol file.  Encapsulating the search for
 *		the map file in this function allows an intelligent search
 *		process to be implemented.
 *
 *		The list of symbol files will be searched until either a
 *		symbol file is found whose version matches the currently
 *		executing kernel or the end of the list is encountered.  If
 *		the end of the list is encountered the first available
 *		symbol file is returned to the caller.
 *
 *		This strategy allows klogd to locate valid symbol files
 *		for both a production and an experimental kernel.  For
 *		example a map for a production kernel could be installed
 *		in /boot.  If an experimental kernel is loaded the map
 *		in /boot will be skipped and the map in /usr/src/linux would
 *		be used if its version number matches the executing kernel.
 *
 * Arguements:	None specified.
 *
 * Return:	char *
 *
 *		If a valid system map cannot be located a null pointer
 *		is returned to the caller.
 *
 *		If the search is succesful a pointer is returned to the
 *		caller which points to the name of the file containing
 *		the symbol table to be used.
 *
 *--------------------------------------------------------------------*/

static char *FindSymbolFile () 

{
	char *file = (char *) 0,
	**mf = system_maps;
	struct utsname utsname;
	static char symfile [100];
	FILE *sym_file = (FILE *) 0;
	if (uname (&utsname) < 0) 
	{
		Syslog (LOG_ERR, "Cannot get kernel version information.");
		return (0);
	}
	if (debugging) fputs ("Searching for symbol map.\n", stderr);
	for (mf = system_maps; *mf != (char *) 0 && file == (char *) 0; ++mf) 
	{
		sprintf (symfile, "%s-%s", *mf, utsname.release);
		if (debugging) fprintf (stderr, "Trying %s.\n", symfile);
		if ((sym_file = fopen (symfile, "r")) != (FILE *) 0) 
		{
			if (CheckMapVersion (symfile) == 1) file = symfile;
		}
		if (sym_file == (FILE *) 0 || file == (char *) 0) 
		{
			sprintf (symfile, "%s", *mf);
			if (debugging) fprintf (stderr, "Trying %s.\n", symfile);
			if ((sym_file = fopen (symfile, "r")) != (FILE *) 0) 
			{
				if (CheckMapVersion (symfile) == 1) file = symfile;
			}
		}
	}

/*
 * At this stage of the game we are at the end of the symbol
 * tables.
 */

	if (debugging) fprintf (stderr, "End of search list encountered.\n");
	return (file);
}


/*====================================================================*
 *   
 *   int CheckVersion (char *version);
 *   
 * Purpose:	This function is responsible for determining whether or
 *		the system map being loaded matches the version of the
 *		currently running kernel.
 *
 *		The kernel version is checked by examing a variable which
 *		is of the form:	_Version_66347 (a.out) or Version_66437 (ELF).
 *
 *		The suffix of this variable is the current kernel version
 *		of the kernel encoded in base 256.  For example the
 *		above variable would be decoded as:
 *
 *			(66347 = 1*65536 + 3*256 + 43 = 1.3.43)
 *
 *		(Insert appropriate deities here) help us if Linus ever
 *		needs more than 255 patch levels to get a kernel out the
 *		door... :-)
 *
 * Arguements:	(char *) version
 *
 *			version:->	A pointer to the string which
 *					is to be decoded as a kernel
 *					version variable.
 *
 * Return:	int
 *
 *		       -1:->	The currently running kernel version does
 *				not match this version string.
 *
 *			0:->	The string is not a kernel version variable.
 *
 *			1:->	The executing kernel is of the same version
 *				as the version string.
 *
 *--------------------------------------------------------------------*/

static int CheckVersion (char *version) 

{
	int vnum,
	major,
	minor,
	patch;

#ifndef TESTING

	int kvnum;
	struct utsname utsname;

#endif

	static char *prefix = 
	{
		"Version_"
	};

/*
 * Early return if there is no hope. 
 */

/* ELF */

/* a.out */

	if (strncmp (version, prefix, strlen (prefix)) == 0 || (*version == '_' && strncmp (++version, prefix, strlen (prefix)) == 0));
	else return (0);

/*
 * Since the symbol looks like a kernel version we can start
 * things out by decoding the version string into its component
 * parts.
 */

	vnum = atoi (version + strlen (prefix));
	patch = vnum & 0x000000FF;
	minor = (vnum >> 8) & 0x000000FF;
	major = (vnum >> 16) & 0x000000FF;
	if (debugging) fprintf (stderr, "Version string = %s, Major = %d, Minor = %d, Patch = %d.\n", version + strlen (prefix), major, minor, patch);
	sprintf (vstring, "%d.%d.%d", major, minor, patch);

#ifndef TESTING

/*
 * We should now have the version string in the vstring variable in
 * the same format that it is stored in by the kernel.  We now
 * ask the kernel for its version information and compare the two
 * values to determine if our system map matches the kernel
 * version level.
 */

	if (uname (&utsname) < 0) 
	{
		Syslog (LOG_ERR, "Cannot get kernel version information.");
		return (0);
	}
	if (debugging) fprintf (stderr, "Comparing kernel %s with symbol table %s.\n", utsname.release, vstring);
	if (sscanf (utsname.release, "%d.%d.%d", &major, &minor, &patch) < 3) 
	{
		Syslog (LOG_ERR, "Kernel send bogus release string `%s'.", utsname.release);
		return (0);
	}

/*
 * Compute the version code from data sent by the kernel 
 */

	kvnum = (major << 16) | (minor << 8) | patch;

/*
 * Failure. 
 */

	if (vnum != kvnum) return (-1);

/*
 * Success. 
 */

#endif

	return (1);
}


/*====================================================================*
 *   
 *   static int CheckMapVersion (char *fname);
 *
 * Purpose:	This function is responsible for determining whether or
 *		the system map being loaded matches the version of the
 *		currently running kernel.  It uses CheckVersion as
 *		backend.
 *
 * Arguements:	(char *) fname
 *
 *			fname:->	A pointer to the string which
 *					references the system map file to
 *					be used.
 *
 * Return:	int
 *
 *		       -1:->	The currently running kernel version does
 *				not match the version in the given file.
 *
 *			0:->	No system map file or no version information.
 *
 *			1:->	The executing kernel is of the same version
 *				as the version of the map file.
 *   
 *--------------------------------------------------------------------*/

static int CheckMapVersion (char *fname) 

{
	FILE *sym_file;
	unsigned long int address;
	char symbol [512];
	char type;
	int version;
	if ((sym_file = fopen (fname, "r")) != (FILE *) 0) 
	{

/*
 * At this point a map file was successfully opened.  We
 * now need to search this file and look for version
 * information.
 */

		Syslog (SYSLOG_INFO, "Inspecting %s", fname);
		version = 0;
		while (!feof (sym_file) && (version == 0)) 
		{
			if (fscanf (sym_file, "%lx %c %s\n", &address, &type, symbol) != 3) 
			{
				Syslog (LOG_ERR, "Error in symbol table input (#2).");
				fclose (sym_file);
				return (0);
			}
			if (VERBOSE_DEBUGGING && debugging) fprintf (stderr, "Address: %lx, Type: %c, Symbol: %s\n", address, type, symbol);
			version = CheckVersion (symbol);
		}
		fclose (sym_file);
		switch (version) 
		{
		case -1:
			Syslog (LOG_ERR, "Symbol table has incorrect version number.\n");
			break;
		case 0:
			if (debugging) fprintf (stderr, "No version information found.\n");
			break;
		case 1:
			if (debugging) fprintf (stderr, "Found table with matching version number.\n");
			break;
		}
		return (version);
	}
	return (0);
}


/*====================================================================*
 *   
 *   int AddSymbol (unsigned long address, char *symbol);
 *
 * Purpose:	This function is responsible for adding a symbol name
 *		and its address to the symbol table.
 *
 * Arguements:	(unsigned long) address, (char *) symbol
 *
 * Return:	int
 *
 *		A boolean value is assumed.  True if the addition is
 *		successful.  False if not.
 *--------------------------------------------------------------------*/

static int AddSymbol (unsigned long address, char *symbol) 

{

/*
 * Allocate the the symbol table entry. 
 */

	symbols = (struct module_symbol *) realloc (symbols, (num_syms + 1) * sizeof (struct module_symbol));
	if (symbols == (struct module_symbol *) 0) return (0);

/*
 * Then the space for the symbol. 
 */

	symbols [num_syms].name = (char *) malloc (strlen (symbol) * sizeof (char) + 1);
	if (symbols [num_syms].name == (char *) 0) return (0);
	symbols [num_syms].value = address;
	strcpy (symbols [num_syms].name, symbol);
	++num_syms;
	return (1);
}


/*====================================================================*
 *
 *   char *LookupSymbol (unsigned long address, struct symbol *symbol);
 *
 * Purpose:	Find the symbol which is related to the given kernel
 *		address.
 *
 * Arguements:	(long int) value, (struct module_symbol *) sym
 *
 *		value:->	The address to be located.
 * 
 *		sym:->		A pointer to a structure which will be
 *				loaded with the symbol's parameters.
 *
 * Return:	(char *)
 *
 *		If a match cannot be found a diagnostic string is printed.
 *		If a match is found the pointer to the symbolic name most
 *		closely matching the address is returned.
 *   
 *--------------------------------------------------------------------*/

extern char const *LookupSymbol (unsigned long address, struct symbol *symbol) 

{
	int lp;
	char const *last;
	if (!symbols) return ((char *) 0);
	last = symbols [0].name;
	symbol->offset = 0;
	symbol->size = 0;
	if (address < symbols [0].value) return ((char *) 0);
	for (lp = 0; lp <= num_syms; ++lp) 
	{
		if (symbols [lp].value > address) 
		{
			symbol->offset = address - symbols [lp - 1].value;
			symbol->size = symbols [lp].value - symbols [lp - 1].value;
			return (last);
		}
		last = symbols [lp].name;
	}
	if ((last = LookupModuleSymbol (address, symbol)) != (char *) 0) return (last);
	return ((char *) 0);
}


/*====================================================================*
 *
 *   void FreeSymbols ();
 *
 * Purpose:	This function is responsible for freeing all memory which
 *		has been allocated to hold the static symbol table.  It
 *		also initializes the symbol count and in general prepares
 *		for a re-read of a static symbol table.
 *
 * Arguements:  void
 *
 * Return:	void
 *   
 *--------------------------------------------------------------------*/

static void FreeSymbols () 

{
	int index;
	for (index = 0; index < num_syms; ++index) 
	{
		free (symbols [index].name);
	}
	free (symbols);
	symbols = (struct module_symbol *) (0);
	num_syms = 0;
	return;
}


/**************************************************************************
 *   
 *   char *ExpandKadds (char *line, char *el);
 *   
 * Purpose:	This function is responsible for logging a kernel message
 *		line after all potential numeric kernel addresses have
 *		been resolved symolically.
 *
 * Arguements:	(char *) line, (char *) el
 *
 *		line:->	A pointer to the buffer containing the kernel
 *			message to be expanded and logged.
 *
 *		el:->	A pointer to the buffer into which the expanded
 *			kernel line will be written.
 *
 * Return:	void
 **************************************************************************/

#ifdef TEST

static char *ExpandKadds (char *line, char *el) 

{
	unsigned long address;
	struct symbol symbol;
	char dlm;
	char *kp;
	char *sl = line;
	char *elp = el;
	char const *string;
	char num [15];

/*
 * This is as handy a place to put this as anyplace.
 *
 * Since the insertion of kernel modules can occur in a somewhat
 * dynamic fashion we need some mechanism to insure that the
 * kernel symbol tables get read just prior to when they are
 * needed.
 *
 * To accomplish this we look for the Oops string and use its
 * presence as a signal to load the module symbols.
 *
 * This is not the best solution of course, especially if the
 * kernel is rapidly going out to lunch.  What really needs to
 * be done is to somehow generate a callback from the
 * kernel whenever a module is loaded or unloaded.  I am
 * open for patches.
 */

	if (i_am_paranoid && (strstr (line, "Oops:") != (char *) 0) && !InitMsyms ()) Syslog (LOG_WARNING, "Cannot load kernel module symbols.\n");

/*
 * Early return if there do not appear to be any kernel
 * messages in this line.
 */

	if ((num_syms == 0) || (kp = strstr (line, "[<")) == (char *) 0) 
	{
		strcpy (el, line);
		return (el);
	}

/*
 * Loop through and expand all kernel messages. 
 */

	do 
	{
		while (sl < kp + 1) *elp++ = *sl++;

/*
 * Now poised at a kernel delimiter. 
 */

		if ((kp = strstr (sl, ">]")) == (char *) 0) 
		{
			strcpy (el, sl);
			return (el);
		}
		dlm = *kp;
		strncpy (num, sl + 1, kp - sl - 1);
		num [kp - sl - 1] = '\0';
		address = strtoul (num, (char **) 0, 16);
		if ((string = LookupSymbol (address, &symbol)) == (char *) 0) string = sl;
		strcat (elp, string);
		elp += strlen (string);
		if (debugging) fprintf (stderr, "Symbol: %s = %lx = %s, %x/%d\n", sl + 1, address, (symbol.size == 0)? string + 1: string, symbol.offset, symbol.size);
		address = 2;
		if (symbol.size != 0) 
		{
			--address;
			++kp;
			elp += sprintf (elp, "+%x/%d", symbol.offset, symbol.size);
		}
		strncat (elp, kp, address);
		elp += address;
		sl = kp + address;
		if ((kp = strstr (sl, "[<")) == (char *) 0) strcat (elp, sl);
	}
	while (kp != (char *) 0);
	if (debugging) fprintf (stderr, "Expanded line: %s\n", el);
	return (el);
}


#endif

/*====================================================================*
 *
 *   void Syslog (int priority, char const *format, ...);
 *
 *
 *--------------------------------------------------------------------*/

#ifdef TEST

void Syslog (int priority, char const *format, ...) 

{
	va_list ap;
	va_start (ap, format);
	fprintf (stdout, "Pr: %d ", priority);
	vfprintf (stdout, format, ap);
	fprintf (stdout, "\n");
	va_end (ap);
	return;
}


#endif

/*====================================================================*
 *   
 *   int main (int argc, char *argv[]);
 *   
 *   Setting the -DTEST define enables the following code fragment to
 *   be compiled.  This produces a small standalone program which will
 *   echo the standard input of the process to stdout while translating
 *   all numeric kernel addresses into their symbolic equivalent.
 *   
 *--------------------------------------------------------------------*/

#ifdef TEST

#include <stdarg.h>

int main (int argc, char *argv []) 

{
	char line [1024];
	char eline [2048];
	debugging = 1;
	if (!InitKsyms ((char *) 0)) 
	{
		error (1, 0, "Error loading system map.");
	}
	while (!feof (stdin)) 
	{
		fgets (line, sizeof (line), stdin);
		if (line [strlen (line) - 1] == '\n') 
		{
			line [strlen (line) - 1] = '\0';
		}
		memset (eline, '\0', sizeof (eline));
		ExpandKadds (line, eline);
		fprintf (stdout, "%s\n", eline);
	}
	return (0);
}


#endif

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#endif

