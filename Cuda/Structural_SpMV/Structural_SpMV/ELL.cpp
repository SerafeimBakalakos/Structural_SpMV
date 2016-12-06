#include "stdafx.h"
#include <string>
#include "ELL.hpp"


int ELL::indexOf(int row, int col) const
{
	if ((row < 0) || (row >= _order) || (col < 0) || (col >= _order))
	{
		std::string msg = "Requested (row, col) = (" + std::to_string(row) + ", "
			+ std::to_string(col) + "), but order = " + std::to_string(_order);
		throw std::out_of_range(msg);
	}
	if (col == 0) // 0 is also used as a sentinel value for padding entries at row ends
	{
		// if A[0,row]!=0, then _columnIndexes[0*_order + row] contains 0, else it contains another column index
		if (_columnIndexes[row] == 0) return row; 
	}
	else
	{
		int entriesCount = _nnz + _paddingCount;
		for (int i = row; i < entriesCount; i+=_order)
		{
			if (_columnIndexes[i] == col) return i; // padding entries (columnIndexes=0) will now be exluded
		}
	}
	
	return -1;
}

ELL::ELL(int order, int nnz, int paddingCount, double* values, int* columnIndexes) :
	_order(order), _nnz(nnz), _paddingCount(paddingCount), _columnsPerRow((nnz+paddingCount)/order),
	_values(values), _columnIndexes(columnIndexes)
{
}

ELL::~ELL()
{
	delete[] _values;
}

int ELL::getOrder() const
{
	return _order;
}

int ELL::getNonZeroCount() const
{
	return _nnz;
}

double ELL::get(int row, int col) const
{
	int index = indexOf(row, col);
	return (index == -1) ? 0.0 : _values[index];
}

void ELL::spMV(double* lhs, double* rhs) const
{
	for (int row = 0; row < _order; ++row)
	{
		double dot = 0.0;
		for (int i = 0; i < _columnsPerRow; ++i)
		{
			int index1D = i*_order + row;
			double val = _values[index1D];
			if (val != 0.0) dot += val * lhs[_columnIndexes[index1D]];
		}
		rhs[row] = dot;
	}
}

void ELL::spMV_T(double* lhs, double* rhs) const
{
	// Initialization
	for (int i = 0; i < _order; ++i) rhs[i] = 0.0;

	// rhs = Sum(column[j] * lhs[j])
	for (int col = 0; col < _order; ++col)
	{
		double scalar = lhs[col];
		for (int i = 0; i < _columnsPerRow; ++i)
		{
			int index1D = i*_order + col;
			double val = _values[index1D];
			if (val != 0.0)
			{
				rhs[_columnIndexes[index1D]] += scalar * val;
			}
		}
	}
}

std::ostream& operator<<(std::ostream& out, const ELL& matrix)
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

std::ostream& operator<<(std::ostream& out, const ELL* matrix)
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