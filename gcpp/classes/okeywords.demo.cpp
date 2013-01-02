/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#include "../classes/okeywords.cpp"
#include "../classes/ocpluswords.cpp"

ocpluswords cpluswords;
int main (signed argc, char const * argv []) 

{
	cpluswords.enumerate ("", "\n");
	cpluswords.enumerate (80);
	cpluswords.enumerate ();
	return (0);
}

