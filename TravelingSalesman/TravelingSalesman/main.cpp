#include "Array2d.h"
#include "Graph.h"
#include "Tests.h"
#include <iostream>
#include <algorithm>
#include "Path.h"
#include "Edge.h"

int main()
{
	tsp::tests::run();
	tsp::SmallGraphi graph;

	graph.add_weight(1, 0, 10);
	graph.add_weight(3, 1, 20);
	auto view = graph.get_neighbours(1);

	for (auto node : graph.get_neighbours(1))
	{
		std::cout << graph.get_weight(node.start_node, node.end_node) << std::endl;
	}

	tsp::Path<int> path;

	
	path.push(tsp::Edge(0, 1), graph);
	path.push(tsp::Edge(1, 3), graph);

	std::cout << path.total_weight() << std::endl;
	std::cout << "fk you!";
	
}