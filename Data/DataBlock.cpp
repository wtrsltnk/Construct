#include "DataBlock.h"

DataBlock::DataBlock()
{
	this->pData = 0;
	this->nSize = 0;
}

DataBlock::~DataBlock()
{
	if (this->pData != 0)
	{
		free(this->pData);
	}
	this->pData = 0;
	this->nSize = 0;
}

char* DataBlock::Ptr()
{
	return this->pData;
}

int DataBlock::Size()
{
	return this->nSize;
}

DataBlock* DataBlock::Read(FILE* file, int size, int offset)
{
	DataBlock* result = new DataBlock();
	
	if (size >= 0)
	{
		result->pData = (char*)malloc(size);
		if (offset != -1)
		{
			::fseek(file, offset, SEEK_SET);
		}
		result->nSize = ::fread(result->pData, 1, size, file);
	}
	else
	{
		::fseek(file, 0, SEEK_END);
		result->nSize = (int)::ftell(file);
		::fseek(file, 0, SEEK_SET);

		result->pData = (char*)malloc(result->nSize);
		result->nSize = ::fread(result->pData, 1, size, file);
	}

	if (result->nSize == 0)
	{
		delete result;
		result = 0;
	}
	
	return result;
}

DataBlock* DataBlock::Create(char* data, int size)
{
	DataBlock* result = new DataBlock();

	result->pData = (char*)malloc(size);
	result->nSize = size;
	memcpy(result->pData, data, result->nSize);
	
	return result;
}
