#ifndef DATABLOCK_H_
#define DATABLOCK_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

class DataBlock
{
protected:
	char* pData;
	int nSize;
	
	DataBlock();
	
public:
	virtual ~DataBlock();
	
	char* Ptr();
	int Size();
	
public:
	static DataBlock* Read(FILE* file, int size = -1, int offset = -1);
	static DataBlock* Create(char* data, int size);
};

#endif /*DATABLOCK_H_*/
