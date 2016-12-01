#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <chrono>
#include "CSR.hpp"

class Benchmark
{
private:
	CSR* _matrix;
	double* _vector;
	int _repetitions;

	void run();

public:
	Benchmark(std::string& matrixPath, int repetitions = 1000);
	~Benchmark();
	long long measure();
};

#endif
