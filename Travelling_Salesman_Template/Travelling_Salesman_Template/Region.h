#pragma once
#include <vector>
#include <cmath>

namespace tsp
{
	template <class T>
	class Region
	{
	public: 
		void add_city(T x, T y);
		T distance(std::pair<T, T> c0, std::pair<T, T> c1) const; 
		int size() { return static_cast<int>(m_city_coords.size()); }
		std::pair<T, T> operator[](int index) { return m_city_coords[index]; }

	private: 
		std::vector<std::pair<T, T>> m_city_coords;
	};

	template <class T>
	void Region<T>::add_city(T x, T y)
	{
		m_city_coords.push_back(std::make_pair(x, y));
	}

	template <class T>
	T Region<T>::distance(std::pair<T, T> c0, std::pair<T, T> c1) const
	{
		T x = c0.first - c1.first;
		T y = c0.second - c1.second;
		T ret = std::sqrt(x * x + y * y);
		return std::sqrt(x * x + y * y);
	}
};