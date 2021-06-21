#include "DataReader.h"

DataReader::DataReader(Data* data)
{
	this->pData = data;
}

DataReader::~DataReader()
{
}

ReaderResult DataReader::ReadFile(const char* filename)
{
	FILE* file = ::fopen(filename, "rb");
	
	if (file != 0)
	{
		ReaderResult result = this->ReadMemory(DataBlock::Read(file));
		
		::fclose(file);
		return result;
	}
	
	return ReaderResult(false, "Unable to open file %s", filename);
}
