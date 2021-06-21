#include "WADTexture.h"
#include "../World/miptex.h"
#include <string.h>
#include <stdio.h>

void WADTexture::Convert()
{
	miptex_t* miptex = (miptex_t*)this->wdata;
	
	int size = miptex->width * miptex->height;
	
	byte* indices = (byte*)miptex + miptex->offsets[0];
	byte* palette = (byte*)miptex + miptex->offsets[3] + (size / 64) + 2;
	
	strcpy(this->name, miptex->name);
	
	this->img.sizeX = miptex->width;
	this->img.sizeY = miptex->height;
	this->img.bpp = 4;
	this->img.data = (char*)malloc(size * this->img.bpp);

	int pos = 0;
	for (int i = 0; i < size; i++)
	{
		byte rgba[4] = { 	palette[indices[i]*3], 
							palette[indices[i]*3 + 1], 
							palette[indices[i]*3 + 2], 
							255 };
		
		this->FilterPixel(miptex->name, rgba);
		
		this->img.data[pos++] = rgba[0];//palette[indices[i]*3];
		this->img.data[pos++] = rgba[1];//palette[indices[i]*3 + 1];
		this->img.data[pos++] = rgba[2];//palette[indices[i]*3 + 2];
		this->img.data[pos++] = rgba[3];//255;
	}
}

void WADTexture::FilterPixel(char* name, byte rgba[])
{
	if (name[0] == '{')
	{
		if ((rgba[0] == 0) && (rgba[1] == 0) && (rgba[2] == 255))
		{
			rgba[0] = 0;
			rgba[1] = 0;
			rgba[2] = 0;
			rgba[3] = 0;
		}
	}
	else if ((strcmp(name, "clip") == 0) || 
			(strcmp(name, "origin") == 0) || 
			(strcmp(name, "aaatrigger") == 0))
	{
		rgba[3] = 155;
	}
}

WADTexture::WADTexture(char* d)
{
	this->wdata = d;
}

WADTexture::~WADTexture()
{
}
