#include "stdafx.h"
#include "DOK.hpp"
#include <iostream>
#include <stdexcept>
#include <set>


//void print(double* array, int length)
//{
//	std::cout << "[ ";
//	for (int i = 0; i < length; ++i)
//	{
//		std::cout << array[i] << ' ';
//	}
//	std::cout << "]\n";
//}
//
//void print(int* array, int length)
//{
//	std::cout << "[ ";
//	for (int i = 0; i < length; ++i)
//	{
//		std::cout << array[i] << ' ';
//	}
//	std::cout << "]\n";
//}
//
//void print(int order, int nnz, double* values, int* indices, int* ptrs)
//{
//	std::cout << "Values = ";
//	print(values, nnz);
//	std::cout << "Column indices = ";
//	print(indices, nnz);
//	std::cout << "Row pointers = ";
//	print(ptrs, order + 1);
//}

std::vector<int> DOK::oldToNewIndices(std::vector<int>& rowsToKeep)
{
	std::set<int> keep{ rowsToKeep.begin(), rowsToKeep.end() };
	std::vector<int> indexMap(_order);
	int newIndex = -1;
	for (int i = 0; i < _order; ++i)
	{
		if (keep.count(i)) indexMap[i] = ++newIndex;
		else indexMap[i] = -1;
	}
	return indexMap;
}

int DOK::maxNonZerosPerRow()
{
	int max = 0;
	for (auto row : _rows)
	{
		if (row.size() > max) max = row.size();
	}
	return max;
}

DOK::DOK(int order) : _order(order), _rows(order)
{
}

void DOK::add(int row, int col, double value)
{
	if ((col < 0) || (col >= _order))
	{
		throw std::out_of_range("Invalid column index: " + col);
	}
		
	if (_rows[row].count(col) == 1)
	{
		throw std::exception("There already exists an entry with the same row and column indices");
	}
	else
	{
		_rows[row].insert(std::pair<int, double>(col, value));
	}
}
 
int DOK::getOrder()
{
	return _order;
}

double DOK::get(int row, int col)
{
	if ((col < 0) || (col >= _order))
	{
		throw std::out_of_range("Invalid column index: " + col);
	}
	auto iter = _rows[row].find(col);
	return (_rows[row].count(col) == 1) ? _rows[row][col] : 0.0;
}

int DOK::nonZeroCount()
{
	int count = 0;
	for (auto row : _rows) count += row.size();
	return count;
}


void DOK::printDiagonal()
{
	std::cout << "Diagonal: \n";
	for (int row = 0; row < _order; ++row)
	{
		std::cout << get(row, row) << "\n";
	}
}

DOK DOK::slice(std::vector<int>& rowsToKeep)
{
	std::vector<int> indexMap = oldToNewIndices(rowsToKeep);
	DOK newDOK{ static_cast<int>(rowsToKeep.size()) };
	for (int row = 0; row < _order; ++row)
	{
		int newRow = indexMap[row];
		if (newRow > -1)
		{
			for (auto colValPair : _rows[row])
			{
				int newCol = indexMap[colValPair.first];
				if (newCol > -1)
				{
					newDOK.add(newRow, newCol, colValPair.second);
				}
			}
		}
	}
	return newDOK;
}

CSR* DOK::toCSR()
{
	int nnz = nonZeroCount();
	double* values = new double[nnz];
	int* columnIndices = new int[nnz];
	int* rowPointers = new int[_order + 1];
	rowPointers[_order] = nnz;

	int counter = 0;
	for (int row = 0; row < _order; ++row)
	{
		rowPointers[row] = counter;
		for (auto colValPair : _rows[row])
		{
			values[counter] = colValPair.second;
			columnIndices[counter] = colValPair.first;
			++counter;
		}
	}

	//print(_order, nnz, values, columnIndices, rowPointers);
	return new CSR(_order, nnz, values, columnIndices, rowPointers);
}

ELL* DOK::toELL()
{
	int nnz = nonZeroCount();
	int ellColumnsCount = maxNonZerosPerRow();
	int entriesCount = _order * ellColumnsCount;

	// Zero initialization. 0 is also used as a padding value.
	double* values = new double[entriesCount]();
	int* columnIndices = new int[entriesCount]();

	for (int row = 0; row < _order; ++row)
	{
		int ellCol = 0;
		for (auto colValPair : _rows[row])
		{
			int index = ellCol * _order + row;
			values[index] = colValPair.second;
			columnIndices[index] = colValPair.first;
			++ellCol;
		}
	}

	return new ELL(_order, nnz, entriesCount-nnz, values, columnIndices);
}

CusparseCSR* DOK::toCusparseCSR()
{
	int nnz = nonZeroCount();
	double* values = new double[nnz];
	int* columnIndices = new int[nnz];
	int* rowPointers = new int[_order + 1];
	rowPointers[_order] = nnz;

	int counter = 0;
	for (int row = 0; row < _order; ++row)
	{
		rowPointers[row] = counter;
		for (auto colValPair : _rows[row])
		{
			values[counter] = colValPair.second;
			columnIndices[counter] = colValPair.first;
			++counter;
		}
	}

	return new CusparseCSR(_order, nnz, values, columnIndices, rowPointers);
}

// Operators
std::ostream& operator<<(std::ostream& out, const DOK& matrix)
{
	out << "[\n";
	for (int row = 0; row < matrix._order; ++row)
	{
		auto rowMap = matrix._rows[row];
		out << "[ ";
		for (int col = 0; col < matrix._order; ++col)
		{
			out << rowMap[col] << ' ';
		}
		out << "]\n";
	}
	out << "]";
	return out;
}