#include <iostream>
#include "cusparse_v2.h"
#include "CSR.hpp"

class CusparseCSR
{
private:
	int _order;
	int _nnz;
	cusparseMatDescr_t _description;
	double* d_values;
	int* d_columnIndices;
	int* d_rowPointers;
	double* d_ZERO;
	double* d_ONE;

public:
	CusparseCSR(int order, int nnz, double* values, int* columnIndexes, int* rowPointers);
	~CusparseCSR();
	int getOrder() const;
	int getNonZeroCount() const;
	void spMV(cusparseHandle_t _handle, double* dLhs, double* dRhs) const;
	void spMV_T(cusparseHandle_t _handle, double* dLhs, double* dRhs) const;
	CSR toCSR() const;
	friend std::ostream& operator<<(std::ostream& out, const CusparseCSR& matrix);
	friend std::ostream& operator<<(std::ostream& out, const CusparseCSR* matrix);
};