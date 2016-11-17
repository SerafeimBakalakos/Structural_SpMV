#include "stdafx.h"
#include "AbaqusReader.hpp"
#include <sstream>
#include <cmath>

// Helper functions
static std::vector<int> findFreeDOFs(DOK& matrix)
{
	double tolerance = 1e-8;
	double infinity = 1e+36;
	std::vector<int> freeDOFs;
	for (int dof = 0; dof < matrix.getOrder(); ++dof)
	{
		double diagonal = matrix.get(dof, dof);
		if (abs(1.0 - infinity / diagonal) > tolerance) freeDOFs.push_back(dof);
	}
	return freeDOFs;
}


// Class member functions
AbaqusReader::AbaqusReader(std::string path): _path{path}
{
}

int AbaqusReader::findOrder()
{
	// Open the file
	std::ifstream file{ _path };
	if (!file.is_open())
	{
		std::string message = "Could not open file ";
		message.append(_path);
		throw std::ios_base::failure(message);
	}

	std::stringstream sstream;
	int maxRow = -1;
	while (file)
	{
		// Read a number representing the row index
		std::string word;
		file >> word;

		// Convert it to an int
		sstream << word;
		int row;
		sstream >> row;
		sstream.clear();

		// Check if it is the new max
		if (row > maxRow) maxRow = row;

		// Discard the col index and the value in the same line
		file >> word;
		file >> word;
	}

	file.close();
	return maxRow;
}

DOK AbaqusReader::readStiffnessMatrix()
{
	int order = findOrder();

	// Open the file
	std::ifstream file{ _path };
	if (!file.is_open())
	{
		std::string message = "Could not open file ";
		message.append(_path);
		throw std::ios_base::failure(message);
	}

	DOK matrix{ order };
	std::stringstream sstream;
	std::string word;
	int row, col;
	double value;
	while (file >> word)
	{
		//Read row index
		sstream << word;
		sstream >> row;
		sstream.clear();

		//Read column index
		file >> word;
		sstream << word;
		sstream >> col;
		sstream.clear();

		//Read value
		file >> word;
		sstream << word;
		sstream >> value;
		sstream.clear();

		matrix.add(row-1, col-1, value);
	}

	file.close();
	return matrix;
}

DOK AbaqusReader::readFreeFreeStiffnessMatrix()
{
	DOK matrix = readStiffnessMatrix();
	std::vector<int> freeDOFs = findFreeDOFs(matrix);
	DOK submatrix = matrix.slice(freeDOFs);
	return submatrix;
}

