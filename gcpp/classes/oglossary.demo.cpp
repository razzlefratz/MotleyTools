#include "../classes/stdafx.hpp"
#include <iostream>
#include "../classes/oglossary.hpp"
#include "../classes/olist.hpp"
#include "../classes/oitem.hpp"

#include "../classes/oglossary.cpp"
#include "../classes/olist.cpp"
#include "../classes/oitem.cpp"

void main (int argc, char * argv []) 

{
	oglossary glossary;
	cout << "glossary test ..." << std::endl;
	glossary.define ("ab", "%2%");
	glossary.define ("abc", "%1%");
	glossary.define ("abcde", "%3%");
	glossary.define ("abcd", "5");
	glossary.define ("a", "4");
	cout << "glossary loaded" << std::endl;
	cout << "glossary=[" << glossary.lookup ("abcde") << "]" << std::endl;
}


