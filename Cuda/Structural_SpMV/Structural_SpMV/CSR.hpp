#ifndef CSR_H
#define CSR_H

#include <iostream>

class CSR
{
private:
	int _order;
	int _nnz;
	double* _values;
	int* _columnIndexes;
	int* _rowPointers;

	int indexOf(int row, int col) const;

public:
	CSR(int order, int nnz, double* values, int* columnIndexes, int* rowPointers);
	~CSR();
	int getOrder() const;
	int getNonZeroCount() const;
	double get(int row, int col) const;
	void spMV(double* lhs, double* rhs) const;
	void spMV_T(double* lhs, double* rhs) const;

	friend std::ostream& operator<<(std::ostream& out, const CSR& matrix);
	friend std::ostream& operator<<(std::ostream& out, const CSR* matrix);
};

#endif
