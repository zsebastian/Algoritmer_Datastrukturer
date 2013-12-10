#pragma once
#include "Graph.h"
#include "Edge.h"
#include <vector>
#include <numeric>

/*
	1. pick a starting node at random
	2. pick the neighbour with the lowest traveling cost
	3. go to that node
	4. mark as visited
	4. repeat step 2 and 3

	function NearestNeighbour(Graph)
		vector<int> unvisited(number of cities);
		int current_node
		int next_node
		int lowest_travelling_cost = INT_MAX

		while(vector != empty)
			for each neighbour to current_node in vector
				if(neighbour < lowest_travelling_cost)
					next_node = neighbour
					lowest_travelling_cost = neighbour.cost
				end
			end
			current_node = next_node
			unvisited.pop(next_node)
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
			
		}
	}
}
