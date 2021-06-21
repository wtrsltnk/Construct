#ifndef WORLD_H_
#define WORLD_H_

#include "BSPFile.h"
#include "WADFile.h"
#include "../Textures/Texture.h"
#include "Visibility.h"
#include "BSPEntities.h"
#include "array.h"

#define MAX_WADS 32
#define MAX_TEXTURES 256

typedef WADFile* LPWADFile;
typedef Texture* LPTexture;

typedef struct tFace
{
	int type;
	int flags;
	int texture;
	
	dplane_t plane;
	int side;

	int first;
	int count;
	
	tFace* next;
	
} tFace;

class World
{
protected:
	bool isloaded;
	BSPFile pBspFile;
	BSPEntities pBspEntities;
	
	int numwadfiles;
	LPWADFile vWadFiles[MAX_WADS];
	
	int numtextures;
	LPTexture vTextures[MAX_TEXTURES];
	
	int numfaces;
	tFace* firstface;
	
	array_t<3> vertlist;

	bool LoadDependencies();
	void UnLoadDependencies();
	
	bool InitializeWorldSpawn(entity_t* worldspawn);
	void AddWad(char* wad);
	
	bool InitializeTextures();
	Texture* FindTexture(char* name);
	Texture* GetStubTexture();
	
	bool InitializeFaces();
	
public:
	World();
	virtual ~World();
	
	bool LoadWorld(char* worldname);
	void Cleanup();

	Visibility* GetVisibilityTable();
	BSPEntities* GetEntities();
	LPTexture* GetTextures();
	int GetTextureCount();
	array_t<3>* VertList();
	tFace* FirstFace();
};

#endif /*WORLD_H_*/
