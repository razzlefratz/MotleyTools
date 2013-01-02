/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#include <iostream>

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/olist.hpp"
#include "../classes/oitem.hpp"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#include "../classes/olist.cpp"
#include "../classes/oitem.cpp"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

int main () 

{
	olist list;
	cout << "list test ..." << "\n";
	list.insertitem (new oitem ("abc"));
	list.insertitem (new oitem ("789"));
	list.insertitem (new oitem ("ghi"));
	list.insertitem (new oitem ("def"));
	list.insertitem (new oitem ("123"));
	list.insertitem (new oitem ("mno"));
	list.insertitem (new oitem ("mno"));
	list.insertitem (new oitem ("jkl"));
	list.insertitem (new oitem ("stu"));
	list.insertitem (new oitem ("456"));
	list.insertitem (new oitem ("pqr"));
	list.insertitem (new oitem ("yz0"));
	list.insertitem (new oitem ("vwx"));
	list.insertitem (new oitem ("jkl"));
	list.insertitem (new oitem ("stu"));
	list.insertitem (new oitem ("456"));
	list.insertitem (new oitem ("pqr"));
	list.insertitem (new oitem ("yz0"));
	list.insertitem (new oitem ("vwx"));
	list.insertitem (new oitem ("abc"));
	list.insertitem (new oitem ("789"));
	list.insertitem (new oitem ("ghi"));
	list.insertitem (new oitem ("def"));
	list.insertitem (new oitem ("123"));
	for (unsigned index = 0; index < list.count (); index++) 
	{
		cout << list.items (index) ->name () << "\n";
	}
}

