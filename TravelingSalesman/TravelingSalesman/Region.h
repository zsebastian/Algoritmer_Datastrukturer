#pragma once

#include <vector>
#include <cmath>

/* represents many cities with XY-coordinates */
namespace tsp
{
	template <class T>
	class Region
	{
	public:
		void add_city(T x, T y);
		typename std::vector<std::pair<T, T>>::const_iterator begin() const;
		typename std::vector<std::pair<T, T>>::const_iterator end() const;

		T distance(std::pair<T, T> c0, std::pair<T, T> c1) const;
	private:
		std::vector<std::pair<T, T>> m_city_coords;
	};

	template <class T>
	void Region<T>::add_city(T x, T y)
	{
		m_city_coords.push_back(std::make_pair(x, y));
	}

	template <class T>
	typename std::vector<std::pair<T, T>>::const_iterator Region<T>::begin() const
	{
		return m_city_coords.begin();
	}

	template <class T>
	typename std::vector<std::pair<T, T>>::const_iterator Region<T>::end() const
	{
		return m_city_coords.end();
	}

	template <class T>
	T Region<T>::distance(std::pair<T, T> c0, std::pair<T, T> c1) const
	{
		int x = c0.first - c1.first;
		int y = c0.second - c1.second;
		return std::sqrt(x * x + y * y);
	}

}