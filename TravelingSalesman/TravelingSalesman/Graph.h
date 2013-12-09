#pragma once
#include <utility>
#include <memory>

/* WeightedMatrixRep concept:
	bool is_null(int x, int y) const // true if x, y is not set. If out of bounds returns true
	int size_x() const // returns dimensions of matrix
	int size_y() const // returns dimensions of matrix
	void set(int x, int y, const T& weight)	//for setting element, this resizes the matrix if needed
	T& get(int x, int y) //for getting element. This may never throw, and must return a null-value if out of bounds
	void reserve(int x_size, int y_size)  //for reserving the size of the matrix (if MatrixRep is array-based)
	MatrixRep needs to handle dynamic resizing, especially the MatrixRep needs to resize
	if setting and element that is beyond the size of the matrix
	MatrixRep needs to be a class template on a T type, which is the type of the weight
	Needs to be copy-able and move-able.
*/

namespace tsp
{

	template <class T, template <class> class WeightedMatrixRep>
	class Graph: private WeightedMatrixRep<T>
	{
	public: 
		class NeighbourView
		{
		public: 
			template <class T, template <class> class WeightedMatrixRep>
			friend class Graph;

			class Iterator
			{
			public: 
				struct Node
				{
					Node(int neighbour_, int start_node_)
						:neighbour(neighbour_), start_node(start_node_)
					{}

					const int neighbour;
					const int start_node;
				};

				Iterator(int index, int node, Graph<T, WeightedMatrixRep>& graph);

				bool operator!=(const Iterator& rhs) const;
				Iterator operator++();
				Node operator*() const;
				int starting_node() const;
			private:
				void next();

				int m_index;
				int m_node; 
				Graph<T, WeightedMatrixRep>& m_graph;
			};

			NeighbourView(int node, Graph<T, WeightedMatrixRep>& graph);
			Iterator begin();
			Iterator end();
		private: 
			int m_node;	
			int m_end;
			Graph<T, WeightedMatrixRep>& m_graph;
		};

	public:
		NeighbourView get_neighbours(int node);
		void add_weight(int n0, int n1, const T& weight);
		int get_weight(int n0, int n1) const; 
	};
	
	template <class T, template <class> class WeightedMatrixRep>
	Graph<T, WeightedMatrixRep>::NeighbourView::Iterator::Iterator(int index, int node, Graph<T, WeightedMatrixRep>& graph)
		:m_index(index)
		,m_node(node)
		,m_graph(graph)
	{}

	template <class T, template <class> class WeightedMatrixRep>
	typename Graph<T, WeightedMatrixRep>::NeighbourView::Iterator Graph<T, WeightedMatrixRep>::NeighbourView::begin()
	{
		return Iterator(0, m_node, m_graph);
	}
	
	template <class T, template <class> class WeightedMatrixRep>
	typename Graph<T, WeightedMatrixRep>::NeighbourView::Iterator Graph<T, WeightedMatrixRep>::NeighbourView::end()
	{
		return Iterator(m_end, m_node, m_graph);
	}

	template <class T, template <class> class WeightedMatrixRep>
	bool Graph<T, WeightedMatrixRep>::NeighbourView::Iterator::operator!=(const Iterator& rhs) const
	{
		return m_index != rhs.m_index;
	}

	template <class T, template <class> class WeightedMatrixRep>
	void Graph<T, WeightedMatrixRep>::NeighbourView::Iterator::next()
	{
		if (m_index >= m_graph.size_y())
		{
			m_index = m_graph.size_y();
			return;
		}

		++m_index;
		while(m_graph.is_null(m_node, m_index))
		{
			++m_index;

			if (m_index >= m_graph.size_y())
			{
				m_index = m_graph.size_y();
				break;
			}
		}
	}

	template <class T, template <class> class WeightedMatrixRep>
	int Graph<T, WeightedMatrixRep>::NeighbourView::Iterator::starting_node() const
	{
		return m_node;
	}

	template <class T, template <class> class WeightedMatrixRep>
	typename Graph<T, WeightedMatrixRep>::NeighbourView::Iterator Graph<T, WeightedMatrixRep>::NeighbourView::Iterator::operator++()
	{
		next();
		return *this;
	}

	template <class T, template <class> class WeightedMatrixRep>
	typename Graph<T, WeightedMatrixRep>::NeighbourView::Iterator::Node Graph<T, WeightedMatrixRep>::NeighbourView::Iterator::operator*() const
	{
		return Node(m_index, m_node);
	}

	template <class T, template <class> class WeightedMatrixRep>
	Graph<T, WeightedMatrixRep>::NeighbourView::NeighbourView(int node, Graph<T, WeightedMatrixRep>& graph)
		:m_node(node)
		,m_graph(graph)
		,m_end(graph.size_y())
	{}

	template <class T, template <class> class WeightedMatrixRep>
	typename Graph<T, WeightedMatrixRep>::NeighbourView Graph<T, WeightedMatrixRep>::get_neighbours(int node)
	{
		return NeighbourView(node, *this);
	}

	template <class T, template <class> class WeightedMatrixRep>
	void Graph<T, WeightedMatrixRep>::add_weight(int n0, int n1, const T& weight)
	{
		set(n0, n1, get(n0, n1) + weight);
		set(n1, n0, get(n1, n0) + weight);
	}

	template <class T, template <class> class WeightedMatrixRep>
	int Graph<T, WeightedMatrixRep>::get_weight(int n0, int n1) const
	{
		return get(n0, n1);
	}

}