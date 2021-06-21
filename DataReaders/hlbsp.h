#ifndef BSP_H_
#define BSP_H_

#include "hlmiptex.h"

#define LUMP_ENTITIES 0
#define LUMP_PLANES 1
#define LUMP_TEXTURES 2
#define LUMP_VERTEXES 3
#define LUMP_VISIBILITY 4
#define LUMP_NODES 5
#define LUMP_TEXINFO 6
#define LUMP_FACES 7
#define LUMP_LIGHTING 8
#define LUMP_CLIPNODES 9
#define LUMP_LEAFS 10
#define LUMP_MARKSURFACES 11
#define LUMP_EDGES 12
#define LUMP_SURFEDGES 13
#define LUMP_MODELS 14

#define BSPVERSION 30
#define NUM_LUMPS (LUMP_MODELS + 1)

typedef struct tBSPLump
{
	int offset;
	int size;
	
} tBSPLump;

typedef struct tBSPHeader
{
	int version;
	tBSPLump lumps[NUM_LUMPS];
	
} tBSPHeader;

#endif /*BSP_H_*/
