#pragma once
#include <map>

namespace tsp
{
	namespace matrix
	{
		template <class T>
		class KeyValue
		{
		public:
			KeyValue();
			bool is_null(int x, int y) const;
			int size_x() const;
			int size_y() const;
			void reserve(int size_x, int size_y);
			void set(int x, int y, T weight);
			const T& get(int x, int y) const;
		private:
			std::map<std::pair<int, int>, T> m_map;
			int m_size_x;
			int m_size_y;

			const T& null_value() const;
		};

		template <class T>
		KeyValue<T>::KeyValue()
			:m_size_x(0)
			,m_size_y(0)
		{}

		template <class T>
		void KeyValue<T>::reserve(int size_x, int size_y)
		{
			m_size_x = std::max(m_size_x, size_x);
			m_size_y = std::max(m_size_y, size_y);
		}

		template <class T>
		void KeyValue<T>::set(int x, int y, T weight)
		{
			m_size_x = std::max(m_size_x, x + 1);
			m_size_y = std::max(m_size_y, y + 1);
			m_map[std::make_pair(std::max(x, y), std::min(x, y))] = std::move(weight);
		}

		template <class T>
		const T& KeyValue<T>::get(int x, int y) const
		{
			auto find = m_map.find(std::make_pair(std::max(x, y), std::min(x, y)));
			if (find != m_map.end())
				return find->second;
			else
				return null_value();
		}

		template <class T>
		bool KeyValue<T>::is_null(int x, int y) const
		{
			if (x < m_size_x && y < m_size_y)
				return m_map.count(std::make_pair(std::max(x, y), std::min(x, y))) == 0;
			else
				return true;
		}

		template <class T>
		int KeyValue<T>::size_x() const
		{
			return m_size_x;
		}

		template <class T>
		int KeyValue<T>::size_y() const
		{
			return m_size_y;
		}

		template <class T>
		const T& KeyValue<T>::null_value() const
		{
			static T null_val = T();
			return null_val;
		}
	}
}