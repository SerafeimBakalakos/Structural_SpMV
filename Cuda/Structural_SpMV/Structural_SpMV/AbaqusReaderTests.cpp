#include "stdafx.h"
#include "AbaqusReader.hpp"
#include <iostream>
#include <string>


namespace AbaqusReaderTests
{
	void ReadOrder()
	{
		std::string path = "MatrixPool/5Hexa_Cantilever_Stiffness.mtx";
		AbaqusReader reader{ path };
		int order = reader.findOrder();
		std::cout << "Order = " << order << std::endl;

		order = reader.findOrder();
		std::cout << "Next try: Order = " << order << std::endl;
	}

	void ReadMatrix()
	{
		//std::string path = "MatrixPool/matrix.txt";
		std::string path = "MatrixPool/5Hexa_Cantilever_Stiffness.mtx";
		AbaqusReader reader{ path };
		DOK matrix = reader.readFreeFreeStiffnessMatrix();
		std::cout << matrix;
		std::cout << "Order = " << matrix.getOrder() << ", nnz = " << matrix.nonZeroCount() << std::endl;
	}
}
