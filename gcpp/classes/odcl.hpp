/*====================================================================*
 *
 *   odcl.hpp - command definitions and declarations;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 2005 by Charles Maier Associates for internal use;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oDCL_HEADER
#define oDCL_HEADER

/*====================================================================*
 *   variables;
 *--------------------------------------------------------------------*/

typedef signed errno_t;
typedef struct tree

{
	struct tree * next;
	struct tree * list;
	char * name;
}

TREE;

/*====================================================================*
 *   functions;
 *--------------------------------------------------------------------*/

class odcl

{
public: 
	dcl ();
	~ dcl ();
	TREE * line ();
	TREE * name ();
	TREE * text (char);
	TREE * list (char, TREE * ());
	TREE * item ();
	TREE * term ();
	void display (TREE *);
	void discard (TREE *);
	void init ();
private: 
	signed grab ();
	void error (int, errno_t, char const *, ...);
	static char buffer [];
	static char * string;
	static char const * format;
	static char const * indent;
	static char c;
};

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#endif



