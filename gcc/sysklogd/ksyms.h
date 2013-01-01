/*====================================================================*
 *   
 *   ksyms.h - Definitions for symbol table utilities.
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
 *   
 *--------------------------------------------------------------------*/

#ifndef KSYMS_HEADER
#define KSYMS_HEADER

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

struct kernel_sym 

{
	unsigned long value;
	char name [60];
};

struct module_symbol 

{
	unsigned long value;
	char *name;
};

struct module_ref 

{
	struct module *dep;
	struct module *ref;
	struct module_ref *next_ref;
};

struct module_info 

{
	unsigned long addr;
	unsigned long size;
	unsigned long flags;
	long usecount;
};

typedef struct 

{
	volatile int counter;
}

atomic_t;
struct module 

{
	unsigned long size_of_struct;
	struct module *next;
	char const *name;
	unsigned long size;
	union 
	{
		atomic_t usecount;
		long pad;
	}
	uc;
	unsigned long flags;
	unsigned nsyms;
	unsigned ndeps;
	struct module_symbol *syms;
	struct module_ref *deps;
	struct module_ref *refs;
	int (*init) (void);
	void (*cleanup) (void);
	const struct exception_table_entry *ex_table_start;
	const struct exception_table_entry *ex_table_end;

#ifdef __alpha__

	unsigned long gp;

#endif

};

struct symbol 

{
	char *name;
	int size;
	int offset;
};

struct _module_ 

{
	char *name;
	struct module module;
	struct module_symbol *symbols;
	int num_syms;

#if LINUX_VERSION_CODE >= 0x20112

	struct module_info module_info;

#endif

};


/*====================================================================*
 *   function declarations;
 *--------------------------------------------------------------------*/

extern int InitKsyms (char const *mapfile);
extern int InitMsyms (void);
extern char const *LookupSymbol (unsigned long address, struct symbol *symbol);
extern char const *LookupModuleSymbol (unsigned long address, struct symbol *symbol);
extern void SetParanoiaLevel (int level);
void Syslog (int priority, char const *format, ...);

/*====================================================================*
 *   end declarations;
 *--------------------------------------------------------------------*/

#endif

