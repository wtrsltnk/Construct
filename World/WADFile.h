#ifndef WADFILE_H_
#define WADFILE_H_

#include "../Common/cmdlib.h"
#include "wad.h"

class WADFile
{
protected:
	FILE *wadhandle;
	wadinfo_t wadinfo;
	int numlumps;
    lumpinfo_t* lumpinfo = nullptr;
	
	bool ReadWadHeader(FILE *wadhandle, wadinfo_t *wadinfo);
	bool ReadWadLumps(FILE *wadhandle, long offset, int num_lumps, lumpinfo_t *lumpinfo);
	bool ReadWadMip(FILE *wadhandle, lumpinfo_t *lumpinfo, void *buffer);
	
public:
	WADFile();
	virtual ~WADFile();

    bool OpenWAD(const char *wadname);
	
    bool HasTexture(const char* name);
    bool ReadTexture(const char* name, void* buffer);
	
	int GetNumTextures();
	lumpinfo_t* GetTexture(int index);
	
	void CloseWAD();
};

#endif /*WADFILE_H_*/
