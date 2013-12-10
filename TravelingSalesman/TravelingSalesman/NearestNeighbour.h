#pragma once
#include "Graph.h"
#include "Path.h"
#include <vector>
#include <numeric>

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
