#include "stdafx.h"
#include "Benchmark.hpp"

void runBenchmark()
{
	std::string path = "MatrixPool/5Hexa_Cantilever_Stiffness.mtx";
	Benchmark test{ path };
	long long duration = test.measure();
	std::cout << "Average running time = " << duration << "microseconds";
}

