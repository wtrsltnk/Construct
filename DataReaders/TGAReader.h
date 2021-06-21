#ifndef TGAREADER_H_
#define TGAREADER_H_

#include "DataReader.h"

class TGAReader : public DataReader
{
protected:
	virtual ReaderResult ReadMemory(DataBlock* block);
	
public:
	TGAReader(Data* data);
	virtual ~TGAReader();
};

#endif /*TGAREADER_H_*/
