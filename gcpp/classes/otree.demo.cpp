#include "../classes/otree.hpp"
#include "../classes/otree.cpp"

int main (signed argc, char const * argv [])

{
	otree tree ("node1");
	otree * node = & tree;
	char buffer [100];
	node->appendbelow ("child1");
	node->appendbelow ("child2");
	node = node->appendafter ("node2");
	node->appendbelow ("child1");
	node->appendbelow ("child2");
	node = node->appendafter ("node3");
	node->appendbelow ("child1");
	node = node->appendbelow ("child2");
	std::cout << node->pathname (buffer, sizeof (buffer), '.') << std::endl;

// tree.createpath ("node2.child1.test1", '.');

	tree.outline ();
	return (0);
}

