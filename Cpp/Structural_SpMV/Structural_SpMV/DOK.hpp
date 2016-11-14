#ifndef DOK_H
#define DOK_H

#include "stdafx.h"
#include <vector>
#include <map>

class DOK
{
private:
	const int _order;
	std::vector<std::map<int, double>> _rows;

public:
	DOK(const int order);
	void add(int row, int col, double value);
	int getOrder();
	double get(int row, int col);

	friend std::ostream& operator<<(std::ostream& out, const DOK& matrix);
};

#endif
