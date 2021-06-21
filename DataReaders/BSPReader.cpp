#include "BSPReader.h"
#include "../Common/Utility.h"

BSPReader::BSPReader(Data* data) : DataReader(data)
{
}

BSPReader::~BSPReader()
{
}

ReaderResult BSPReader::ReadMemory(DataBlock* block)
{
	this->pData->header = DataBlock::Create(block->Ptr(), sizeof(tBSPHeader));
	tBSPHeader* hdr = (tBSPHeader*)this->pData->header->Ptr();
	
	if (hdr->version != BSPVERSION)
	{
		return ReaderResult(false, "Wrong BSP Version. Found %d, needed %d", BSPVERSION, hdr->version);
	}
	
	this->pData->entities = this->GetBlockFromLump(hdr->lumps[LUMP_ENTITIES], block);
	this->pData->planes = this->GetBlockFromLump(hdr->lumps[LUMP_PLANES], block);
	this->pData->textures = this->GetBlockFromLump(hdr->lumps[LUMP_TEXTURES], block);
	this->pData->vertices = this->GetBlockFromLump(hdr->lumps[LUMP_VERTEXES], block);
	this->pData->visibility = this->GetBlockFromLump(hdr->lumps[LUMP_VISIBILITY], block);
	this->pData->nodes = this->GetBlockFromLump(hdr->lumps[LUMP_NODES], block);
	this->pData->texinfo = this->GetBlockFromLump(hdr->lumps[LUMP_TEXINFO], block);
	this->pData->faces = this->GetBlockFromLump(hdr->lumps[LUMP_FACES], block);
	this->pData->lighting = this->GetBlockFromLump(hdr->lumps[LUMP_LIGHTING], block);
	this->pData->clipnodes = this->GetBlockFromLump(hdr->lumps[LUMP_CLIPNODES], block);
	this->pData->leafs = this->GetBlockFromLump(hdr->lumps[LUMP_LEAFS], block);
	this->pData->marksurfaces = this->GetBlockFromLump(hdr->lumps[LUMP_MARKSURFACES], block);
	this->pData->edges = this->GetBlockFromLump(hdr->lumps[LUMP_EDGES], block);
	this->pData->surfedges = this->GetBlockFromLump(hdr->lumps[LUMP_SURFEDGES], block);
	this->pData->models = this->GetBlockFromLump(hdr->lumps[LUMP_MODELS], block);
	
	this->pData->ents.ParseEntities(this->pData->entities->Ptr(), this->pData->entities->Size());
	
	this->LoadWadfiles();
	
	return ReaderResult();
}

void BSPReader::LoadWadfiles()
{
	if (this->pData != 0)
	{
		entity_t* worldspawn = this->pData->ents.FindEntityByClassName("worldspawn");
		
		if (worldspawn != 0)
		{
			this->pData->wads = new WADList();
			
			const char* wads = BSPEntities::FindEntityValue(worldspawn, "wad");
	
			char wad[256] = { 0 };
			int wi = 0;
	
			for (int i = 0; i < (int)strlen(wads); i++)
			{
				if (wads[i] == ';')
				{
					WADFile* file = new WADFile();
					
					file->OpenWAD(Utility::GetFileName(wad));
					
					this->pData->wads->AddWAD(file);
					
					wi = 0;
				}
				else
				{
					wad[wi++] = wads[i];
				}
			}
		}
	}
}

void BSPReader::LoadTextures()
{
	
}

void BSPReader::LoadSky()
{
	
}

DataBlock* BSPReader::GetBlockFromLump(tBSPLump& lump, DataBlock* block)
{
	if ((lump.offset + lump.size) > block->Size())
	{
		return false;
	}
	return DataBlock::Create(block->Ptr() + lump.offset, lump.size);
}
