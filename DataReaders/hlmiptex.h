#ifndef HLMIPTEX_H_
#define HLMIPTEX_H_

#define MIPTEX_LEVES 4

typedef struct tMiptex
{
	char name[16];
	unsigned width, height;
	unsigned offsets[MIPTEX_LEVES];
	
} tMiptex;

#endif /*HLMIPTEX_H_*/
