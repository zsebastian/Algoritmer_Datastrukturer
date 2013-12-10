#pragma once
#include "Graph.h"
#include "Edge.h"
#include <vector>
#include <numeric>

/*
	1. pick a starting node at random
	2. pick the neighbour with the lowest travelling cost
	3. go to that node
	4. mark as visited
	4. repeat step 2 and 3

	function NearestNeighbour(Graph)
		A[] unvisited = number of cities;
		var current_node
		var next_node
		var lowest_travelling_cost = infinit_value

		while A is not empty ->
			foreach neighbour of current_node in A
				if neighbour < lowest_travelling_cost
					next_node = neighbour
					lowest_travelling_cost = cost to neighbour
				end
			end
			current_node = next_node
			remove next_node from A
		end
	end 
*/

namespace tsp
{
	namespace algorithm
	{
		template <class T, template <class> class MatrixRep, template <class, template <class> class > class AccessorPolicy>
		void NearestNeighbour(const Graph<T, MatrixRep, AccessorPolicy>& graph)
		{
			SmallGraphi graph;
			auto node_view = graph.get_nodes();
			std::vector<int> nodes(node_view.begin(), node_view.end());
			auto neighbours = graph.get_neighbours(nodes.front());

			while(!nodes.empty())
			{
				for(auto node : neighbours)
				{
					
				}
			}
		}
	}
}
