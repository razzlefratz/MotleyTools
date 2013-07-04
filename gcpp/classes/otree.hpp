/*====================================================================*
 *
 *   otree.hpp - interface for the otree class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oTREE_HEADER
#define oTREE_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstdio>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *7
 *--------------------------------------------------------------------*/

class __declspec (dllexport) otree 

{
public:
	otree (char const * nodename);
	otree (char const * nodename, void const * object);
	otree (char const nodename [], size_t length);
	virtual ~ otree ();
	char const * nodename () const;
	char const * nodetext () const;
	void * nodedata () const;
	otree & nodetext (char const * string);
	otree & nodedata (void * nodedata);
	long index () const;
	long level () const;
	long count () const;
	long first () const;
	long final () const;
	otree * nodeabove () const;
	otree * nodeprior () const;
	otree * nodeafter () const;
	otree * nodebelow () const;
	otree & nodeabove (otree * node);
	otree & nodeprior (otree * node);
	otree & nodeafter (otree * node);
	otree & nodebelow (otree * node);
	otree * root () const;
	otree * home () const;
	otree * head () const;
	otree * tail () const;
	otree * select (char const * string, const int c) const;
	otree * fetch (char const * string, char const c) const;
	otree * nodes (long index) const;
	char * strings (long index) const;
	void * objects (long index) const;
	char * pathname (char buffer [], size_t length, char extender);
	char * pathnames (char extender, char const * pathbreak);
	otree * findnext (char const * string) const;
	otree * findprev (char const * string) const;
	otree * selectpath (char const * pathname, char extender);
	otree * createpath (char const * pathname, char extender);
	otree * extendpath (char const * pathname, char extender);
	otree * insertabove (char const * nodename);
	otree * insertprior (char const * nodename);
	otree * insertafter (char const * nodename);
	otree * insertbelow (char const * nodename);
	otree * appendabove (char const * nodename);
	otree * appendprior (char const * nodename);
	otree * appendafter (char const * nodename);
	otree * appendbelow (char const * nodename);
	otree * createafter (char const * nodename, signed order);
	otree * createbelow (char const * nodename, signed order);
	otree & outline ();
	otree & connect ();
	long reorder (long index, long level);
protected:
	char * msymbol;
	char * mstring;
	void * mobject;
	otree * mabove;
	otree * mbelow;
	otree * mprior;
	otree * mafter;
	otree * mother;
private:
	otree & index (long index);
	otree & level (long level);
	otree & count (long count);
	static char * mbuffer;
	static char * mlength;
	long mlevel;
	long mcount;
	long mindex;
	long mclass;
};

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

