#include "stdafx.h"
#include "DOK.hpp"
#include <iostream>
#include <stdexcept>


DOK::DOK(const int order) : _order(order), _rows(order)
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