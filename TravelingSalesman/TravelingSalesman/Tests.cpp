#include "Tests.h"
#include <cassert>
#include "Array2d.h"
#include "Graph.h"
#include "KeyValue.h"

template <class rep>
void test_matrix_rep();

void test_graph_weight_symmetry();
void test_graph_view_iterator();

void tsp::tests::run()
{
	test_matrix_rep<tsp::matrix::Array2d<int>>();
	test_matrix_rep<tsp::matrix::KeyValue<int>>();

	test_graph_weight_symmetry();
	test_graph_view_iterator();
}

void test_graph_view_iterator()
{
	tsp::Graph<int, tsp::matrix::Array2d> graph;
	tsp::matrix::Array2d<int> matrix;
	matrix.set(1, 1, 1);
	matrix.set(1, 3, 2);
	matrix.set(4, 1, 3);
	matrix.set(2, 3, 42);
	matrix.set(3, 5, 42);

	int what = matrix.get(1, 1);
	graph.add_weight(1, 1, 1);
	graph.add_weight(1, 3, 2);
	graph.add_weight(4, 1, 3);
	graph.add_weight(3, 2, 42);
	graph.add_weight(3, 5, 42);

	int current = 0;
	for (auto node : graph.get_neighbours(1))
	{
		++current;
		assert (graph.get_weight(node.neighbour, node.start_node) == current);
	}
}

template <class rep>
void test_matrix_rep()
{
	rep matrix;
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

void test_graph_weight_symmetry()
{
	tsp::Graph<int, tsp::matrix::Array2d> graph0;
	tsp::Graph<int, tsp::matrix::KeyValue> graph1;
	graph0.add_weight(1, 2, 10);
	graph0.add_weight(1, 3, 15);
	graph0.add_weight(1, 10, 20);
	assert(graph0.get_weight(2, 1) == 10);
	assert(graph0.get_weight(1, 2) == 10);
	assert(graph0.get_weight(3, 1) == 15);
	assert(graph0.get_weight(1, 3) == 15);
	assert(graph0.get_weight(10, 1) == 20);
	assert(graph0.get_weight(1, 10) == 20);

	graph1.add_weight(1, 2, 10);
	graph1.add_weight(1, 3, 15);
	graph1.add_weight(1, 10, 20);
	assert(graph1.get_weight(2, 1) == 10);
	assert(graph1.get_weight(1, 2) == 10);
	assert(graph1.get_weight(3, 1) == 15);
	assert(graph1.get_weight(1, 3) == 15);
	assert(graph1.get_weight(10, 1) == 20);
	assert(graph1.get_weight(1, 10) == 20);
}