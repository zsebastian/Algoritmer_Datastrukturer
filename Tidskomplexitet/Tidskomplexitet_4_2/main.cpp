#include <iostream>
#include "complexity_table.h"
#include <chrono>

int main()
{
	complexity::complexity_table<int> complexity;
	
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