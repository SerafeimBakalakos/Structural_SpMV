#ifndef ABAQUS_READER_H
#define ABAQUS_READER_H

#include <string>
#include <fstream>
#include "DOK.hpp"

class AbaqusReader
{
private:
	std::string _path;


public:
	AbaqusReader(std::string path);
	int findOrder();
	DOK readStiffnessMatrix();
	DOK readFreeFreeStiffnessMatrix();
};

#endif