#include "Graph.h"
#include "NearestNeighbour.h"
#include <iostream>

int main()
{
	tsp::Region<float> region;
	
	region.add_city(15, 30);	
	region.add_city(43, 18);
	region.add_city(95, 80);
	region.add_city(15, 65);
	region.add_city(0, 60);
	region.add_city(47, 55);
	region.add_city(32, 27);
	

	tsp::Graph<float> graph(region);

	auto path = tsp::algorithm::NearestNeighbour(graph);
	float total_weight = 0; 
	for(auto edge : path.get_path())
	{
		total_weight += graph.get_weight(edge);
		std::cout << edge.get_start_node() << " -> " << edge.get_end_node() << " (" << graph.get_weight(edge) << ")" << std::endl; 
	}

	std::cout << "Total weight: " << total_weight << std::endl;

	return 0; 
}