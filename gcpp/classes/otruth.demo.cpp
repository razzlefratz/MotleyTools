#include <iostream>

#include "../classes/otruth.hpp"

#include "../classes/otruth.cpp"
#include "../classes/ocode.cpp"

int main (int argc, char const *argv []) 

{
	otruth truth;
	cout << truth.value ("true", -1) << "\n";
	cout << truth.value ("false", -1) << "\n";
	return (0);
}

