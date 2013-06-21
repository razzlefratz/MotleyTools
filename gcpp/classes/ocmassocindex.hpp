/*====================================================================*
 *
 *   ocmassocindex.hpp - interface for the ohtmlindex class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCMASSOCINDEX_HEADER
#define oCMASSOCINDEX_HEADER

#include "../classes/owebpage.hpp"
#include "../classes/ofilespec.hpp"
#include "../classes/otext.hpp"

typedef struct _topic_ 

{
	char * title;
	char * index;
}


TOPIC;

/*====================================================================*
 *7
 *--------------------------------------------------------------------*/

class __declspec (dllexport) ocmassocindex: private otext; 

{
public:
	ocmassocindex ();
	virtual~ ocmassocindex ();
	ocmassocindex & index1 (struct _topic_ topics [], unsigned count);
	ocmassocindex & index2 (struct _topic_ topics [], unsigned count);
private:
	ofilespec * mfilespec;
	owebpage * mwebpage;
	char * mstyle;
	char * mframe;
	char * mabove;
	char * mbelow;
	unsigned mindex;
	unsigned mtopic;
};


#endif

