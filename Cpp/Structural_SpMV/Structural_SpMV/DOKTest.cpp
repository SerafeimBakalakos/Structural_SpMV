#include "stdafx.h"
#include "DOK.hpp"
#include <iostream>

void buildAndPrint()
{
	DOK matrix{ 5 };
	matrix.add(0, 0, 100.0);
	matrix.add(0, 1, 101.0);
	matrix.add(0, 4, 104.0);
	matrix.add(1, 1, 111.0);
	matrix.add(1, 3, 113.0);
	matrix.add(3, 3, 133.0);
	std::cout << matrix;
}

DOK buildMatrix()
{
	int order = 5;
	DOK matrix{ order };
	matrix.add(0, 0, 1); matrix.add(0, 3, 2);
	matrix.add(1, 1, 3); matrix.add(1, 2, 4), matrix.add(1, 4, 5);
	matrix.add(2, 2, 6), matrix.add(2, 3, 7);
	matrix.add(3, 1, 5), matrix.add(3, 3, 8);
	matrix.add(4, 0, 2), matrix.add(4, 2, 7); matrix.add(4, 4, 9);
	
	return matrix;
}

void testSlicing()
{
	using std::cout;
	DOK matrix = buildMatrix();
	cout << "\nOriginal:\n" << matrix;

	DOK sliced1 = matrix.slice(std::vector<int>{1, 2, 3});
	cout << "\n Keep 1, 2, 3:\n" << sliced1;

	DOK sliced2 = matrix.slice(std::vector<int>{0, 3});
	cout << "\n Keep 0, 3:\n" << sliced2;

	DOK sliced3 = matrix.slice(std::vector<int>{0, 4});
	cout << "\n Keep 0, 4:\n" << sliced3;

	DOK sliced4 = matrix.slice(std::vector<int>{0, 1, 2, 3, 4});
	cout << "\n Keep all:\n" << sliced4;
}