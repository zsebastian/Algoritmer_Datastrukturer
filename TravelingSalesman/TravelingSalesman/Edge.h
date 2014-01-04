#pragma once

namespace tsp
{
template <class T, template <class> class MatrixRep, template <class, template <class> class > class AccessorPolicy>
class Graph;

	struct Edge
	{
		Edge(int start_node_, int end_node_)
			:start_node(start_node_), end_node(end_node_)
		{}

		Edge& operator=(const Edge& rhs)
		{
			if (this != &rhs)
			{
				start_node = rhs.start_node;
				end_node = rhs.end_node;
			}
			return *this;
		}

		Edge(const Edge& rhs)
			:start_node(rhs.start_node), end_node(rhs.end_node)
		{}

		template <class T, template <class> class MatrixRep, template <class, template <class> class > class AccessorPolicy>
		auto get_weight(const Graph<T, MatrixRep, AccessorPolicy>& from_graph) -> T;

		int start_node;
		int end_node;
	};
}
#include "Graph.h"
namespace tsp
{
	template <class T, template <class> class MatrixRep, template <class, template <class> class > class AccessorPolicy>
	auto Edge::get_weight(const Graph<T, MatrixRep, AccessorPolicy>& from_graph) -> T
	{
		return from_graph.get_weight(*this);
	}
}