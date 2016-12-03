#include <iostream>
#include <exception>
#include <cuda_runtime.h>

#include "CusparseCSR.cuh"
#include "CSR.hpp"

CusparseCSR::CusparseCSR(int order, int nnz, double* values, int* columnIndexes, int* rowPointers):
	_order(order), _nnz(nnz)
{
	cudaError_t err;
	err = cudaMalloc((void**)&d_values, nnz * sizeof(double));
	err = cudaMemcpy(d_values, values, nnz * sizeof(double), cudaMemcpyHostToDevice);
	err = cudaMalloc((void**)&d_columnIndices, nnz * sizeof(int));
	err = cudaMemcpy(d_columnIndices, columnIndexes, nnz * sizeof(int), cudaMemcpyHostToDevice);
	err = cudaMalloc((void**)&d_rowPointers, (order+1) * sizeof(int));
	err = cudaMemcpy(d_rowPointers, rowPointers, (order + 1) * sizeof(int), cudaMemcpyHostToDevice);

	delete[] values;
	values = nullptr;
	delete[] columnIndexes;
	columnIndexes = nullptr;
	delete[] rowPointers;
	rowPointers = nullptr;

	cusparseCreateMatDescr(&_description); // General matrix, index base = 0
	d_ZERO = nullptr;
	d_ONE = nullptr;
}

CusparseCSR::~CusparseCSR()
{
	cusparseDestroyMatDescr(_description);
	cudaError_t err;
	err = cudaFree(d_values);
	err = cudaFree(d_columnIndices);
	err = cudaFree(d_rowPointers);
}

int CusparseCSR::getOrder() const
{
	return _order;
}

int CusparseCSR::getNonZeroCount() const
{
	return _nnz;
}

// y = alpha * A * x + beta * y
void CusparseCSR::spMV(cusparseHandle_t handle, double* dLhs, double* dRhs) const
{
	double alpha = 1.0;
	double beta = 0.0;
	cusparseDcsrmv(handle, CUSPARSE_OPERATION_NON_TRANSPOSE, _order, _order, _nnz, &alpha, _description, 
		d_values, d_rowPointers, d_columnIndices, dLhs, &beta, dRhs);
	cudaDeviceSynchronize();
}

void CusparseCSR::spMV_T(cusparseHandle_t handle, double* dLhs, double* dRhs) const
{
	double alpha = 1.0;
	double beta = 0.0;
	cusparseDcsrmv(handle, CUSPARSE_OPERATION_TRANSPOSE, _order, _order, _nnz, &alpha, _description,
		d_values, d_rowPointers, d_columnIndices, dLhs, &beta, dRhs);
	cudaDeviceSynchronize();
}

CSR CusparseCSR::toCSR() const
{
	cudaError_t err;
	double* hValues = new double[_nnz];
	err = cudaMemcpy(hValues, d_values, _nnz * sizeof(double), cudaMemcpyDeviceToHost);
	int* hColIndices = new int[_nnz];
	err = cudaMemcpy(hColIndices, d_columnIndices, _nnz * sizeof(int), cudaMemcpyDeviceToHost);
	int* hRowPtrs = new int[_order + 1];
	err = cudaMemcpy(hRowPtrs, d_rowPointers, (_order + 1) * sizeof(int), cudaMemcpyDeviceToHost);
	return CSR(_order, _nnz, hValues, hColIndices, hRowPtrs);
}

std::ostream& operator<<(std::ostream& out, const CusparseCSR& matrix)
{
	return out << matrix.toCSR();
}

std::ostream& operator<<(std::ostream& out, const CusparseCSR* matrix)
{
	return out << matrix->toCSR();
}