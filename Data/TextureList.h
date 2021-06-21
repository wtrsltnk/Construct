#ifndef TEXTURELIST_H_
#define TEXTURELIST_H_

#include "../Textures/Texture.h"

class TextureList
{
private:
	class Item
	{
	public:
		Item(Item* next, Texture* tex) : next(next), tex(tex) { }
		virtual ~Item() { }
		
		Item* next;
		Texture* tex;
	};
	
protected:
	int nSize;
	Item* pFirst;
	Item* pLast;
	
public:
	TextureList();
	virtual ~TextureList();
	
	int AddTexture(Texture* tex);
	
	int Size();
	Texture* GetTexture(int index);
};

#endif /*TEXTURELIST_H_*/
