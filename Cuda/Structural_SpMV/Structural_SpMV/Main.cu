#include <iostream>

int testKernel();
void cusparseTest();
void buildAndPrint();
void testSlicing();
void testConversionToCSR();
void ReadMatrix();
void CSRspMVTest();
void runBenchmark();

namespace CusparseCSRTests
{
	void printMatrix();
}

int main()
{
	//testKernel();
	//cusparseTest();
	//testSlicing();
	//ReadMatrix();
	//CSRspMVTest();
	//testConversionToCSR();
	//runBenchmark();
	CusparseCSRTests::printMatrix();

	std::cout << "\n\nPress any key to exit: ";
	char a;
	std::cin >> a;
	return 0;
}