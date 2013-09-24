/*====================================================================*
 *
 *   sizes.h - buffer and vector sizes; 
 *
 *.  Motley Tools by Charles Maier
 *:  modified tue 16 sep 03 by user root on host zeus;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SIZES_HEADER
#define SIZES_HEADER

/*====================================================================*
 *   buffer and list allocation constants;
 *--------------------------------------------------------------------*/

#define _LISTSIZE 001100
#define _HEAPSIZE 0x1000
#define _LINESIZE 0x1000
#define _PAGESIZE 0x0400
#define _NAMESIZE 0x0100
#define _CARDSIZE 0x0048
#define _ADDRSIZE 0x0008

#define _MAXTOKEN 0x0100
#define _MAXUNGET 0x0400

#define BARWIDTH_MAX 0x0044
#define PREAMBLE_MAX 0x0064 

#define DATETIME_MAX 0x0030
#define HOSTNAME_MAX 0x0040
#define USERNAME_MAX 0x0020 
#define PROCNAME_MAX 0x0020 
#define ERRORMSG_MAX 0x0080 
#define LINESIZE_MAX 0x1000
#define TEXTLINE_MAX 0x1000
#define HOSTADDR_MAX 0x0020

#define STRINGSIZE 2048
#define BUFFERSIZE 1024
#define SYMBOLSIZE 512 
#define VECTORSIZE 512 
#define DIGESTSIZE 256/8 

#define ARGVSIZE 16
#define ENVPSIZE 16

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#define FILE_VER_MAX 100
#define FILE_DIR_MAX 255  
#define FILE_EXT_MAX 64  

/*====================================================================*
 *   end definitions;
 *--------------------------------------------------------------------*/

#endif



