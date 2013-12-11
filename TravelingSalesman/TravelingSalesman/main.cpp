#include "Array2d.h"
#include "KeyValue.h"

#include "Graph.h"
#include "Tests.h"
#include <iostream>
#include <algorithm>
#include "Path.h"
#include "Edge.h"
#include "BranchAndBound.h"
#include "Region.h"
#include "NearestNeighbour.h"

int main()
{
	
	tsp::tests::run();
	tsp::Region<float> region;
	
	region.add_city(0, 60);
	region.add_city(32, 27);
	region.add_city(15, 30);
	region.add_city(47, 55);
	region.add_city(43, 18);
	region.add_city(15, 65);
	region.add_city(95, 80);
	region.add_city(5, 40);
	region.add_city(64, 20);
	region.add_city(95, 46);
	region.add_city(46, 85);
	region.add_city(23, 64);
	region.add_city(76, 6);
	region.add_city(15, 97);

	tsp::Graph<float, tsp::matrix::KeyValue, tsp::accessor::Symmetric> graph(region);

	auto view = graph.get_neighbours(1);

	for (auto node : graph.get_neighbours(1))
	{
		std::cout << node.get_weight(graph) << std::endl;
	}

	for (auto node : graph.get_nodes())
	{
		std::cout << node << std::endl;
	}

	auto path0 = tsp::algorithm::BranchAndBound(graph);
	auto path1 = tsp::algorithm::NearestNeighbour(graph);

	for (auto edge : path0)
	{
		std::cout << edge.first.start_node << " -> " << edge.first.end_node << " (" << edge.second << ")" << std::endl;
	}

	std::cout << path.total_weight() << std::endl;
	std::cout << "fk you!";
	
}