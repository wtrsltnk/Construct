#ifndef WADTEXTURE_H_
#define WADTEXTURE_H_

#include "Texture.h"

class WADTexture : public Texture
{
protected:
	char* wdata;

	void FilterPixel(char* name, byte rgba[]);
public:
	WADTexture(char* d);
	virtual ~WADTexture();

	void Convert();
};

#endif /*WADTEXTURE_H_*/
