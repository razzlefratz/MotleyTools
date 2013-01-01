/* printk.c - send textual output to the tty you're 
 * running on, regardless of whether it's passed 
 * through X11, telnet, etc. 
 */

/* my_tty->driver is a struct which holds the tty's 
 * functions, one of which (write) is used to 
 * write strings to the tty. It can be used to take 
 * a string either from the user's memory segment 
 * or the kernel's memory segment. 
 *
 * The function's first parameter is the tty to 
 * write to, because the  same function would 
 * normally be used for all tty's of a certain type.
 * The second parameter controls whether the 
 * function receives a string from kernel memory 
 * (false, 0) or from user memory (true, non zero). 
 * The third parameter is a pointer to a string, 
 * and the fourth parameter is the length of 
 * the string.
 */

/* ttys were originally hardware devices, which 
 * (usually) adhered strictly to the ASCII standard. 
 * According to ASCII, to move to a new line you 
 * need two characters, a carriage return and a 
 * line feed. In Unix, on the other hand, the 
 * ASCII line feed is used for both purposes - so 
 * we can't just use \n, because it wouldn't have 
 * a carriage return and the next line will 
 * start at the column right
 *                          after the line feed. 
 *
 * BTW, this is the reason why the text file 
 *  is different between Unix and Windows. 
 * In CP/M and its derivatives, such as MS-DOS and 
 * Windows, the ASCII standard was strictly 
 * adhered to, and therefore a new line requires 
 * both a line feed and a carriage return. 
 */

/* 
 * Copyright (C) 1998 by Ori Pomerantz 
 */

#include <linux/kernel.h>   
#include <linux/module.h>   

#if CONFIG_MODVERSIONS==1
#define MODVERSIONS
#include <linux/modversions.h>
#endif        

#include <linux/sched.h>    
#include <linux/tty.h>      

void print_string (char *str) 

{
	struct tty_struct *my_tty;
	my_tty = current->tty;
	if (my_tty != NULL) 
	{
		(my_tty->driver->write)(my_tty, 0, str, strlen (str));
		(my_tty->driver->write)(my_tty, 0, "\r\n", 2);
	}
}

