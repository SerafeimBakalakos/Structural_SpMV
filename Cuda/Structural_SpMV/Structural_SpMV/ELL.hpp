#ifndef ELL_H
#define ELL_H

#include <iostream>

class ELL
{
private:
	int _order;
	int _nnz;
	int _paddingCount; // value = 0, colIndex = 0
	int _columnsPerRow; // of the ELL format, not the original matrix
	double* _values;
	int* _columnIndexes;

	int indexOf(int row, int col) const;

public:
	ELL(int order, int nnz, int paddingCount, double* values, int* columnIndexes);
	~ELL();
	int getOrder() const;
	int getNonZeroCount() const;
	double get(int row, int col) const;
	void spMV(double* lhs, double* rhs) const;
	void spMV_T(double* lhs, double* rhs) const;

	friend std::ostream& operator<<(std::ostream& out, const ELL& matrix);
	friend std::ostream& operator<<(std::ostream& out, const ELL* matrix);
};


#endif
