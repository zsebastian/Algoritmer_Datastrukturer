#include "Tests.h"
#include <cassert>
#include "ArrayOfArrayRep.h"
#include "Graph.h"

void test_array_of_array_rep();
void test_matrix_weight_symmetry();

void tsp::tests::run()
{
	test_array_of_array_rep();
	test_matrix_weight_symmetry();
}

void test_array_of_array_rep()
{
	tsp::ArrayOfArrayRep<int> matrix;
	matrix.set(1, 1, 1);
	matrix.reserve(3, 3);
	matrix.set(3, 2, 3);
	assert(matrix.get(3, 2) == 3);
	assert(matrix.get(4, 3) == 0);

	assert(matrix.is_null(4,3));
	assert(!matrix.is_null(3,2));

	matrix.set(4, 2, 2);
	matrix.reserve(4, 4);

	assert(matrix.get(3, 2) == 3);
	assert(matrix.get(4, 2) == 2);
	assert(!matrix.is_null(4, 2));
	assert(matrix.is_null(10, 10));
}

void test_matrix_weight_symmetry()
{
	tsp::Graph<int, tsp::ArrayOfArrayRep> graph;
	graph.add_weight(1, 2, 10);
	graph.add_weight(1, 3, 15);
	assert(graph.get_weight(2, 1) == 10);
	assert(graph.get_weight(1, 2) == 10);
	assert(graph.get_weight(3, 1) == 15);
	assert(graph.get_weight(1, 3) == 15);
}