#include "DataFile.h"

DataFile::DataFile()
{
	this->szFileName = 0;
	this->pFile = 0;
	this->nSize = 0;
}

DataFile::~DataFile()
{
	this->CloseFile();
}

bool DataFile::OpenFile(const char* filename)
{
	this->szFileName = new char[strlen(filename) + 1];
	strcpy(this->szFileName, filename);
	
	if (filename != 0)
	{
		this->pFile = ::fopen(filename, "rb");
		
		if (this->pFile != 0)
		{
			::fseek(this->pFile, 0, SEEK_END);
			this->nSize = (int)::ftell(this->pFile);
			::fseek(this->pFile, 0, SEEK_SET);
			
			return true;
		}
	}
	return false;
}

bool DataFile::IsOpen()
{
	return (this->pFile != 0);
}

DataBlock* DataFile::ReadDataBlock(int size, int offset)
{
	return DataBlock::Read(this->pFile, size, offset);
}

int DataFile::ReadData(void* data, int size, int offset)
{
	if (offset >= 0)
	{
		::fseek(this->pFile, offset, SEEK_SET);
	}
	return (int)::fread(data, 1, size, this->pFile);
}

void DataFile::CloseFile()
{
	if (this->szFileName != 0)
	{
		delete [] this->szFileName;
	}
	this->szFileName = 0;
	if (this->pFile != 0)
	{
		::fclose(this->pFile);
	}
	this->pFile = 0;
	this->nSize = 0;
}

int DataFile::Size()
{
	return this->nSize;
}
