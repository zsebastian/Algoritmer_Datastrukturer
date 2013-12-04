#include <iostream>
#include <cmath>
#include <cassert>
#include <limits>
#include <chrono>

//---- 4.1
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

int main()
{	
	std::cout << "T(10) = " << complexity(short(10)) << std::endl;	
	std::cout << "T(3) = " << complexity(3) << std::endl;	
	std::cout << "T(4) = " << complexity(4) << std::endl;
	
	auto now = std::chrono::system_clock::now();

	for (int i = 0; i < 10000; ++i) 
	{
		complexity(i % 100 + 1);
	}

	auto then = std::chrono::system_clock::now();
	auto diff = std::chrono::duration_cast<std::chrono::microseconds>(then - now).count();

	std::cout << "100000 complexities took: " << diff << std::endl;

	return 0; 
}