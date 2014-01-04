#pragma once

#include <set>
#include <map>
#include <exception>
#include <utility>
#include "Region.h"
#include "Edge.h"

namespace tsp
{
	struct Path
	{
	public: 
		void push(Edge edge) { m_path.push_back(edge); }
		std::vector<Edge> get_path() const { return m_path; }	
	private: 
		std::vector<Edge> m_path;

	}; 

	template <class T>
	class Graph
	{
	public: 
		Graph() {}
		Graph(tsp::Region<T>& region);
		
		void set(Edge edge, T weight);
		T get_weight(Edge edge) const; 
		std::set<int> get_neighbours(int) const; 
		std::set<int> get_nodes() const; 
		std::map<Edge, T> get_graph() const;
		
	private: 
		std::map<Edge, T> m_map; 
	};

	template <class T>
	Graph<T>::Graph(tsp::Region<T>& region)
	{
		for(int i = 0; i < region.size() - 1; ++i)
		{
			for(int j = i + 1; j < region.size(); ++j)
			{
				set(Edge(i, j), region.distance(region[i], region[j]));
			}
		}
	}

	template <class T>
	void Graph<T>::set(Edge edge, T weight)
	{
		edge.balance();
		m_map[edge] = weight;
	}

	template <class T>
	T Graph<T>::get_weight(Edge edge) const
	{
		edge.balance();
		auto find = m_map.find(edge);
		if(find == m_map.end())
			throw std::out_of_range("Edge not found");

		return find->second;
	}

	template <class T>
	std::set<int> Graph<T>::get_neighbours(int node) const
	{
		std::set<int> ret; 

		for(auto itr : m_map)
		{
			if(itr.first.get_start_node() == node)
				ret.insert(itr.first.get_end_node());
			if(itr.first.get_end_node() == node) 
				ret.insert(itr.first.get_start_node());
		}

		return ret; 
	}

	template <class T>
	std::set<int> Graph<T>::get_nodes() const
	{
		std::set<int> ret;
		for(auto node : m_map)
		{
			ret.insert(node.first.get_start_node());
			ret.insert(node.first.get_end_node());
		}
			
		return ret; 
	}

	template <class T>
	std::map<Edge, T> Graph<T>::get_graph() const
	{
		return m_map; 
	}
}

