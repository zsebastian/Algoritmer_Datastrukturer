#include "Array2d.h"
#include "Graph.h"
#include "Tests.h"
#include <iostream>
#include <algorithm>

int main()
{
	tsp::tests::run();
	tsp::Graph<int, tsp::matrix::Array2d, tsp::Symmetric> mat;
	mat.add_weight(1, 0, 10);
	mat.add_weight(3, 1, 20);
	auto view = mat.get_neighbours(1);

	for (auto node : mat.get_neighbours(1))
	{
		std::cout << mat.get_weight(node.start_node, node.neighbour) << std::endl;
	}
	std::cout << "fk you!";
	
}