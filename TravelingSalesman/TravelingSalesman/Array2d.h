#pragma once
#include <vector>

namespace tsp
{
	namespace matrix
	{
		template <class T>
		class Array2d	
		{
		public:
			virtual ~Array2d() {};
			Array2d();
			bool is_null(int x, int y) const;
			int size_x() const;
			int size_y() const;
			void reserve(int size_x, int size_y);
			void set(int x, int y, T weight);
			const T& get(int x, int y) const;
		private:
			std::vector<std::pair<bool, T>> m_vector;
			int m_size_x;
			int m_size_y;

			int get_index(int x, int y) const;
			const T& null_value() const;
		};

		template <class T>
		Array2d<T>::Array2d()
			:m_size_x(0)
			,m_size_y(0)
		{}

		template<class T>
		bool Array2d<T>::is_null(int x, int y) const
		{
			if (x < m_size_x && y < m_size_y)
				return !m_vector[get_index(x, y)].first;
			else
				return true;
		}

		template <class T>
		int Array2d<T>::size_x() const
		{
			return m_size_x; 
		}
	
		template <class T>
		int Array2d<T>::size_y() const
		{
			return m_size_y;
		}

		template <class T>
		int Array2d<T>::get_index(int x, int y) const
		{

			return m_size_x * y + x;
		}

		template <class T>
		const T& Array2d<T>::get(const int x, const int y) const
		{
			if (x < m_size_x && y < m_size_y)
				return m_vector[get_index(x, y)].second;
			else
				return null_value();
		}

		template <class T>
		const T& Array2d<T>::null_value() const
		{
			static T null_val = T();
			return null_val;
		}

		template <class T>
		void Array2d<T>::set(int x, int y, T weight)
		{
			if (x >= m_size_x || y >= m_size_y)
			{
				reserve(std::max(x + 1, m_size_x), std::max(m_size_y, y + 1));
			}
			m_vector[get_index(x, y)] = std::make_pair(true, std::move(weight));
		}

		template <class T>
		void Array2d<T>::reserve(int size_x, int size_y)
		{
			Array2d<T> old(std::move(*this));
		
			int max_x = std::max(old.m_size_x, size_x);
			int max_y = std::max(old.m_size_y, size_y);
			m_size_x = max_x;
			m_size_y = max_y;
			m_vector.resize(max_x * max_y);
		
			for (int x = 0; x < m_size_x; ++x)
			{
				for (int y = 0; y < m_size_y; ++y)
				{
					if (x < old.m_size_x && y < old.m_size_y)
						m_vector[get_index(x, y)] = std::move(old.m_vector[old.get_index(x, y)]);
					else
						m_vector[get_index(x, y)] = std::make_pair(false, T());
				}
			}
		}
	}
}