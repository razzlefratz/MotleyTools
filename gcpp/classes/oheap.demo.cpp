#include <iostream>
#include "../classes/stdafx.hpp"
#include "../classes/oheap.hpp"

void heaptest () 

{
	oheap heap;
	cout << "heap test ..." << endl;
	heap.store ("456", (void *) (0));
	heap.store ("jkl", (void *) (0));
	heap.store ("mno", (void *) (0));
	heap.store ("def");
	heap.store ("pqr");
	heap.store ("stu");
	heap.store ("789");
	heap.store ("ghi");
	heap.store ("vwx");
	heap.store ("abc");
	heap.store ("yz0");
	heap.store ("123");
}

