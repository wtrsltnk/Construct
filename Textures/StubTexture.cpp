#include "StubTexture.h"
#include <stdio.h>

void StubTexture::Convert()
{
	strcpy(this->name, "stub");
	this->img.sizeX = 16;
	this->img.sizeY = 16;
	this->img.bpp = 4;
	this->img.data = (char*)malloc(16 * 16 * this->img.bpp);
	
	for (int i = 0; i < 16 * 16; i++)
	{
		this->img.data[(i*3)] = this->color[0];
		this->img.data[(i*3)+1] = this->color[1];
		this->img.data[(i*3)+2] = this->color[2];
		this->img.data[(i*3)+3] = this->color[3];
	}
}

StubTexture::StubTexture(byte color[])
{
	for (int i = 0; i < 4; i++)
		this->color[i] = color[i];
	
	this->Convert();
}

StubTexture::~StubTexture()
{
}
