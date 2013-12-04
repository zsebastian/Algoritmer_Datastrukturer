#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <iomanip>
#include <chrono>

template <class itrType>
void bucketSort(itrType begin, itrType end)
{
	int k = *std::max_element(begin, end);

	std::vector<int> buckets(k + 1, 0);

	for(itrType itr = begin; itr != end; ++itr)
	{
		++buckets[*itr];
	}

	int val = 0;
	for(auto bucket : buckets)
	{
		for (int i = 0; i < bucket; ++i)
		{
			*begin = val;
			++begin;
		}
		++val;
	}
}


int main()
{
	std::mt19937 engine;
	std::uniform_int_distribution<int> distro(0, 127);
	std::vector<int> list(5000000);
	for (auto iter = list.begin(); iter != list.end(); ++iter)
	{
		*iter = distro(engine);
	}

	auto bucketSorted = list;
	auto qsorted = list;

	auto now = std::chrono::system_clock::now();
	bucketSort(bucketSorted.begin(), bucketSorted.end());
	auto then = std::chrono::system_clock::now();
	auto diff1 = std::chrono::duration_cast<std::chrono::microseconds>(then - now).count();

	now = std::chrono::system_clock::now();
	std::sort(qsorted.begin(), qsorted.end());
	then = std::chrono::system_clock::now();
	auto diff2 = std::chrono::duration_cast<std::chrono::microseconds>(then - now).count();

	int i = 0;
	/*for(auto itr : bucketSorted)
	{
		++i;
		if (i % 5 == 0)
			std::cout << std::endl;
		std::cout << std::setw(5) << itr; 
	}*/
	std::cout << std::endl;
	std::cout << "Bucket sort took: " << diff1 << " microsecs." << std::endl;
	std::cout << "std::sort took: " << diff2 << " microsecs." << std::endl;


	return 0; 
}