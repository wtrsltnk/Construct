#ifndef DATAREADER_H_
#define DATAREADER_H_

#include "../Data/Data.h"
#include "ReaderResult.h"

class DataReader
{
protected:
	Data* pData;

	virtual ReaderResult ReadMemory(DataBlock* block) = 0;
	
public:
	DataReader(Data* data);
	virtual ~DataReader();

	ReaderResult ReadFile(const char* filename);
	
};

#endif /*DATAREADER_H_*/
