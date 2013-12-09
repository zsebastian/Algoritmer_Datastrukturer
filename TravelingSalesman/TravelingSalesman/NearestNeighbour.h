#pragma once
#include "Graph.h"
#include <vector>
#include <numeric>

namespace tsp
{
	namespace algorithm
	{
		template <class T, template <class> class MatrixRep, template <class, template <class> class > class AccessorPolicy> 
		void NearestNeighbour(int start_node, int end_node, const Graph<T, MatrixRep, AccessorPolicy>& graph)
		{
			int lowest_weight_found = std::numeric_limits<T>::max();
			int next_node;  
			int current_node = start_node; 
			std::vector<int> visited; 

			while(start_node != end_node)
			{
				for(auto node : graph.get_neighbours(current_node))
				{
					if(graph.get_weight(node.start_node, node.neighbour) < lowest_weight_found)
					{
						lowest_weight_found = graph.get_weight(node.start_node, node.neighbour);
						next_node = node; 
					}
				}
				current_node = next_node; 
				visited.push_back(current_node);
			}
		}
	}
}
