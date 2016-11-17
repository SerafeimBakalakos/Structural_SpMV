// Structural_SpMV.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

void buildAndPrint();
void testSlicing();
void ReadMatrix();

int main()
{
	//testSlicing();
    ReadMatrix();
    

    std::cout << "\n\nPress any key to exit: ";
    char a;
    std::cin >> a;
    return 0;
}

