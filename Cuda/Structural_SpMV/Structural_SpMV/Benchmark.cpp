#include "stdafx.h"
#include "Benchmark.hpp"
#include <chrono>
#include "AbaqusReader.hpp"
#include "DOK.hpp"

void Benchmark::run()
{
	for (int i = 0; i < _repetitions; ++i)
	{
		_matrix->spMV(_vector, _vector);
	}
}

Benchmark::Benchmark(std::string& matrixPath, int repetitions): 
	_matrix{ nullptr }, _vector{ nullptr }, _repetitions{ repetitions }
{
	AbaqusReader reader{ matrixPath };
	DOK dok = reader.readFreeFreeStiffnessMatrix();
	_matrix = dok.toCSR();
	_vector = new double[_matrix->getOrder()];
}

Benchmark::~Benchmark()
{
	delete _matrix;
	delete[] _vector;
}

long long Benchmark::measure()
{
	using namespace std::chrono;
	high_resolution_clock::time_point start = high_resolution_clock::now();
	run();
	high_resolution_clock::time_point end = high_resolution_clock::now();
	long long duration = duration_cast<microseconds>(end - start).count();
	return duration / _repetitions;
}

