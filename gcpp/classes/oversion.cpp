/*====================================================================*
 *
 *   oversion.cpp - implementation of the oversion class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oVERSION_SOURCE
#define oVERSION_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oversion.hpp"

/*====================================================================*
 *
 *   oversion & program (char const * program);
 *   char const * program () const * ;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oversion & oversion::program (char const * program)

{
	this->mprogram = otext::replace (this->mprogram, program);
	return (* this);
}

char const * oversion::program () const

{
	return (this->mprogram);
}

/*====================================================================*
 *
 *   oversion & company (char const * company);
 *   char const * company () const * ;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oversion & oversion::company (char const * company)

{
	this->mcompany = otext::replace (this->mcompany, company);
	return (* this);
}

char const * oversion::company () const

{
	return (this->mcompany);
}

/*====================================================================*
 *
 *   oversion & project (char const * project);
 *   char const * project () const * ;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oversion & oversion::project (char const * project)

{
	this->mproject = otext::replace (this->mproject, project);
	return (* this);
}

char const * oversion::project () const

{
	return (this->mproject);
}

/*====================================================================*
 *
 *   oversion & package (char const * package);
 *   char const * package () const * ;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oversion & oversion::package (char const * package)

{
	this->mpackage = otext::replace (this->mpackage, package);
	return (* this);
}

char const * oversion::package () const

{
	return (this->mpackage);
}

/*====================================================================*
 *
 *   char const * version () const * ;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oversion & oversion::version (char const * version)

{
	this->mversion = otext::replace (this->mversion, version);
	return (* this);
}

char const * oversion::version () const

{
	return (this->mversion);
}

/*====================================================================*
 *
 *   oversion & release (char const * release);
 *   char const * release () const * ;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oversion & oversion::release (char const * release)

{
	this->mrelease = otext::replace (this->mrelease, release);
	return (* this);
}

char const * oversion::release () const

{
	return (this->mrelease);
}

/*====================================================================*
 *
 *   oversion & contact (char const * contact);
 *   char const * contact () const * ;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oversion & oversion::contact (char const * contact)

{
	this->mcontact = otext::replace (this->mcontact, contact);
	return (* this);
}

char const * oversion::contact () const

{
	return (this->mcontact);
}

/*====================================================================*
 *
 *   oversion & print (void);
 *
 *   print full version information on stdout;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oversion & oversion::print (void)

{
	std::cerr << this->mprogram << " ";
	std::cerr << this->mpackage << "-";
	std::cerr << this->mversion << " ";
	std::cerr << "C++" << " ";
	std::cerr << this->mcompany << " ";
	std::cerr << this->mrelease << " ";
	std::cerr << this->mlicense << " ";
	std::cerr << std::endl;
	return (* this);
}

/*====================================================================*
 *
 *   oversion ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oversion::oversion ()

{
	this->mprogram = otext::save (PROGRAM);
	this->mcompany = otext::save (COMPANY);
	this->mproject = otext::save (PROJECT);
	this->mpackage = otext::save (PACKAGE);
	this->mversion = otext::save (VERSION);
	this->mrelease = otext::save (RELEASE);
	this->mlicense = otext::save (LICENSE);
	this->mcontact = otext::save (CONTACT);
	return;
}

/*====================================================================*
 *   
 *   ~oversion ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oversion::~ oversion ()

{
	return;
}

/*====================================================================*
 *   end implementation
 *--------------------------------------------------------------------*/

#endif



