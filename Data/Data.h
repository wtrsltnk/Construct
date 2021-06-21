#ifndef DATA_H_
#define DATA_H_

#include "DataBlock.h"
#include "PackageList.h"
#include "TextureList.h"
#include "WADList.h"
#include "../World/BSPEntities.h"

class Data
{
public:
	Data();
	virtual ~Data();

	DataBlock* header;
	DataBlock* models;
	DataBlock* visibility;
	DataBlock* lighting;
	DataBlock* textures;
	DataBlock* entities;
	DataBlock* leafs;
	DataBlock* planes;
	DataBlock* nodes;
	DataBlock* vertices;
	DataBlock* edges;
	DataBlock* faces;
	DataBlock* texinfo;
	DataBlock* clipnodes;
	DataBlock* marksurfaces;
	DataBlock* surfedges;
	
	WADList* wads;
	
	TextureList* texs;
	
	BSPEntities ents;
	
};

#endif /*DATA_H_*/
