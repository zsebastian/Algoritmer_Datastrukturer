#pragma once
#include <type_traits>
#include <map>
#include <cassert>

namespace complexity
{
	namespace detail
	{
		template <class T, class U>
		typename std::enable_if<std::numeric_limits<T>::digits >= std::numeric_limits<U>::digits, T>::type
			ceildiv (T x_, U y_)
		{
			typename std::enable_if<std::is_integral<T>::value, T>::type x = x_;
			typename std::enable_if<std::is_integral<U>::value, U>::type y = y_;
			assert(x >= 0 && y > 0);

			if (x == 0)
				return (x + y - 1) / y;
			else
				return 1 + ((x - 1) / y);
		}

		template <class T, class U>
		typename std::enable_if<std::numeric_limits<T>::digits < std::numeric_limits<U>::digits, U>::type
			ceildiv (T x_, U y_)
		{
			typename std::enable_if<std::is_integral<T>::value, T>::type x = x_;
			typename std::enable_if<std::is_integral<U>::value, U>::type y = y_;
			assert(x >= 0 && y > 0);

			if (x == 0)
				return (x + y - 1) / y;
			else
				return 1 + ((x - 1) / y);
		}

		template <class T>
		typename std::enable_if<std::is_integral<T>::value, T>::type
			complexity (T n) 
		{
			if(n == 1) 
				return 1; 
			else 
				//this is wrong for some values due to floating point imprecision. :(
				return complexity(n-1) + complexity(static_cast<T>(ceildiv(n, 2))) + n;
		}
	}

	template<class T, class Enable = void>
	class complexity_table; // undefined

	template <class T>
	class complexity_table<T, typename std::enable_if<std::is_integral<T>::value>::type>
	{
	public:
		T complexity(T);
		inline T operator()(T);
	private:
		std::map<T, T> m_Table;
	};
	
	template <class T>
	T complexity_table<T, typename std::enable_if<std::is_integral<T>::value>::type>::operator()(T n)
	{
		return complexity(n);
	}

	template <class T>
	T complexity_table<T, typename std::enable_if<std::is_integral<T>::value>::type>::complexity(T n)
	{
		auto find = m_Table.find(n);
		if (find == m_Table.end())
		{
			T val = detail::complexity(n);
			m_Table.insert(std::make_pair(n, val));
			return val;
		}
		else
			return find->second;
	}
}