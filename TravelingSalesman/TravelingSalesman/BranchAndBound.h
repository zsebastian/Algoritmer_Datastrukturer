#pragma once
/*	Reads:
		http://lcm.csa.iisc.ernet.in/dsa/node187.html
*/

#include "Graph.h"
#include <vector>
#include <utility>
#include "Path.h"

namespace tsp
{
	namespace algorithm
	{
		template <class T, template <class> class MatrixRep, template <class, template <class> class > class AccessorPolicy>
		void BranchAndBound(const Graph<T, MatrixRep, AccessorPolicy>& graph)
		{
			Path<T, Graph<T, MatrixRep, AccessorPolicy>> path(graph);
		}

	}
}