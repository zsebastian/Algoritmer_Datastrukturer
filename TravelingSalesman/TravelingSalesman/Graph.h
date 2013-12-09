#pragma once
#include <utility>
#include <memory>
#include "Edge.h"
/*	MatrixRep concept:
		Must have a virtual destructor!
		Require these:
			bool is_null(int x, int y) const // true if x, y is not set. If out of bounds returns true
			int size_x() const // returns dimensions of matrix
			int size_y() const // returns dimensions of matrix
			void set(int x, int y, const T& weight)	//for setting element, this resizes the matrix if needed
			const T& get(int x, int y) const //for getting element. This may never throw, and must return a null-value if out of bounds
			void reserve(int x_size, int y_size)  //for reserving the size of the matrix (if MatrixRep is array-based)
		MatrixRep needs to handle dynamic resizing, especially the MatrixRep needs to resize
		if setting an element that is beyond the size of the matrix. The matrix should resize
		only when setting an element, not when reading.
		MatrixRep needs to be a class template on a T type, which is the type of the weight
		Needs to be copy-able and move-able.

	AccessorPolicy:
		Must have a virtual destructor
*/

namespace tsp
{
	namespace matrix
	{
		template <class T>
		class Array2d;
	}
	namespace matrix
	{
		template <class T>
		class KeyValue;
	}
	namespace accessor
	{
		template <class T, template <class> class MatrixType>
		class Symmetric;
	}

	template <class T, template <class> class MatrixRep, template <class, template <class> class > class AccessorPolicy>
	class Graph;

	typedef Graph<int, matrix::Array2d, accessor::Symmetric> SmallGraphi;
	typedef Graph<int, matrix::KeyValue, accessor::Symmetric> LargeGraphi;

	template <class T, template <class> class MatrixRep, template <class, template <class> class > class AccessorPolicy>
	class Graph: 
		public AccessorPolicy<T, MatrixRep>
	{
	public: 
		class NeighbourView
		{
		public: 
			template <class T, template <class> class MatrixRep>
			friend class AccessorPolicy;

			class Iterator
			{
			public: 

				Iterator(int index, int node, typename const Graph<T, MatrixRep, AccessorPolicy>& graph);

				bool operator!=(const Iterator& rhs) const;
				Iterator operator++();
				Edge operator*() const;
				int starting_node() const;
			private:
				void next();

				int m_index;
				int m_node; 
				const Graph<T, MatrixRep, AccessorPolicy>& m_graph;
			};

			NeighbourView(int node, typename const Graph<T, MatrixRep, AccessorPolicy>& graph );
			Iterator begin();
			Iterator end();
		private: 
			int m_node;	
			int m_end;
			const Graph<T, MatrixRep, AccessorPolicy>& m_graph;
		};

	public:
		NeighbourView get_neighbours(int node) const;

		using AccessorPolicy<T, MatrixRep>::get_weight;
		T get_weight(Edge edge) const;
	};



	template <class T, template <class> class MatrixRep, template <class, template <class> class > class AccessorPolicy>
	Graph<T, MatrixRep, AccessorPolicy>::NeighbourView::Iterator::Iterator(int index, int node, typename const Graph<T, MatrixRep, AccessorPolicy>& graph)
		:m_index(index)
		,m_node(node)
		,m_graph(graph)
	{
		next();
	}

	template <class T, template <class> class MatrixRep, template <class, template <class> class > class AccessorPolicy>
	typename Graph<T, MatrixRep, AccessorPolicy>::NeighbourView::Iterator Graph<T, MatrixRep, AccessorPolicy>::NeighbourView::begin()
	{
		return Iterator(0, m_node, m_graph);
	}
	
	template <class T, template <class> class MatrixRep, template <class, template <class> class > class AccessorPolicy>
	typename Graph<T, MatrixRep, AccessorPolicy>::NeighbourView::Iterator Graph<T, MatrixRep, AccessorPolicy>::NeighbourView::end()
	{
		return Iterator(m_end, m_node, m_graph);
	}

	template <class T, template <class> class MatrixRep, template <class, template <class> class > class AccessorPolicy>
	bool Graph<T, MatrixRep, AccessorPolicy>::NeighbourView::Iterator::operator!=(const Iterator& rhs) const
	{
		return m_index != rhs.m_index;
	}

	template <class T, template <class> class MatrixRep, template <class, template <class> class > class AccessorPolicy>
	void Graph<T, MatrixRep, AccessorPolicy>::NeighbourView::Iterator::next()
	{
		int size = std::max(m_graph.size_x(), m_graph.size_y());
		if (m_index >= size)
		{
			m_index = size;
			return;
		}

		while(m_graph.is_null(std::min(m_node, m_index), std::max(m_node, m_index)))
		{
			++m_index;

			if (m_index >= size)
			{
				m_index = size;
				break;
			}
		}
	}

	template <class T, template <class> class MatrixRep, template <class, template <class> class > class AccessorPolicy>
	int Graph<T, MatrixRep, AccessorPolicy>::NeighbourView::Iterator::starting_node() const
	{
		return m_node;
	}

	template <class T, template <class> class MatrixRep, template <class, template <class> class > class AccessorPolicy>
	typename Graph<T, MatrixRep, AccessorPolicy>::NeighbourView::Iterator Graph<T, MatrixRep, AccessorPolicy>::NeighbourView::Iterator::operator++()
	{
		++m_index;
		next();
		return *this;
	}

	template <class T, template <class> class MatrixRep, template <class, template <class> class > class AccessorPolicy>
	typename Edge Graph<T, MatrixRep, AccessorPolicy>::NeighbourView::Iterator::operator*() const
	{
		return Edge(m_index, m_node);
	}

	template <class T, template <class> class MatrixRep, template <class, template <class> class > class AccessorPolicy>
	Graph<T, MatrixRep, AccessorPolicy>::NeighbourView::NeighbourView(int node, const Graph<T, MatrixRep, AccessorPolicy>& graph)
		:m_node(node)
		,m_graph(graph)
		,m_end(std::max(graph.size_x(), graph.size_y()))
	{}

	template <class T, template <class> class MatrixRep, template <class, template <class> class > class AccessorPolicy>
	typename Graph<T, MatrixRep, AccessorPolicy>::NeighbourView Graph<T, MatrixRep, AccessorPolicy>::get_neighbours(int node) const
	{
		return NeighbourView(node, *this);
	}

	template <class T, template <class> class MatrixRep, template <class, template <class> class > class AccessorPolicy>
	T Graph<T, MatrixRep, AccessorPolicy>::get_weight(Edge edge) const
	{
		return get_weight(edge.start_node, edge.end_node);
	}

	namespace accessor
	{
		template <class T, template <class> class MatrixType>
		class Symmetric:
			protected MatrixType<T>
		{
		public:
			virtual ~Symmetric() {};
			void add_weight(int n0, int n1, const T& weight);
			int get_weight(int n0, int n1) const; 
		};

		template <class T, template <class> class MatrixType>
		class Asymmetric:
			protected MatrixType<T>
		{
		public:
			virtual ~Asymmetric() {};
			void add_weight(int n0, int n1, const T& weight);
			int get_weight(int n0, int n1) const; 
		};


		template <class T, template <class> class MatrixType>
		void Symmetric<T, MatrixType>::add_weight(int n0, int n1, const T& weight)
		{
			int min = std::min(n0, n1);
			int max = std::max(n0, n1);
			set(min, max, get(min, max) + weight);
		}

		template <class T, template <class> class MatrixType>
		int Symmetric<T, MatrixType>::get_weight(int n0, int n1) const
		{
			return get(std::min(n0, n1), std::max(n0, n1));
		}

		template <class T, template <class> class MatrixType>
		void Asymmetric<T, MatrixType>::add_weight(int n0, int n1, const T& weight)
		{
			set(n0, n1, get(n0, n1) + weight);
		}

		template <class T, template <class> class MatrixType>
		int Asymmetric<T, MatrixType>::get_weight(int n0, int n1) const
		{
			return get(n0, n1);
		}
	}
}