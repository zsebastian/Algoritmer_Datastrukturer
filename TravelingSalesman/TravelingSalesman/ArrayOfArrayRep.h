#pragma once
#include <vector>

namespace tsp
{
	template <class T>
	class ArrayOfArrayRep	
	{
	public:
		ArrayOfArrayRep();

		void reserve(int size_x, int size_y);
		void set(int x, int y, T weight);
		const T& get(int x, int y) const;
		const T& operator()(int x, int y) const;
		T& operator()(int x, int y);
	private:
		std::vector<T> m_vector;
		int m_size_x;
		int m_size_y;

		int get_index(int x, int y) const;
		const T& null_value() const;
	};

	template <class T>
	ArrayOfArrayRep<T>::ArrayOfArrayRep()
		:m_size_x(0)
		,m_size_y(0)
	{}

	template <class T>
	int ArrayOfArrayRep<T>::get_index(int x, int y) const
	{
		return m_size_y * x + y;
	}

	template <class T>
	const T& ArrayOfArrayRep<T>::get(const int x, const int y) const
	{
		if (x < m_size_x && y < m_size_y)
			return m_vector[get_index(x, y)];
		else
			return null_value();
	}

	template <class T>
	const T& ArrayOfArrayRep<T>::null_value() const
	{
		static T null_val = T();
		return null_val;
	}

	template <class T>
	void ArrayOfArrayRep<T>::set(int x, int y, T weight)
	{
		if (x >= m_size_x && y >= m_size_y)
		{
			reserve(x + 1, y + 1);
		}

		m_vector[get_index(x, y)] = std::move(weight);
	}

	template <class T>
	void ArrayOfArrayRep<T>::reserve(int size_x, int size_y)
	{
		ArrayOfArrayRep<T> old(std::move(*this));
		m_size_x = size_x;
		m_size_y = size_y;
		int max_x = std::max(old.m_size_x, m_size_x);
		int max_y = std::max(old.m_size_y, m_size_y);
		m_vector.resize(max_x * max_y);
		
		for (int x = 0; x < m_size_x; ++x)
		{
			for (int y = 0; y < m_size_y; ++y)
			{
				if (x < old.m_size_x && y < old.m_size_y)
					m_vector[get_index(x, y)] = old.m_vector[old.get_index(x, y)];
				else
					m_vector[get_index(x, y)] = T();
			}
		}
	}

	template <class T>
	const T& ArrayOfArrayRep<T>::operator()(int x, int y) const
	{
		if (x >= m_size_x && y >= m_size_y)
		{
			reserve(x + 1, y + 1);
		}

		return m_vector[get_index(x, y)];
	}

	template <class T>
	T& ArrayOfArrayRep<T>::operator()(int x, int y)
	{
		if (x >= m_size_x && y >= m_size_y)
		{
			reserve(x + 1, y + 1);
		}

		return m_vector[get_index(x, y)];
	}
}