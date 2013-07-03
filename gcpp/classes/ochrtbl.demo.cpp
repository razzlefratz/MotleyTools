#include <cstring>
#include <iostream>

#include "../chrlib/charset.hpp"
#include "../classes/ochrlwr.cpp"
#include "../classes/ochrupr.cpp"

int main () 

{
	static char * list [] = 
	{
		"abc",
		"ABC",
		"ABC",
		"abc",
		"abC",
		"abc",
		"abc",
		"abC",
		"abc",
		"xyz",
		"abc",
		"XYZ",
		"ABC",
		"xyz",
		NULL
	};
	ochrlwr * p = new ochrlwr;
	ochrupr * q = new ochrupr;
	cout << p->convert (strdup (gcsAlnum)) << std::endl;
	cout << q->convert (strdup (gcsAlnum)) << std::endl;
	cout << std::endl;
	for (int n = 0; list [n]; ++n, ++n) 
	{
		cout << list [n] << " " << list [n + 1] << " " << p->compare (list [n], list [n + 1]) << std::endl;
	}
	cout << std::endl;
	for (int n = 0; list [n]; ++n, ++n) 
	{
		cout << list [n] << " " << list [n + 1] << " " << q->compare (list [n], list [n + 1]) << std::endl;
	}
	cout << std::endl;
	return (0);
}

