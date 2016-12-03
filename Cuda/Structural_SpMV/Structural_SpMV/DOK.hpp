#ifndef DOK_H
#define DOK_H

#include "stdafx.h"
#include <vector>
#include <map>
#include "CSR.hpp"
#include "CusparseCSR.cuh"

class DOK
{
private:
	const int _order;
	std::vector<std::map<int, double>> _rows;

	std::vector<int> oldToNewIndices(std::vector<int>& rowsToKeep);

public:
	DOK(int order);
	void add(int row, int col, double value);
	int getOrder();
	double get(int row, int col);
	int nonZeroCount();
	void printDiagonal();
	DOK slice(std::vector<int>& rowsToKeep);
	CSR* toCSR();
	CusparseCSR toCusparseCSR();

	friend std::ostream& operator<<(std::ostream& out, const DOK& matrix);
};

#endif
