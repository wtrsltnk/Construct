#include "WADFile.h"

bool WADFile::OpenWAD(const char *wadname)
{
	int size;

	wadhandle = SafeOpenRead(wadname);

	if (!this->ReadWadHeader(this->wadhandle, &this->wadinfo))
	{
		fclose(wadhandle);
		return false;
	}
	
	size = this->wadinfo.numlumps * sizeof(lumpinfo_t);
	this->lumpinfo = (lumpinfo_t *)malloc(size);

	this->numlumps = this->wadinfo.numlumps;
   
	this->ReadWadLumps(this->wadhandle, this->wadinfo.infotableofs, this->wadinfo.numlumps, this->lumpinfo);
	
	return true;
}

bool WADFile::HasTexture(const char* name)
{
	for (int i = 0; i < this->numlumps; i++)
	{
		if (strcmp(this->lumpinfo[i].name, name) == 0)
		{
			return true;
		}
	}
	return false;
}

bool WADFile::ReadTexture(const char* name, void* buffer)
{
	for (int i = 0; i < this->numlumps; i++)
	{
		if (strcmp(this->lumpinfo[i].name, name) == 0)
		{
			return this->ReadWadMip(this->wadhandle, &this->lumpinfo[i], buffer);
		}
	}
	return false;
}

int WADFile::GetNumTextures()
{
	return this->numlumps;
}

lumpinfo_t* WADFile::GetTexture(int index)
{
	if (index > 0 && index < this->numlumps)
	{
		return &this->lumpinfo[index];
	}
	return 0;
}

bool WADFile::ReadWadHeader(FILE *wadhandle, wadinfo_t *wadinfo)
{
   SafeRead(wadhandle, wadinfo, sizeof(wadinfo_t));

   if (strncmp(wadinfo->identification, "WAD3", 4))
      return false;

   wadinfo->numlumps = LittleLong(wadinfo->numlumps);
   wadinfo->infotableofs = LittleLong(wadinfo->infotableofs);

   return true;
}

bool WADFile::ReadWadLumps(FILE *wadhandle, long offset, int num_lumps, lumpinfo_t *lumpinfo)
{
   int index;

   fseek(wadhandle, offset, SEEK_SET);

   for (index=0; index < num_lumps; index++)
   {
      SafeRead(wadhandle, &lumpinfo[index], sizeof(lumpinfo_t));

      lumpinfo[index].filepos = LittleLong(lumpinfo[index].filepos);
      lumpinfo[index].disksize = LittleLong(lumpinfo[index].disksize);
      lumpinfo[index].size = LittleLong(lumpinfo[index].size);
   }
   
   return true;
}

bool WADFile::ReadWadMip(FILE *wadhandle, lumpinfo_t *lumpinfo, void *buffer)
{
   fseek(wadhandle, lumpinfo->filepos, SEEK_SET);

   SafeRead(wadhandle, buffer, lumpinfo->disksize);
   
   return true;
}

WADFile::WADFile()
{
	this->wadhandle = 0;
	this->numlumps = 0;
	this->lumpinfo = 0;
    this->wadinfo = {};
}

WADFile::~WADFile()
{
	this->CloseWAD();
}

void WADFile::CloseWAD()
{
	if (this->wadhandle != 0)
	{
		fclose(this->wadhandle);
		this->wadhandle = 0;
	}
	
	if (this->lumpinfo != 0)
	{
		free(this->lumpinfo);
		this->lumpinfo = 0;
		this->numlumps = 0;
	}
}
