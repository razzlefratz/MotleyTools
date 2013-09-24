#include "../classes/stdafx.hpp"
#include <iostream>
#include "../classes/oprefix.hpp"

void oprefixtest()

{
	oprefix prefix;

/*
 * char buffer[1024];
 */

	cout << "prefix test ..." << std::endl;
	prefix.define("ab", "%2%");
	prefix.define("abc", "%1%");
	prefix.define("abcde", "%3%");
	prefix.define("abcd", "5");
	prefix.define("a", "4");
	cout << "prefix=[" << prefix.prefix("abcdefg") << "]" << std::endl;

/*
 * prefix.report(buffer, 12, stdout);
 */

}

