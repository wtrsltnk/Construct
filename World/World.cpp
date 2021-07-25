#include "World.h"
#include "../Common/GameRoot.h"
#include "../Common/Utility.h"
#include "../Textures/WADTexture.h"
#include "../Textures/StubTexture.h"

/*
 * Initialization routines
 */
bool World::LoadWorld(const char* worldname)
{
	printf("[Load World]\n");

	if (this->isloaded) this->Cleanup();
	
	if (this->pBspFile.LoadBSP(worldname))
	{
		this->pBspFile.PrintBSPFileSizes();
		if (this->LoadDependencies())
		{
			this->isloaded = true;
			return true;
		}
	}

	this->Cleanup();
	
	return false;
}

bool World::LoadDependencies()
{
	printf("[Load Dependencies]\n");

	if (this->pBspEntities.ParseEntities(this->pBspFile.dentdata, this->pBspFile.entdatasize) > 0)
	{
		if (!this->InitializeWorldSpawn(this->pBspEntities.FindEntityByClassName("worldspawn")))
		{
			printf(" *** ERROR *** - Failed to load worldspawn\n");
			return false;
		}
		if (!this->InitializeTextures())
		{
			printf(" *** ERROR *** - Failed to load textures\n");
			return false;
		}
		if (!this->InitializeFaces())
		{
			printf(" *** ERROR *** - Failed to setup faces\n");
			exit(0);
			return false;
		}
	}
	return true;
}

bool World::InitializeWorldSpawn(entity_t* worldspawn)
{
	printf("[Initialize WorldSpawn]\n");
	
	if (worldspawn != 0)
	{
		const char* wads = BSPEntities::FindEntityValue(worldspawn, "wad");
		
		char wad[256] = { 0 };
		int wi = 0;

		for (int i = 0; i < (int)strlen(wads); i++)
		{
			if (wads[i] == ';')
			{
				this->AddWad(Utility::GetFileName(wad));
				wi = 0;
			}
			else
			{
				wad[wi++] = wads[i];
			}
		}
		return true;
	}
	return false;
}

void World::AddWad(const char* wad)
{
	char* fullwadpath = GameRoot::GetInstance()->FindGameFile(wad);
	
	if (fullwadpath != 0)
	{
		WADFile* wadfile = new WADFile();
		if (wadfile->OpenWAD(fullwadpath))
		{
			printf("[Add Wad: %s]\n", wad);
			
			this->vWadFiles[this->numwadfiles++] = wadfile;
		}
	}
}

bool World::InitializeTextures()
{
	printf("[Initialize Textures]\n");
	
	dmiptexlump_t* lumps = (dmiptexlump_t*)this->pBspFile.dtexdata;
	
	for (int i = 0; i < lumps->nummiptex; i++)
	{
		Texture* tex = 0;
		if (lumps->dataofs[i] != -1)
		{
			miptex_t* miptex = (miptex_t*)(this->pBspFile.dtexdata + lumps->dataofs[i]);
			
			if (miptex->offsets[0] != 0)
			{
				tex = new WADTexture((char*)miptex);
			}
			else
			{
				tex = this->FindTexture(miptex->name);
			}
		}
		else
		{
			tex = this->GetStubTexture();
		}
		tex->Convert();
		this->vTextures[this->numtextures++] = tex;
	}
	return true;
}

Texture* World::FindTexture(const char* name)
{
	for (int i = 0; i < this->numwadfiles; i++)
	{
		WADFile* wad = this->vWadFiles[i];
		char buffer[MAX_LUMP_SIZE] = { 0 };
		
		if (wad->ReadTexture(name, buffer))
		{
			return new WADTexture(buffer);
		}
	}
	return this->GetStubTexture();
}

Texture* World::GetStubTexture()
{
	byte color[] = {128,45,3,255};
	
	return new StubTexture(color);
}

bool World::InitializeFaces()
{
    this->numfaces = 0;
	this->firstface = 0;
    printf("numfaces: %d\n", this->pBspFile.numfaces);

    for (int i = 0; i < this->pBspFile.numfaces; i++)
	{
		tFace* face = (tFace*)malloc(sizeof(tFace));
		face->next = this->firstface;
        this->firstface = face;
        this->numfaces++;
		
		memcpy(&face->plane, &this->pBspFile.dplanes[this->pBspFile.dfaces[i].planenum], sizeof(dplane_t));
		face->side = this->pBspFile.dfaces[i].side;
		
		switch (this->pBspFile.dfaces[i].numedges)
		{
		case 3: face->type = GL_TRIANGLES; break;
		case 4: face->type = GL_QUADS; break;
		default: face->type = GL_POLYGON; break;
		}

        texinfo_t *ti = this->pBspFile.texinfo + this->pBspFile.dfaces[i].texinfo;
        face->texture = ti->miptex; // texture index
        face->flags = ti->flags;
        
        face->first = this->vertlist.current();
        face->count = this->pBspFile.dfaces[i].numedges;
        
        for (int j = 0; j < this->pBspFile.dfaces[i].numedges; j++)
        {
        	float v[3] = { 0 };
        	
        	int eidx = *(this->pBspFile.dsurfedges + this->pBspFile.dfaces[i].firstedge + j);
        	if (eidx < 0)
        	{
        		eidx = -eidx;
        		dedge_t* e = &this->pBspFile.dedges[eidx];
        		for (int k = 0; k < 3; k++)
        			v[k] = this->pBspFile.dvertexes[e->v[1]].point[k];
        	}
        	else
        	{
        		dedge_t* e = &this->pBspFile.dedges[eidx];
        		for (int k = 0; k < 3; k++)
        			v[k] = this->pBspFile.dvertexes[e->v[0]].point[k];
        		
        	}
        	this->vertlist.add(v);
        }
	}

	return true;
}

/*
 * Cleanup routines
 */
void World::UnLoadDependencies()
{
	printf("[Unload Dependencies]\n");
	
	this->pBspEntities.Cleanup();
	
	for (int i = 0; i < this->numwadfiles; i++)
	{
		this->vWadFiles[i]->CloseWAD();
		
		delete this->vWadFiles[i];
	}
	
	for (int i = 0; i < this->numtextures; i++)
	{
		delete this->vTextures[i];
	}
}

void World::Cleanup()
{
	this->UnLoadDependencies();

	printf("[Cleanup World]\n");
	
	this->pBspFile.Cleanup();
	
	this->isloaded = false;
}

/*
 * Get / Set routines
 */
Visibility* World::GetVisibilityTable()
{
	static Visibility vis;
	
	vis.Decompress_VIS(this->pBspFile.numleafs, this->pBspFile.dleafs, this->pBspFile.dmodels, this->pBspFile.dvisdata);
	
	return &vis;
}

BSPEntities* World::GetEntities()
{
	static BSPEntities ents;
	
	ents.ParseEntities(this->pBspFile.dentdata, this->pBspFile.entdatasize);
	
	return &ents;
}

Texture** World::GetTextures()
{
	return this->vTextures;
}

int World::GetTextureCount()
{
	return this->numtextures;
}

array_t<3>* World::VertList()
{
	return &this->vertlist;
}

tFace* World::FirstFace()
{
	return this->firstface;
}

/*
 * De / Con-structors
 */
World::World()
{
	this->isloaded = false;
	this->numtextures = 0;
	this->numwadfiles = 0;
}

World::~World()
{
	this->Cleanup();
}
