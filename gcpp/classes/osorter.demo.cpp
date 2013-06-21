#include "../classes/stdafx.hpp"
#include <iostream>
#include <cstring>
#include "../classes/osorter.hpp"

void osortertest () 

{
	osorter list (std::strcmp);
	list+= "xxx";
	list+= "yyy";
	list+= "789";
	list+= "abc";
	list+= "abc";
	list+= "def";
	list+= "ghi";
	list+= "jkl";
	list+= "mno";
	list+= "pqr";
	list+= "stu";
	list+= "vwx";
	list+= "yz0";
	list+= "123";
	list+= "456";
	list+= "789";
	list+= "def";
	list+= "abc";
	list+= "vwx";
	list+= "yz0";
	list+= "123";
	list+= "456";
	list+= "789";
	list+= "ghi";
	list+= "jkl";
	list+= "mno";
	list+= "pqr";
	list+= "stu";
	for (unsigned index = 0; index < list.count (); ++index) 
	{
		cout << index << " " << list [index] << std::endl;
	}
}


