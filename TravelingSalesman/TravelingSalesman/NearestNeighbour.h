#pragma once
#include "Graph.h"
#include "Path.h"
#include "Edge.h"
#include <vector>
#include <set>
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
		namespace detail
		{
			template <class T, template <class> class MatrixRep, template <class, template <class> class > class AccessorPolicy>
			Path<T> NearestNeighbourOf(const Graph<T, MatrixRep, AccessorPolicy>& graph, int index)
			{
				Path<T> p;
				auto node_view = graph.get_nodes();
			
				std::set<int> unvisited;
				int start_node = index;

				for (auto node : node_view)
				{
					unvisited.insert(node);
				}
			
				if(unvisited.empty() || start_node == -1)
					return p;

				int current_node = start_node;

				int next_node;
				unvisited.erase(current_node); 
				while(!unvisited.empty())
				{
					T min_weight = std::numeric_limits<T>::max();
					tsp::Edge current_edge(current_node, 0); 
					auto neighbours = graph.get_neighbours(current_node);
					for(auto node : neighbours)
					{
						if(unvisited.count(node.end_node) == 0)
						{
							continue;
						}					
						T w = graph.get_weight(current_node, node.end_node);
						if(graph.get_weight(current_node, node.end_node) < min_weight)
						{
							min_weight = graph.get_weight(current_node, node.end_node);
							next_node = node.end_node;
						}
					}
					current_node = next_node;
					current_edge.end_node = current_node; 
					p.push(current_edge, graph);
					unvisited.erase(current_node); 
				}
				p.push(Edge(p.back().first.end_node, p.front().first.start_node), graph);
				return p;
			}
		}

		template <class T, template <class> class MatrixRep, template <class, template <class> class > class AccessorPolicy>
		Path<T> NearestNeighbour(const Graph<T, MatrixRep, AccessorPolicy>& graph)
		{
			T min_weight = std::numeric_limits<T>::max();
			Path<T> ret;
			auto node_view = graph.get_nodes();
			
			std::set<int> unvisited;
			int start_node = -1;

			for (auto node : node_view)
			{
				Path<T> path = detail::NearestNeighbourOf(graph, node);
				if (path.begin() != path.end() && path.total_weight() < min_weight)
				{
					min_weight = path.total_weight();
					ret = path;
				}
			}
			return ret;
		}
	}
}
