// Structural_SpMV.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

void buildAndPrint();
void testSlicing();
void testConversionToCSR();
void ReadMatrix();
void CSRspMVTest();
void runBenchmark();

int main()
{
	//testSlicing();
    //ReadMatrix();
	//CSRspMVTest();
	//testConversionToCSR();
	runBenchmark();

    std::cout << "\n\nPress any key to exit: ";
    char a;
    std::cin >> a;
    return 0;
}

