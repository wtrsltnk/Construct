#include "TGAReader.h"

TGAReader::TGAReader(Data* data) : DataReader(data)
{
}

TGAReader::~TGAReader()
{
}

ReaderResult TGAReader::ReadMemory(DataBlock* block)
{
	return ReaderResult();
}
