#include <iostream>
#include "../classes/stdafx.hpp"
#include "../classes/odict.hpp"
#include "../classes/odict.cpp"

void main (int argc, char * argv []) 

{
	odict dict ("*", "*");
	dict.define ("all", "FF:FF:FF:FF:FF:FF");
	dict.define ("broadcast", "FF:FF:FF:FF:FF:FF");
	dict.define ("local", "00:B0:52:00:00:01");
	dict.define ("EK6000", "00:B0:52:00:00:02");
	dict.define ("Unit1", "00:B0:52:DA:DA:02");
	dict.define ("unit1", "00:B0:52:DA:DA:03");
	dict.define ("abcd", "5");
	dict.define ("MCDonald", "6");
	dict.define ("A", "7");
	dict.define ("About", "8");
	dict.define ("Broadcast", "FF:FF:FF:FF:FF:FF");
	dict.define ("abandom", "9");
	dict.define ("McDonald", "14");
	std::cout << "lookup=[" << dict.lookup ("local") << "]" << std::endl;
	dict.enumerate ();
	return (0);
}

