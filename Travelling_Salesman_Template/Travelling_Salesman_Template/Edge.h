#pragma once
#include <algorithm>

namespace tsp
{
	class Edge
	{
	public: 
		Edge(int start_node, int end_node)
			:m_start_node(start_node)
			,m_end_node(end_node)
		{}
		
		void set_start_node(int start) { m_start_node = start; }
		void set_end_node(int end)	   { m_end_node = end; }
		int get_start_node() const	   { return m_start_node; }
		int get_end_node() const	   { return m_end_node; }

		void balance()
		{
			int old_start_node = m_start_node;
			m_start_node = std::min(old_start_node, m_end_node);
			m_end_node = std::max(old_start_node, m_end_node);
		}

		inline friend bool operator<(const Edge& lhs, const Edge& rhs)
		{
			return (lhs.m_start_node < rhs.m_start_node) || (!(rhs.m_start_node < lhs.m_start_node)) && lhs.m_end_node < rhs.m_end_node;
		}

	private:
		int m_start_node; 
		int m_end_node;
	};
}