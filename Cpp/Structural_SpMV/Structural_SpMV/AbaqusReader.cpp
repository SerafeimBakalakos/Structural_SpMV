#include "stdafx.h"
#include "AbaqusReader.hpp"
#include <sstream>


AbaqusReader::AbaqusReader(std::string path): _file{path}
{
	if (!_file.is_open())
	{
		std::string message = "Could not open file ";
		message.append(path);
		throw std::ios_base::failure(message);
	}
}

int AbaqusReader::findOrder()
{
	std::stringstream sstream;
	int maxRow = -1;
	while (_file)
	{
		// Read a number representing the row index
		std::string word;
		_file >> word;

		// Convert it to an int
		sstream << word;
		int row;
		sstream >> row;
		sstream.clear();

		// Check if it is the new max
		if (row > maxRow) maxRow = row;

		// Discard the col index and the value in the same line
		_file >> word;
		_file >> word;
	}
	return maxRow;
}
