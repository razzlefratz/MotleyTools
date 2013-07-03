/*==========================================================================/
 *
 *   ocmassocindex.cpp - implementation of the ocmassocindex2 class;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCMASSOCINDEX_SOURCE
#define oCMASSOCINDEX_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include <cstdio>
#include <sys/stat.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <dirent.h>
#include <math.h>

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#include "../classes/ocmassocindex.hpp"

/*====================================================================*
 *   program constants;  
 *--------------------------------------------------------------------*/

#define NEWLINE "\r\n"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

ocmassocindex & ocmassocindex::index1 (struct _topic_ topics [], unsigned count) 

{
	this->mfilespec->pathname (topics [0].index);
	if (freopen (this->mfilespec->pathname (), "w", stdout) != (FILE *) (0)) 
	{
		this->mwebpage->title (topics [0].title);
		this->mwebpage->topPage (stdout);
		this->mwebpage->print (2, 1, "<ul>", stdout);
		for (this->mindex = 1; this->mindex < count; this->mindex++) 
		{
			cout << "\t\t\t" << "<li style='" << this->mbelow << "'>" << NEWLINE;
			cout << "\t\t\t\t" << "<a target='" << this->mframe << "' href='" << topics [this->mindex].index << "'>" << topics [this->mindex].title << "</a>" << NEWLINE;
			cout << "\t\t\t\t" << "</li>" << NEWLINE;
		}
		this->mwebpage->print (3, 1, "</ul>", stdout);
		this->mwebpage->botPage (stdout);
	}
}

ocmassocindex & ocmassocindex::index2 (struct _topic_ topics [], unsigned count) 

{
	for (this->mtopic = 1; this->mtopic < count; this->mtopic++) 
	{
		this->mfilespec->pathname (topics [this->mtopic].index);
		if (mkdir (this->mfilespec->basename (), 0755)) 
		{
			if (freopen (this->mfilespec->pathname (), "w", stdout) != (FILE *) (0)) 
			{
				this->mwebpage->title (topics [this->mtopic].title);
				this->mwebpage->topPage (stdout);
				this->mwebpage->print (2, 1, "<ul>", stdout);
				for (this->mindex = 1; this->mindex < count; this->mindex++) 
				{
					if (this->mindex == this->mtopic) 
					{
						cout << "\t\t\t<li style='" << this->mabove << "%s'>" << NEWLINE;
						cout << "\t\t\t\t" << "<a target='" << this->mframe << "' href='../" << topics [0].index << "'>" << topics [this->mindex].title << "</a>" << NEWLINE;
						cout << "\t\t\t\t" << "<ul>" << NEWLINE;
						cout << "\t\t\t\t\t" << "</ul>" << NEWLINE;
						cout << "\t\t\t\t" << "</li>" << NEWLINE;
					}
					else 
					{
						cout << "\t\t\t" << "<li style='" << this->mbelow << "'>" << NEWLINE;
						cout << "\t\t\t\t" << "<a href='../" << topics [this->mindex].index << "'>" << topics [this->mindex].title << "</a>" << NEWLINE;
						cout << "\t\t\t\t" << "</li>" << NEWLINE;
					}
				}
				this->mwebpage->print (3, 1, "</ul>", stdout);
				this->mwebpage->botPage (stdout);
			}
		}
	}
	return (* this);
}

/*====================================================================*
 *
 *   ocmassocindex ();
 *   
 *   
 *--------------------------------------------------------------------*/

ocmassocindex::ocmassocindex () 

{
	this->mwebpage = new owebpage;
	this->mwebpage->stylesheet ("http://www.cmassoc.net/styles/CMAssocIndex.css");
	this->mfilespec = new ofilespec;
	this->mframe = ocmassocindex::save ("CMAssocTopic");
	this->mabove = ocmassocindex::save ("above");
	this->mbelow = ocmassocindex::save ("below");
	return;
}

/*====================================================================*
 *
 *   ~ocmassocindex ();
 *   
 *   
 *--------------------------------------------------------------------*/

ocmassocindex::~ocmassocindex () 

{
	return;
}

/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif

