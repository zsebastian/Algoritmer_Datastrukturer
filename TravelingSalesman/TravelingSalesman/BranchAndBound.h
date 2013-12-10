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
		/* My kingdom for a friend function! */
		template <class T, template <class> class MatrixRep, template <class, template <class> class > class AccessorPolicy>
		Path<T> BranchAndBound(const Graph<T, MatrixRep, AccessorPolicy>& graph);

		namespace detail
		{
			template <class T, template <class> class MatrixRep, template <class, template <class> class > class AccessorPolicy>
			class BAB
			{
				template <class T, template <class> class MatrixRep, template <class, template <class> class > class AccessorPolicy>
				friend Path<T> BranchAndBound(const Graph<T, MatrixRep, AccessorPolicy>& graph);
			public:
				BAB(const Graph<T, MatrixRep, AccessorPolicy>& graph);
				Path<T> start();
			private:
				void init();

				const Graph<T, MatrixRep, AccessorPolicy>& m_graph;
				Path<T> m_best;
				void recurce(Path<T>);
			};
		}

		template <class T, template <class> class MatrixRep, template <class, template <class> class > class AccessorPolicy>
		Path<T> BranchAndBound(const Graph<T, MatrixRep, AccessorPolicy>& graph)
		{
			if (*graph.get_nodes().begin() == *graph.get_nodes().end())
				return Path<T>();

			detail::BAB<T, MatrixRep, AccessorPolicy> branch(graph);
			return branch.start();
		}		

		namespace detail
		{
			template <class T, template <class> class MatrixRep, template <class, template <class> class > class AccessorPolicy>
			BAB<T, MatrixRep, AccessorPolicy>::BAB(const Graph<T, MatrixRep, AccessorPolicy>& graph)
				:m_graph(graph)
			{
			}

			template <class T, template <class> class MatrixRep, template <class, template <class> class > class AccessorPolicy>
			void BAB<T, MatrixRep, AccessorPolicy>::init()
			{
				auto nodes = m_graph.get_nodes();
				auto begin = nodes.begin();
				auto end = nodes.end();
				int prev = *begin;
				++begin;
				while (begin != end)
				{
					m_best.push(Edge(prev, *begin), m_graph);
					prev = *begin;
					++begin;
				}
			
			}

			template <class T, template <class> class MatrixRep, template <class, template <class> class > class AccessorPolicy>
			Path<T> BAB<T, MatrixRep, AccessorPolicy>::start ()
			{
				init();
				recurce(Path<T>());

				/* wrap up road */
				m_best.push(Edge((m_best.begin() + m_best.total_edges() - 1)->first.end_node, m_best.front().first.start_node), m_graph);
				return m_best;
				/*
				 Naive Branch-and-Bound Solution of TSP
     
				 w = w(1,2) + w(2,3) + w(3,4) + ... + w(n-1,n) + w(n,1)
				 Best_S_so_far = (  n, [ 1, 2, 3, ... , n-1, n ], w )
				 S = ( 1, [ 1 ], 0 )
				 Search( S, Best_S_so_far )
				 print Best_S_so_far

				 procedure Search( S, Best_S_so_far )

					let ( k, [ i1, i2, ... , ik ], w ) = S
					let ( n, [ i1B, i2B, ... , inB ], wB ) = Best_S_so_far
					if k = n then
						new_w = w + w(ik,i1)
						if new_w < wB then
						   Best_S_so_far = ( k, [ i1, i2, ... , ik ], new_w )
						end if
					else
						for all j not in [ i1, i2, ... , ik ]
						   new_w = w + w(ik,j)
						   if new_w < wB then
							   New_S = ( k+1, [ i1, i2, ... , ik, j ], new_w )
							   Search( New_S, Best_S_so_far )
						   end if
						end for
					endif
					return
					end
				*/
			}

			template <class T, template <class> class MatrixRep, template <class, template <class> class > class AccessorPolicy>
			void BAB<T, MatrixRep, AccessorPolicy>::recurce(Path<T> path)
			{
				int last = 0;
				if (path.total_edges() != 0)
					last = path.back().first.end_node;
				else
					last = *m_graph.get_nodes().begin();;	
				
				if (path.total_edges() == m_best.total_edges())
				{
					if (path.total_weight() < m_best.total_weight())
					{
						m_best = path;
					}
				}
				else
				{
					for (auto node : m_graph.get_neighbours(last))
					{
						auto begin = path.begin();

						if (std::find_if(begin, path.end(), 
							[&](const std::pair<Edge, T>& edge) -> bool
							{
								return edge.first.start_node == node.end_node || edge.first.end_node == node.end_node;
							}) == path.end())
						{
							T new_w = path.total_weight();
							if (new_w < m_best.total_weight())
							{
								Path<T> new_path = path;
								new_path.push(node, m_graph);
								recurce(new_path);
							}
						}

					}
				}
				return;
			}
	
		}
	}
}