#include "Array2d.h"
#include "KeyValue.h"

#include "Graph.h"
#include "Tests.h"
#include <iostream>
#include <algorithm>
#include "Path.h"
#include "Edge.h"
#include "BranchAndBound.h"
#include "NearestNeighbour.h"
#include "Region.h"
#include "NearestNeighbour.h"
#include <chrono>

int main()
{
	
	tsp::tests::run();
	tsp::Region<int> region;
	
	region.add_city(47, 55);
	region.add_city(15, 65);
	region.add_city(43, 18);
	region.add_city(95, 80);
	region.add_city(5, 40);
	region.add_city(64, 20);
	region.add_city(95, 46);
	region.add_city(46, 85);
	region.add_city(23, 64);
	region.add_city(76, 6);
	region.add_city(15, 97);
	region.add_city(0, 60);
	/*region.add_city(32, 27);
	region.add_city(15, 30);*/
	
	tsp::SmallGraphi graph(region);
	
	auto now = std::chrono::system_clock::now();
	std::cout << "Doing Nearest Neighbour:" << std::endl;
	auto path1 = tsp::algorithm::NearestNeighbour(graph);
	auto then = std::chrono::system_clock::now();
	auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(then - now).count();
	std::cout << "Nearest Neighbour complete (took " << diff << "ms):" << std::endl;

	for (auto edge : path1)
	{
		std::cout << "	" << edge.first.start_node << " -> " << edge.first.end_node << " (" << edge.second << ")" << std::endl;
	}

	std::cout << "		Total weight: " << path1.total_weight() << std::endl;

	now = std::chrono::system_clock::now();
	std::cout << "Doing Branch And Bound:" << std::endl;
	auto path0 = tsp::algorithm::BranchAndBound(graph);
	then = std::chrono::system_clock::now();
	diff = std::chrono::duration_cast<std::chrono::milliseconds>(then - now).count();
	std::cout << "Branch And Bound complete (took " << diff << "ms):" << std::endl;

	for (auto edge : path0)
	{
		std::cout << "	" <<edge.first.start_node << " -> " << edge.first.end_node << " (" << edge.second << ")" << std::endl;
	}

	std::cout << "		Total weight: " << path0.total_weight() << std::endl;

	std::cout << "fk you!";
	
}