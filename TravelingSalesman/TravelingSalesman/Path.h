#pragma once
#include "Edge.h"
#include <vector>
#include <utility>
#include <numeric>

namespace tsp
{
	template <class T>
	class Path
	{
	public:
		/* returns false if the newly pushed edge follows from the previous edge.
			If the function returns false the edge will NOT have been inserted */
		template <template <class> class MatrixRep, template <class, template <class> class > class AccessorPolicy>
		bool push(Edge edge, const Graph<T, MatrixRep, AccessorPolicy>& from_graph);

		const std::pair<Edge, T>& front() const;
		const std::pair<Edge, T>& back() const;

		std::pair<Edge, T>& front();
		std::pair<Edge, T>& back();

		int total_edges() const;
		int total_weight() const;

		typename std::vector<std::pair<Edge, T>>::const_iterator begin() const;
		typename std::vector<std::pair<Edge, T>>::const_iterator end() const;

	private:
		std::vector<std::pair<Edge, T>> m_path;
	};

	template <class T>
	template <template <class> class MatrixRep, template <class, template <class> class > class AccessorPolicy>
	bool Path<T>::push(Edge edge, const Graph<T, MatrixRep, AccessorPolicy>& from_graph)
	{
		if (m_path.size() != 0) 
			if (m_path[m_path.size() -1].first.end_node != edge.start_node)
				return false;
		

		m_path.push_back(std::make_pair(edge, from_graph.get_weight(edge)));
		return true;
	}

	template <class T>
	int Path<T>::total_edges() const
	{
		return static_cast<int>(m_path.size());
	}

	template <class T>
	int Path<T>::total_weight() const
	{
		return std::accumulate(m_path.begin(), m_path.end(), 0, [&](T val, std::pair<Edge, T> e)
			{
				return val + e.second;
			});
	}

	template <class T>
	const std::pair<Edge, T>& Path<T>::front() const
	{
		return m_path.front();
	}

	template <class T>
	const std::pair<Edge, T>& Path<T>::back() const
	{
		return m_path.back();
	}

	template <class T>
	std::pair<Edge, T>& Path<T>::front()
	{
		return m_path.front();
	}

	template <class T>
	std::pair<Edge, T>& Path<T>::back()
	{
		return m_path.back();
	}

	template <class T>
	typename std::vector<std::pair<Edge, T>>::const_iterator Path<T>::end() const
	{
		return m_path.end();
	}
<<<<<<< HEAD

	template <class T>
	typename std::vector<std::pair<Edge, T>>::const_iterator Path<T>::begin() const
	{
		return m_path.begin();
	}

=======
>>>>>>> dd1890bb27ce4e1102bdfadecb37258121bdd3a5
}