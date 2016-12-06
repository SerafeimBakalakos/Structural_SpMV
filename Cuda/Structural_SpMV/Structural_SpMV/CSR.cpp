#include "stdafx.h"
#include <string>
#include "CSR.hpp"

int CSR::indexOf(int row, int col) const
{
	if ((row < 0) || (row >= _order) || (col < 0) || (col >= _order))
	{
		std::string msg = "Requested (row, col) = (" + std::to_string(row) + ", " 
			+ std::to_string(col) + "), but order = " + std::to_string(_order);
		throw std::out_of_range(msg);
	}
	int rowStart = _rowPointers[row];
	int nextRowStart = _rowPointers[row + 1];
	for (int i = rowStart; i < nextRowStart; ++i)
	{
		if (_columnIndexes[i] == col) return i;
	}
	return -1;
}

CSR::CSR(int order, int nnz, double* values, int* columnIndexes, int* rowPointers):
	_order(order), _nnz(nnz), _values(values), _columnIndexes(columnIndexes), _rowPointers(rowPointers)
{
}

CSR::~CSR()
{
	delete[] _values;
	delete[] _columnIndexes;
	delete[] _rowPointers;
}

int CSR::getOrder() const
{
	return _order;
}

int CSR::getNonZeroCount() const
{
	return _nnz;
}

double CSR::get(int row, int col) const
{
	int index = indexOf(row, col);
	return (index == -1) ? 0.0 : _values[index];
}

void CSR::spMV(double* lhs, double* rhs) const
{
	int rowStart = _rowPointers[0];
	for (int row = 0; row < _order; ++row)
	{
		double dotProduct = 0.0;
		int rowEnd = _rowPointers[row + 1];
		for (int i = rowStart; i < rowEnd; ++i)
		{
			dotProduct += _values[i] * lhs[_columnIndexes[i]];
		}
		rhs[row] = dotProduct;
		rowStart = rowEnd; 
	}
}

void CSR::spMV_T(double* lhs, double* rhs) const
{
	// Initialization
	for (int i = 0; i < _order; ++i) rhs[i] = 0.0;

	// rhs = Sum(column[j] * lhs[j])
	for (int col = 0; col < _order; ++col)
	{
		double scalar = lhs[col];
		int colStart = _rowPointers[col];
		int colEnd = _rowPointers[col + 1];
		for (int i = colStart; i < colEnd; ++i)
		{
			rhs[_columnIndexes[i]] += scalar * _values[i];
		}
	}
}

std::ostream& operator<<(std::ostream& out, const CSR& matrix)
{
	out << "[\n";
	for (int row = 0; row < matrix._order; ++row)
	{
		out << "[ ";
		for (int col = 0; col < matrix._order; ++col)
		{
			out << matrix.get(row, col) << ' ';
		}
		out << "]\n";
	}
	out << "]";
	return out;
}

std::ostream& operator<<(std::ostream& out, const CSR* matrix)
{
	out << "[\n";
	for (int row = 0; row < matrix->_order; ++row)
	{
		out << "[ ";
		for (int col = 0; col < matrix->_order; ++col)
		{
			out << matrix->get(row, col) << ' ';
		}
		out << "]\n";
	}
	out << "]";
	return out;
}