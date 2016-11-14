#include "stdafx.h"
#include "DOK.hpp"
#include <iostream>

void BuildAndPrint()
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