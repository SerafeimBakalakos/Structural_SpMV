#include <iostream>
#include "CusparseCSR.cuh"

namespace CusparseCSRTests
{
	CusparseCSR buildMatrix()
	{
		int order = 6;
		int nnz = 19;
		double* values = new double[nnz] { 10, -2, 3, 9, 3, 7, 8, 7, 3, 8, 7, 5, 8, 9, 9, 13, 4, 2, -1 };
		int* colIndexes = new int[nnz] { 0, 4, 0, 1, 5, 1, 2, 3, 0, 2, 3, 4, 1, 3, 4, 5, 1, 4, 5 };
		int* rowPointers = new int[order + 1]{ 0, 2, 5, 8, 12, 16, 19 };
		return CusparseCSR(order, nnz, values, colIndexes, rowPointers);
	}

	void printMatrix()
	{
		CusparseCSR matrix = buildMatrix();
		std::cout << matrix;
	}

	void checkResult(double* result)
	{
		int order = 6;
		double expected[]{ 12, -57, 98, 145, -63, 8 };
		double tolerance = 1e-6;
		bool isCorrect = true;
		for (int i = 0; i < order; ++i)
		{
			if (abs(result[i] / expected[i] - 1.0) > tolerance)
			{
				isCorrect = false;
				break;
			}
		}
		if (isCorrect) std::cout << "SpMV was correct.\n";
		else std::cout << "Error in SpMV!\n";
	}

	void CSRspMVTest()
	{
		CusparseCSR matrix = buildMatrix();
		double* x = new double[6]{ 2, -3, 7, 9, 4, -12 };
		double* y = new double[6];
		matrix.spMV(x, y);
		checkResult(y);
	}
};
