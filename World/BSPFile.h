#ifndef BSPFILE_H_
#define BSPFILE_H_

#include "../Common/cmdlib.h"
#include "bsp.h"

class BSPFile
{
	friend class World;
protected:
	dheader_t *header;
	dheader_t outheader;
	
	int nummodels;
	dmodel_t *dmodels;

	int visdatasize;
	byte *dvisdata;

	int lightdatasize;
	byte *dlightdata;

	int texdatasize;
	byte *dtexdata;

	int entdatasize;
	char *dentdata;

	int numleafs;
	dleaf_t *dleafs;

	int numplanes;
	dplane_t *dplanes;

	int numvertexes;
	dvertex_t *dvertexes;

	int numnodes;
	dnode_t *dnodes;

	int numtexinfo;
	texinfo_t *texinfo;

	int numfaces;
	dface_t *dfaces;

	int numclipnodes;
	dclipnode_t *dclipnodes;

	int numedges;
	dedge_t *dedges;

	int nummarksurfaces;
	unsigned short *dmarksurfaces;

	int numsurfedges;
	int *dsurfedges;
	
	void SwapBSPFile (qboolean todisk);
	void AddLump (int lumpnum, void *data, int len, FILE* wadfile);
	int CopyLump (int lump, void **dest, int size);
	
public:
	BSPFile();
	virtual ~BSPFile();

	bool LoadBSP(char *bspname);
	void WriteBSPFile(char *bspname);
	void PrintBSPFileSizes(void);
	void Cleanup();
};

#endif /*BSPFILE_H_*/
