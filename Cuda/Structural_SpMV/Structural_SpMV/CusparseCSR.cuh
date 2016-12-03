#include <iostream>
#include "CSR.hpp"

class CusparseCSR
{
private:
	int h_order;
	int h_nnz;
	double* d_values;
	int* d_columnIndices;
	int* d_rowPointers;

public:
	CusparseCSR(int order, int nnz, double* values, int* columnIndexes, int* rowPointers);
	~CusparseCSR();
	int getOrder() const;
	int getNonZeroCount() const;
	void spMV(double* lhs, double* rhs) const;
	void spMV_T(double* lhs, double* rhs) const;
	CSR toCSR() const;
	friend std::ostream& operator<<(std::ostream& out, const CusparseCSR& matrix);
	friend std::ostream& operator<<(std::ostream& out, const CusparseCSR* matrix);
};