#include <iostream>

int testKernel();
namespace DOKTests { void buildAndPrint(); void testSlicing(); void testConversionToCSR(); }
namespace CSRTests { void spMVTest(); }
namespace CusparseCSRTests { void cusparseTest(); void printMatrix(); }
namespace AbaqusReaderTests { void ReadMatrix(); }
namespace BenchmarkTests { void runBenchmark(); }

int main()
{
	//testKernel();
	//DOKTests::testSlicing();
	//DOKTests::testConversionToCSR();
	//CSRTests::spMVTest();
	//CusparseCSRTests:cusparseTest();
	CusparseCSRTests::printMatrix();
	//AbaqusReaderTests::ReadMatrix();
	//BenchmarkTests::runBenchmark();
	

	std::cout << "\n\nPress any key to exit: ";
	char a;
	std::cin >> a;
	return 0;
}