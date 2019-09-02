#pragma once

class File
{
public:
	File(const char* filename);
	~File();
	int getSize() const;
	const char* getData() const;

private:
	int m_size;
	char* m_data;
};