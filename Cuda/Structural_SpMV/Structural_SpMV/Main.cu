#include <iostream>

int testKernel();
namespace DOKTests { void buildAndPrint(); void testSlicing(); void testConversionToCSR(); void testConversionToELL(); }
namespace CSRTests { void spMVTest(); }
namespace ELLTests { void buildAndPrintMatrix(); void spMVTest(); }
namespace CusparseCSRTests { void cusparseTest(); void printMatrix(); void spMVTest(); }
namespace AbaqusReaderTests { void ReadMatrix(); }
namespace BenchmarkTests { void runBenchmark(); }

int main()
{
	//testKernel();
	//DOKTests::testSlicing();
	//DOKTests::testConversionToCSR();
	DOKTests::testConversionToELL();
	//CSRTests::spMVTest();
	//ELLTests::buildAndPrintMatrix();
	//ELLTests::spMVTest();
	//CusparseCSRTests:cusparseTest();
	//CusparseCSRTests::spMVTest();
	//AbaqusReaderTests::ReadMatrix();
	//BenchmarkTests::runBenchmark();
	

	std::cout << "\n\nPress any key to exit: ";
	char a;
	std::cin >> a;
	return 0;
}