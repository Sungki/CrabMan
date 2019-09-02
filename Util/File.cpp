#include "File.h"
#include <fstream>

File::File(const char* filename)
	: m_size(0), m_data(0)
{
	std::ifstream in(filename, std::ifstream::binary);				// use the standard ifstream for reaing a level file
	if (in)
	{
		in.seekg(0, std::ifstream::end);							// move to the end of the file
		m_size = static_cast<int>(in.tellg());						// get the length of the file
		in.seekg(0, std::ifstream::beg);							// move back to the first of the file
		m_data = new char[m_size];									// make the data array for the size
		in.read(m_data, m_size);									// read the data from the file
	}
}

File::~File()
{
	delete[] m_data;												// delete the data array
	m_data = 0;
}

int File::getSize() const											// the function for getting the size
{
	return m_size;
}

const char* File::getData() const									// the function for getting the pointer of the data
{
	return m_data;
}