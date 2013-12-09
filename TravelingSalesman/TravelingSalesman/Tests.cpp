#include "Tests.h"
#include <cassert>
#include "ArrayOfArrayRep.h"

void test_array_of_array_rep();

void tsp::tests::run()
{
	test_array_of_array_rep();
}

void test_array_of_array_rep()
{
	tsp::ArrayOfArrayRep<int> matrix;
	matrix.set(3, 2, 3);
	assert(matrix.get(3, 2) == 3);
	assert(matrix(4, 3) == 0);
	matrix(4, 2) = 2;
	matrix.reserve(4, 4);

	assert(matrix.get(3, 2) == 3);
	assert(matrix(4, 2) == 2);
}