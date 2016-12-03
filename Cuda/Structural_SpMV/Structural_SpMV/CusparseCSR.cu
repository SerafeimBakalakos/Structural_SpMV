#include <iostream>
#include <exception>
#include <cuda_runtime.h>
#include "cusparse_v2.h"
#include "CusparseCSR.cuh"
#include "CSR.hpp"

CusparseCSR::CusparseCSR(int order, int nnz, double* values, int* columnIndexes, int* rowPointers):
	h_order(order), h_nnz(nnz), d_values(nullptr), d_columnIndices(nullptr), d_rowPointers(nullptr)
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
}

CusparseCSR::~CusparseCSR()
{
	cudaError_t err;
	err = cudaFree(d_values);
	err = cudaFree(d_columnIndices);
	err = cudaFree(d_rowPointers);
}

int CusparseCSR::getOrder() const
{
	return h_order;
}

int CusparseCSR::getNonZeroCount() const
{
	return h_nnz;
}

void CusparseCSR::spMV(double* lhs, double* rhs) const
{
}

void CusparseCSR::spMV_T(double* lhs, double* rhs) const
{
	throw std::exception("Not implemented yet");
}

CSR CusparseCSR::toCSR() const
{
	cudaError_t err;
	double* hValues = new double[h_nnz];
	err = cudaMemcpy(hValues, d_values, h_nnz * sizeof(double), cudaMemcpyDeviceToHost);
	int* hColIndices = new int[h_nnz];
	err = cudaMemcpy(hColIndices, d_columnIndices, h_nnz * sizeof(int), cudaMemcpyDeviceToHost);
	int* hRowPtrs = new int[h_order + 1];
	err = cudaMemcpy(hRowPtrs, d_rowPointers, (h_order + 1) * sizeof(int), cudaMemcpyDeviceToHost);
	return CSR(h_order, h_nnz, hValues, hColIndices, hRowPtrs);
}

std::ostream& operator<<(std::ostream& out, const CusparseCSR& matrix)
{
	return out << matrix.toCSR();
}

std::ostream& operator<<(std::ostream& out, const CusparseCSR* matrix)
{
	return out << matrix->toCSR();
}