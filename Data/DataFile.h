#ifndef DATAFILE_H_
#define DATAFILE_H_

#include <stdio.h>
#include "DataBlock.h"

class DataFile
{
protected:
	char* szFileName;
	FILE* pFile;
	int nSize;
	
public:
	DataFile();
	virtual ~DataFile();
	
	bool OpenFile(const char* filename);
	bool IsOpen();
	DataBlock* ReadDataBlock(int size = -1, int offset = -1);
	int ReadData(void* data, int size, int offset = -1);
	void CloseFile();
	
	int Size();
};

#endif /*DATAFILE_H_*/
