#include "stdafx.h"
#include "AbaqusReader.hpp"
#include <iostream>
#include <string>

void ReadMatrix()
{
	std::string path = "MatrixPool/5Hexa_Cantilever_Stiffness.mtx";
	AbaqusReader reader{ path };
	int order = reader.findOrder();
	std::cout << "Order = " << order;
}