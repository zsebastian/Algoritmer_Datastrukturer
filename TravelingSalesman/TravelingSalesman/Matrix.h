#pragma once

/* WeightedMatrixRep concept:
	void set(int x, int y, const T& weight)	//for setting element
	T& get(int x, int y) //for getting element
	void reserve(int x_size, int y_size)  //for reserving the size of the matrix (if MatrixRep is array-based)
	T& operator(int x, int y) (const and non-const) // for accessing element
	MatrixRep needs to handle dynamic resizing, especially the MatrixRep needs to resize
	if setting and element that is beyond the size of the matrix
	MatrixRep needs to be a class template on a T type, which is the type of the weight
	Needs to be copy-able and move-able.
	*/

namespace tsp
{
	template <class T, typename class WeightedMatrixRep>
	class WeightedMatrix
	{

		WeightedMatrixRep m_matrix;
	};
}