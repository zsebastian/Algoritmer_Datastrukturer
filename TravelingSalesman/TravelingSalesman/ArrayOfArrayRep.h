#pragma once
#include <vector>

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
	std::vector<T> m_Vector;
	int m_Size_x;
	int m_Size_y;

	int get_index(int x, int y) const;
	const T& null_value() const;
};

template <class T>
ArrayOfArrayRep<T>::ArrayOfArrayRep()
	:m_Size_x(0)
	,m_Size_y(0)
{}

template <class T>
int ArrayOfArrayRep<T>::get_index(int x, int y) const
{
	return m_Size_y * x + y;
}

template <class T>
const T& ArrayOfArrayRep<T>::get(const int x, const int y) const
{
	static T null_val();
	if (x < m_Size_x && y < m_Size_y)
		return m_Vector[get_index(x, y)];
	else
		null_val;
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
	static T null_val();
	if (x >= m_Size_x && y >= m_Size_y)
	{
		reserve(x, y)
	}

	m_Vector[get_index(x, y)] = std::move(weight);
}

template <class T>
void ArrayOfArrayRep<T>::reserve(int size_x, int size_y)
{
	ArrayOfArrayRep<T> old(std::move(*this));
	int max_x = std::max(old.m_Size_x, m_Size_x);
	int max_y = std::max(old.size_y, m_Size_y);
	
	m_Vector.resize(max_x * max_y);

	for (int x = 0; x < m_Size_x; ++x)
	{
		for (int y = 0; x < m_Size_y; ++y)
		{
			if (x < old.m_Size_x && y < old.m_Size_y)
				m_Vector[get_index(x, y)] = old.m_Vector[old.get_index(x, y)];
			else
				m_Vector[get_index(x, y)] = T();
		}
	}
}

template <class T>
const T& ArrayOfArrayRep<T>::operator()(int x, int y) const
{
	return m_Vector[get_index(x, y)];
}

template <class T>
T& ArrayOfArrayRep<T>::operator()(int x, int y)
{
	return m_Vector[get_index(x, y)];
}