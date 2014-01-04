#pragma once
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

#include "Graph.h"
#include <vector>
#include <numeric>

namespace tsp
{
	namespace algorithm
	{
		template <class T>
		tsp::Path NearestNeighbour(Graph<T> graph)
		{
			std::set<int> nodes = graph.get_nodes();
			T total_weight = std::numeric_limits<T>::max();
			tsp::Path ret; 
			
			for(auto count : nodes)
			{
				T current_total_weight = 0; 
				tsp::Path path; 
				std::set<int> unvisited; 
				int start_node = count; 
				int current_node = start_node; 
				
				for(auto node : nodes) 
				{
					unvisited.insert(node);
				}

				tsp::Edge next_edge(0, 0); 
				unvisited.erase(current_node);

				while(!unvisited.empty())
				{
					T min_weight = std::numeric_limits<T>::max();
					tsp::Edge current_edge(current_node, 0);
					std::set<int> neighbours = graph.get_neighbours(current_node);

					for(auto neighbour : neighbours) 
					{
						if(unvisited.count(neighbour) == 0)
							continue; 
						
						current_edge.set_end_node(neighbour);

						if(graph.get_weight(current_edge) < min_weight)
						{
							next_edge = current_edge;
							min_weight = graph.get_weight(current_edge); 
						}
					}

					current_total_weight += min_weight; 
					current_node = next_edge.get_end_node();
					path.push(next_edge);
					unvisited.erase(current_node);
				}
				path.push(Edge(path.get_path().back().get_end_node(), path.get_path().front().get_start_node()));
				current_total_weight += graph.get_weight(path.get_path().back());

				if(current_total_weight < total_weight)
				{
					total_weight = current_total_weight; 
					ret = path; 
				}
			}
			return ret; 
		}
	}
}
