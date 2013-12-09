#pragma once

#include "Graph.h"
#include "Array2d.h"
#include <set>

namespace tsp
{
	namespace algorithm
	{
		template <class GraphType>
		class NearestNeighbour 
		{
	
		public: 
			NearestNeighbour(GraphType& graph):
		
			void search();
		private:
			GraphType& m_graph;
		};


		template <class GraphType>
		NearestNeighbour<GraphType>::NearestNeighbour(GraphType& graph)
			:m_graph(graph)
		{}

		template <class GraphType>
		void NearestNeighbour<GraphType>::search()
		{
			
		}
	}
}