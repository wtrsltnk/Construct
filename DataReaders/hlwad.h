#ifndef HLWAD_H_
#define HLWAD_H_

#include "hlmiptex.h"

typedef struct tWADHeader
{
	char id[4];
	int numlumps;
	int lumpoffset;
	
} tWADHeader;

typedef struct tWADLump
{
	int filepos;
	int disksize;
	int size;
	char type;				// 0x43 = WAD3 mip (Half-Life)
	char compression;
	char pad1, pad2;
	char name[16];
	
} tWADLump;

#endif /*HLWAD_H_*/
