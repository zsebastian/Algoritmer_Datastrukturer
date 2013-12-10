#include "Array2d.h"
#include "Graph.h"
#include "Tests.h"
#include <iostream>
#include <algorithm>
#include "Path.h"
#include "Edge.h"
#include "BranchAndBound.h"
#include "Region.h"

int main()
{
	
	tsp::tests::run();
	tsp::Region<int> region;
	
	region.add_city(0, 60);
	region.add_city(32, 27);
	region.add_city(15, 30);
	region.add_city(47, 55);
	region.add_city(43, 18);
	region.add_city(15, 65);
	region.add_city(95, 80);
	
	tsp::SmallGraphi graph(region);

	auto view = graph.get_neighbours(1);

	for (auto node : graph.get_neighbours(1))
	{
		std::cout << node.get_weight(graph) << std::endl;
	}

	for (auto node : graph.get_nodes())
	{
		std::cout << node << std::endl;
	}

	auto path = tsp::algorithm::BranchAndBound(graph);
	for (auto edge : path)
	{
		std::cout << edge.first.start_node << " -> " << edge.first.end_node << " (" << edge.second << ")" << std::endl;
	}

	std::cout << path.total_weight() << std::endl;
	std::cout << "fk you!";
	
}