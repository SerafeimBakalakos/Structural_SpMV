#ifndef ABAQUS_READER_H
#define ABAQUS_READER_H

#include <string>
#include <fstream>

class AbaqusReader
{
private:
	std::ifstream _file;


public:
	AbaqusReader(std::string path);
	int findOrder();
};

#endif