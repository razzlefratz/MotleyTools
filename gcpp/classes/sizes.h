/*====================================================================*
 *
 *   sizes.h - buffer and vector sizes; 
 *
 *.  published 2003 by charles maier associates limited for internal use;
 *:  modified tue 16 sep 03 by user root on host zeus;
 *;  compiled for debian gnu/linux using gcc compiler;
 *
 *--------------------------------------------------------------------*/

#ifndef SIZES_HEADER
#define SIZES_HEADER
 
/*====================================================================*
 *   buffer and list allocation constants;
 *--------------------------------------------------------------------*/

#define _LISTSIZE 0x0100
#define _HEAPSIZE 0x1000
#define _LINESIZE 0x0400

#define _MAXTOKEN 0x0100
#define _MAXUNGET 0x0400

#define BARWIDTH_MAX 0x0044
#define PREAMBLE_MAX 0x0064 

#define DATETIME_MAX 0x0030
#define HOSTNAME_MAX 0x0040
#define USERNAME_MAX 0x0020 
#define ERRORMAG_MAX 0x0080 
#define TEXTLINE_MAX 0x1000

#define STRINGSIZE 32767
#define BUFFERSIZE 1024
#define SYMBOLSIZE 512 
#define VECTORSIZE 512 

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
 

