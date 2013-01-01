/*====================================================================* 
 *   
 *   sv_tld[] - 
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define TLD_O_BIZ                       0
#define TLD_O_COM                       1
#define TLD_O_COOP                      2
#define TLD_O_EDU                       3
#define TLD_O_INFO                      4
#define TLD_O_MIL                       5
#define TLD_O_MUSEUM                    6
#define TLD_O_NAME                      7
#define TLD_O_NET                       8
#define TLD_O_ORG                       9
#define TLD_O_PRO                      10
#define TLD_O_FIRM                     11
#define TLD_O_NULL                     12

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

char const *sv_tld [] = 

{
	"biz",
	"com",
	"coop",
	"edu",
	"info",
	"mil",
	"museum",
	"name",
	"net",
	"org",
	"pro",
	"firm",
	(char const *)(0)
};

