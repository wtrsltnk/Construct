#ifndef BSPREADER_H_
#define BSPREADER_H_

#include "DataReader.h"
#include "hlbsp.h"

class BSPReader : public DataReader
{
protected:
	DataBlock* GetBlockFromLump(tBSPLump& lump, DataBlock* block);
	
	void LoadWadfiles();
	void LoadTextures();
	void LoadSky();
	
public:
	BSPReader(Data* data);
	virtual ~BSPReader();

	virtual ReaderResult ReadMemory(DataBlock* block);
	
};

#endif /*BSPREADER_H_*/
