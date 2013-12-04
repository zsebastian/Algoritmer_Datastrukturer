#include "Relations.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

template <class forward_iterator>
void pretty(forward_iterator begin, forward_iterator end, 
			int width, int elem_per_row)
{
	while (begin != end)
	{
		if (std::distance(begin, end) % elem_per_row == 0)
			std::cout << std::endl;
		std::left(std::cout);
		std::cout << std::setw(width)<< (*(begin++))->name();

	}

}

int main()
{
	auto a = relations::node::make("a");	
	auto b = relations::node::make("b");	
	auto c = relations::node::make("c");	
	auto d = relations::node::make("d");	

	auto e = relations::node::make("e");	
	auto f = relations::node::make("f");

	auto g = relations::node::make("g");
	auto h = relations::node::make("h");
	auto i = relations::node::make("i");

	a->add_enemy(b);
	b->add_enemy(c);
	b->add_enemy(d);
	c->add_enemy(b);
	c->add_enemy(d);

	c->add_enemy(e);
	e->add_enemy(f);
	f->add_enemy(g);
	f->add_enemy(h);
	h->add_enemy(i);

	auto friends = a->list_friends();

	pretty(friends.begin(), friends.end(), 4, 10);

	return 0; 
}
