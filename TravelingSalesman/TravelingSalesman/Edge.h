#pragma once

namespace tsp
{
	struct Edge
	{
		Edge(int start_node_, int end_node_)
			:start_node(start_node_), end_node(end_node_)
		{}

		const int start_node;
		const int end_node;
	};
}