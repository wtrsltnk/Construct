#ifndef STUBTEXTURE_H_
#define STUBTEXTURE_H_

#include "Texture.h"

class StubTexture : public Texture
{
protected:
	byte color[4];
	
public:
	StubTexture(byte color[4]);
	virtual ~StubTexture();
	
	void Convert();
};

#endif /*STUBTEXTURE_H_*/
