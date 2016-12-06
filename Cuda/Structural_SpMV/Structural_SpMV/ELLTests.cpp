#include "stdafx.h"
#include <iostream>
#include "ELL.hpp"

namespace ELLTests
{
	ELL buildMatrix()
	{
		int order = 6;
		int nnz = 19;
		int paddingCount = 5;
		double* values = new double[nnz+paddingCount] { 10, 3, 7, 3, 8, 4, -2, 9, 8, 8, 9, 2, 0, 3, 7, 7, 9, -1, 0, 0, 0, 5, 13, 0 };
		int* colIndexes = new int[nnz+paddingCount] { 0, 0, 1, 0, 1, 1, 4, 1, 2, 2, 3, 4, 0, 5, 3, 3, 4, 5, 0, 0, 0, 4, 5, 0 };
		return ELL(order, nnz, paddingCount, values, colIndexes);
	}

	void buildAndPrintMatrix()
	{
		std::cout << buildMatrix();
	}

	void checkSpMVResult(double* result)
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

	void checkTransposeSpMVResult(double* result)
	{
		int order = 6;
		double expected[]{ 38, 6, 128, 148, 53, 55 };
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
		if (isCorrect) std::cout << "TransposeSpMV was correct.\n";
		else std::cout << "Error in TransposeSpMV!\n";
	}

	void spMVTest()
	{
		ELL matrix = buildMatrix();
		double* x = new double[6]{ 2, -3, 7, 9, 4, -12 };
		double* y = new double[6];
		double* z = new double[6];
		matrix.spMV(x, y);
		checkSpMVResult(y);
		matrix.spMV_T(x, z);
		checkTransposeSpMVResult(z);
		delete[] x;
		delete[] y;
		delete[] z;
	}
}