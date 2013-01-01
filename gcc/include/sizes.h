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

#define _LINESIZE 0x0400
#define _LISTSIZE 0x0100
#define _DATESIZE sizeof("yyyy-mm-dd hh:mm:ss tmz") 

#define _MAXTOKEN 0x0100
#define _MAXUNGET 0x0400

#define BARWIDTH_MAX 0x0044
#define PREAMBLE_MAX 0x0064 

#define DATETIME_MAX 0x0030
#define HOSTNAME_MAX 0x0020
#define USERNAME_MAX 0x0020 
#define PROCNAME_MAX 0x0100 
#define TEXTLINE_MAX 0x0400 
#define ERRORMSG_MAX 0x0080 
#define HOSTADDR_MAX 0x0020 

#define STRINGSIZE 32767
#define BUFFERSIZE 2048
#define SYMBOLSIZE 512 
#define VECTORSIZE 512  

#define ARGVSIZE 16
#define ENVPSIZE 16

/*====================================================================*
 *   end definitions;
 *--------------------------------------------------------------------*/

#endif

